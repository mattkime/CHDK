#include <idc.idc>
#include "scan-lib.idc"

#define TRACE 0
#define FPREFIX "graphs/"

#define SHOW_UNK_DATA 0

// Touchgraph todo:
//   file name via command line


/*
 * Similar to xrefs graph in IDA, but
 * builds much more detailed graphs
 * and uses skyrails or touchgraph as a graphical backend
 */

static searchTask(start, arr, calleeHash, edgeHash, depth)
{
  auto x,y, fname, fend;
  auto refCount;
  auto type;
  auto name;
  
  x = GetFunctionAttr(start, FUNCATTR_START);
  if (x == -1) x = start;

  fend = GetFunctionAttr(start, FUNCATTR_END);

  fname = Name(x); //TODO - no-function code refs will be ignored!
  //GetFunctionName(x);

  if (fname == 0) return;

  if (GetHashLong(arr, fname) != 0)
  {
      return;
  }

  if (TRACE) Message("*** " + atoa(start) + "  " + atoa(fend) + " - "+ fname + "\n");
  
  SetHashLong(arr, fname, x);
  if (depth == 1000) SetHashLong(calleeHash, fname, depth);

  refCount = 1;

  if (depth >= 1000) {
      for(; x < fend; x = x+2)
      {

          for( y=Rfirst0(x); y != BADADDR; y=Rnext0(x,y) )
          {
              type = XrefType();
              if (type == fl_JF || type == fl_JN)
              {
                  continue;
              }
              name = GetFunctionName(y);
              if (name == 0) name = Name(y);
              if (name == 0){
                continue;
                name = atoa(y) + " " + GetDisasm(y);
              }

              if (GetHashLong(calleeHash, name) == 0){
                  SetHashLong(calleeHash, name, depth+1);
              }
              SetHashLong(edgeHash, fname+"---"+name, 1);

              searchTask(y, arr, calleeHash, edgeHash, depth+1);
              refCount = refCount + 1;
          }
          for(y = Dfirst(x); y != BADADDR; y=Dnext(x,y) )
          {
              type = XrefType();
              name = GetFunctionName(y);
              if (name == 0) name = Name(y);
              if (name == 0){
                continue;
                name = atoa(y) + " " + GetDisasm(y);
              }

              if (GetHashLong(calleeHash, name) == 0){
                  SetHashLong(calleeHash, name, depth+1);
              }
              SetHashLong(edgeHash, fname+"---"+name, 1);

              searchTask(y, arr, calleeHash, edgeHash, depth+1);
              refCount = refCount + 1;
          }
      }
  }
/*
  if (depth <= 1000)
  {
      x = GetFunctionAttr(start, FUNCATTR_START);

      if (TRACE) Message("* UP " + atoa(start) + "  " + atoa(fend) + " - "+ fname + "\n");

      for( y=RfirstB0(x); y != BADADDR; y=RnextB0(x,y) )
      {
          type = XrefType();
          if (type == fl_JF || type == fl_JN)
          {
              continue;
          }
          name = GetFunctionName(y);
          if (name == 0) name = Name(y);
          if (name == 0){
            continue;
            name = atoa(y) + " " + GetDisasm(y);
          }
          SetHashLong(calleeHash, name, depth-1);
          SetHashLong(edgeHash, name+"---"+fname, 1);
          searchTask(y, arr, calleeHash, edgeHash, depth-1);
          refCount = refCount + 1;
      }
      for(y = DfirstB(x); y != BADADDR; y=DnextB(x,y) )
      {
          type = XrefType();
          name = GetFunctionName(y);
          name = Name(y);
          if (name == 0){
            continue;
            name = atoa(y) + " " + GetDisasm(y);
          }
          SetHashLong(calleeHash, name, depth-1);
          SetHashLong(edgeHash, name+"---"+fname, 1);
          searchTask(y, arr, calleeHash, edgeHash, depth-1);
          refCount = refCount + 1;
      }
  }
*/
}

static ResolveTask(a)
{
  auto f;
  auto t, fname, ea, visitedHash, calleeHash, edgeHash;
  auto idx,fnode, tonode;
  auto length, color, fsize, shape, x, y, label, hint, visible;
  auto flags, type, depth;

  fname = GetFunctionName(a);

  ea = GetFunctionAttr(a, FUNCATTR_START);
  
  DeleteArray( GetArrayId("visitedHash") );
  DeleteArray( GetArrayId("calleeHash") );
  DeleteArray( GetArrayId("edgeHash") );

  visitedHash = CreateArray("visitedHash");
  calleeHash = CreateArray("calleeHash");
  edgeHash = CreateArray("edgeHash");
  
  searchTask(ea, visitedHash, calleeHash, edgeHash, 1000);

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
        color = 0x900000;
        shape = 2;
        label = t;
        hint = form("0x%x %s", GetHashLong(visitedHash, t), "");
        visible = "true";
        depth = GetHashLong(calleeHash, t)-1000;

        //if (depth == 0) visible = "true";

        if (isCode(GetFlags(GetHashLong(visitedHash, t))))
        {
          fsize = 20 - depth*2;
          if (fsize < 10) fsize = 10;
          if (fsize > 22) fsize = 22;
          if (!hasUserName(GetFlags(GetHashLong(visitedHash, t)))){
            color = 0xEE2020;
          }
        }else
        if (isASCII(GetFlags(GetHashLong(visitedHash, t))))
        {
          color = 0x6060C0;
          fsize = 10;
          shape = 1;
          label = getString(GetHashLong(visitedHash, t));
          label = replace(label, "&", "@");
          label = replace(label, "'", "&apos;");
          label = replace(label, "<", "&lt;");
          label = replace(label, ">", "&gt;");
          label = replace(label, "\n", "");
          label = replace(label, "\r", "");
          depth = -1;
        }else
        //if (isData(GetFlags(GetHashLong(visitedHash, t))))
        {
          color = 0x209020;
          fsize = 10;
          shape = 1;
          if (!hasUserName(GetFlags(GetHashLong(visitedHash, t)))){
            color = 0x70A070;
          }
          label = label + ": " + GetDisasm(GetHashLong(visitedHash, t));
          depth = -1;
          if (SHOW_UNK_DATA == 0) continue;
        }
        x = 10;
        y = 10;

        fprintf(f, "<NODE nodeID='AutoID %s'>\n", t);
        fprintf(f, " <NODE_LOCATION x='%d' y='%d' visible='%s'/>\n", x, y, visible);
        fprintf(f, " <NODE_LABEL label='%s' shape='%d' backColor='%x' textColor='FFFFFF' fontSize='%d'/>\n", label, shape, color, fsize);
		if (depth != -1){
            fprintf(f, " <NODE_BEHAVIOUR logic='com.touchgraph.graphlayout.mods.ApproachYbyWeight' weight='%d'/>\n", depth);
        }
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
          length = abs(GetHashLong(visitedHash, fnode)-GetHashLong(visitedHash, tonode))/5;
          if (length > 4000) length = 4000;
          color = 0xA0A0A0;
        }else
        if (isASCII(GetFlags(GetHashLong(visitedHash, tonode)))){
          length = 50;
          color = 0xC0C0E0;
        }else
        //if (isData(GetFlags(GetHashLong(visitedHash, tonode))))
        {
          length = 30;
          color = 0xC0E0C0;
          if (SHOW_UNK_DATA == 0) continue;
        }
        //length = length * 10;


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
