#include <idc.idc>
#include "scan-lib.idc"

#define TRACE 0
#define FPREFIX "graphs/"

/*
 * Similar to xrefs graph in IDA, but
 * builds much more detailed graphs
 * and uses skyrails or touchgraph as a graphical backend
 */

static searchTask(start, arr, calleeHash, edgeHash, depth)
{
  auto x,y, fname, fend;
  auto refCount;
  
  x = start; //GetFunctionAttr(start, FUNCATTR_START);
  fend = GetFunctionAttr(start, FUNCATTR_END);

  fname = Name(start);
  //GetFunctionName(x);

  if (fname == 0) return;

  if (GetHashLong(arr, fname) != 0)
  {
      return;
  }

  if (TRACE) Message("*** " + atoa(start) + "  " + atoa(fend) + " - "+ fname + "\n");
  
  SetHashLong(arr, fname, x);

  refCount = 1;
  
  for(; x < fend; x = x+2)
  {
      auto type;
      auto name;
      for( y=Rfirst0(x); y != BADADDR; y=Rnext0(x,y) )
      {
          type = XrefType();
          if (type == fl_JF || type == fl_JN)
          {
              continue;
          }
          name = GetFunctionName(y);
          if (name == "") name = Name(y);

          SetHashLong(edgeHash, fname+"---"+name, 1);
          searchTask(y, arr, calleeHash, edgeHash, depth+1);
          refCount = refCount + 1;
      }
      for(y = Dfirst(x); y != BADADDR; y=Dnext(x,y) )
      {
          type = XrefType();
          name = GetFunctionName(y);
          if (name == "") name = Name(y);
          {
            SetHashLong(edgeHash, fname+"---"+name, 1);
          	searchTask(y, arr, calleeHash, edgeHash, depth+1);
          }
          refCount = refCount + 1;
      }
      
  }

  SetHashLong(calleeHash, fname, depth);

}

static ResolveTask(a)
{
  auto f;
  auto t, fname, ea, visitedHash, calleeHash, edgeHash;
  auto idx,fnode, tonode;
  auto length, color, fsize, shape, x, y, label, hint, visible;
  auto flags, type;

  fname = GetFunctionName(a);

  ea = GetFunctionAttr(a, FUNCATTR_START);
  
  DeleteArray( GetArrayId("visitedHash") );
  DeleteArray( GetArrayId("calleeHash") );
  DeleteArray( GetArrayId("edgeHash") );

  visitedHash = CreateArray("visitedHash");
  calleeHash = CreateArray("calleeHash");
  edgeHash = CreateArray("edgeHash");
  
  searchTask(ea, visitedHash, calleeHash, edgeHash, 1);

    f = fopen(FPREFIX + "xrefs-"+fname+".vna", "w");
    
    fprintf(f, "*Node data\n");
    fprintf(f, "\"ID\", \"text\", \"depthLevel\", \"type\"\n");
  
    for (t = GetFirstHashKey(calleeHash); t != 0; t = GetNextHashKey(calleeHash, t))
    {
        flags = GetFlags(GetHashLong(visitedHash, t));
        label = t;

        if (isCode(flags)){
          type = 1;
        }else
        if (isASCII(flags)){
          type = 2;
          label = getString(GetHashLong(visitedHash, t));
          label = replace(label, "\"", "'");
          label = replace(label, "\n", " ");
          label = replace(label, "\r", " ");
        }else
        //if (isData(flags))
        {
          type = 3;
        }

        fprintf(f, " \"%s\" \"%s\" \"%d\" \"%d\"\n", t, label, GetHashLong(calleeHash, t), type);
    }

 
    fprintf(f, "*Tie data\n");
    fprintf(f, "FROM TO \"length\" \"xxtype\"\n");

    for (t = GetFirstHashKey(edgeHash); t != 0; t = GetNextHashKey(edgeHash, t))
    {
        idx = strstr(t, "---");
        fnode = substr(t, 0, idx);
        tonode = substr(t, idx+3, strlen(t));
        if (GetHashLong(calleeHash, tonode) == 0) continue;
        if (fnode == tonode) continue;

        flags = GetFlags(GetHashLong(visitedHash, tonode));

        if (isCode(flags)){
          length = abs(GetHashLong(visitedHash, fnode)-GetHashLong(visitedHash, tonode))/100;
          //if (length > 1000) length = 1000;
          type = 1;
        }else
        if (isASCII(flags)){
          length = 20;
          type = 2;
        }else
        //if (isData(flags))
        {
          length = 10;
          type = 3;
        }

        fprintf(f, "\"%s\" \"%s\" %d %d\n", fnode, tonode, length, type);
    }
    

    fclose(f);




    f = fopen(FPREFIX + "xrefs-"+fname+".xml", "w");
    
    fprintf(f, "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>");
    fprintf(f, "<TOUCHGRAPH_LB version='1.20'><NODESET>\n");
  
    for (t = GetFirstHashKey(calleeHash); t != 0; t = GetNextHashKey(calleeHash, t))
    {
        color = 0xA00000;
        shape = 2;
        label = t;
        hint = form("0x%x %s", GetHashLong(visitedHash, t), "");
        visible = "true";

        if (isCode(GetFlags(GetHashLong(visitedHash, t))))
        {
          fsize = 20 - GetHashLong(calleeHash, t)*2;
          if (fsize < 9) fsize = 9;
          if (!hasUserName(GetFlags(GetHashLong(visitedHash, t)))){
            color = 0xFF2020;
          }
        }else
        if (isASCII(GetFlags(GetHashLong(visitedHash, t))))
        {
          color = 0x6060D0;
          fsize = 10;
          shape = 1;
          label = getString(GetHashLong(visitedHash, t));
          label = replace(label, "&", "@");
          label = replace(label, "'", "&apos;");
          label = replace(label, "<", "&lt;");
          label = replace(label, ">", "&gt;");
          label = replace(label, "\n", "");
          label = replace(label, "\r", "");
        }else
        //if (isData(GetFlags(GetHashLong(visitedHash, t))))
        {
          color = 0x50E050;
          fsize = 10;
          shape = 1;
          if (!hasUserName(GetFlags(GetHashLong(visitedHash, t)))){
            color = 0x90D040;
          }
        }
        x = 10;
        y = 10;

        fprintf(f, "<NODE nodeID='AutoID %s'>\n", t);
        fprintf(f, " <NODE_LOCATION x='%d' y='%d' visible='%s'/>\n", x, y, visible);
        fprintf(f, " <NODE_LABEL label='%s' shape='%d' backColor='%x' textColor='FFFFFF' fontSize='%d'/>\n",
                  label, shape, color, fsize);
//            <NODE_URL url="" urlIsLocal="false" urlIsXML="false"/>
        fprintf(f, " <NODE_HINT hint='%s' width='200' height='-1' isHTML='true'/>\n", hint);
        fprintf(f, "</NODE>\n");
    }
    
    fprintf(f, "</NODESET><EDGESET>\n");
    
//        
 
    for (t = GetFirstHashKey(edgeHash); t != 0; t = GetNextHashKey(edgeHash, t))
    {
        idx = strstr(t, "---");
        fnode = substr(t, 0, idx);
        tonode = substr(t, idx+3, strlen(t));
        if (GetHashLong(calleeHash, tonode) == 0) continue;
        if (fnode == tonode) continue;

        
        if (isCode(GetFlags(GetHashLong(visitedHash, tonode)))){
          length = abs(GetHashLong(visitedHash, fnode)-GetHashLong(visitedHash, tonode))/10;
          if (length > 1000) length = 1000;
          color = 0xA0A0A0;
        }else
        if (isASCII(GetFlags(GetHashLong(visitedHash, tonode)))){
          length = 40;
          color = 0xC0C0E0;
        }else
        //if (isData(GetFlags(GetHashLong(visitedHash, tonode))))
        {
          length = 30;
          color = 0xC0E0C0;
        }


        fprintf(f, "<EDGE fromID='AutoID %s' toID='AutoID %s' type='1' length='%d' visible='true' color='%x'/>\n",
                    fnode, tonode, length, color );
    }
    fprintf(f, "</EDGESET>    <PARAMETERS><PARAM name='offsetX' value='627'/><PARAM name='rotateSB' value='0'/><PARAM name='zoomSB' value='-7'/><PARAM name='offsetY' value='19'/></PARAMETERS></TOUCHGRAPH_LB>");
    

    fclose(f);

}

static main()
{
    
    ResolveTask(ScreenEA());

    Message("Done\n");
}

static test()
{

    auto at;

    DeleteArray( GetArrayId("attt") );

    at = CreateArray("attt");

    
    
    DelHashElement(at, "sss");

    SetHashLong(at, "sss", 234);

    Message(atoa(GetHashLong(at, "sss")));

    DeleteArray(at);

}


