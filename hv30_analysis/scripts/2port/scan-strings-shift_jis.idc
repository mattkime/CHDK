#include <idc.idc>
#include "scan-lib.idc"

/**
 * Searches for the strings in the area. IDA sometimes incorrectly detects strings as a code
 */

#define ROM_START 0x4C8A6870
#define ROM_END   0x4CB97064

static main()
{
  auto sb, se, a, c, cnt, w, d, str, isstr, res;
  sb = ROM_START;
  se = GetSegmentAttr( sb, SEGATTR_END);

  cnt = 0;
  for (a=sb; a<se; a=a+1) {

    d = a;

    if (d > ROM_START && d < ROM_END) {
      
      str = d;
      
      isstr = 0;
      do{
        c = Byte(str);

        str = str+1;
        
        if (c == 0){
          isstr = 1;
          break;
        }

        if (  (c >= 0x20 && c <= 0x7E)  ) continue;
        if (c == 0x0A || c == 0x0D) continue;
        if (c == 0x09) continue;
        // shift jis
        break;
        if (  c >= 0xA1 && c <= 0xDF  ) continue;
        if (  c >= 0x81 && c <= 0x9F ||
              c >= 0xE0 && c <= 0xEF )
        {
          auto c2;
          
          c2 = Byte(str);
          if (c2 >= 0x3F && c2 <= 0xEE) {
            str = str+1;
            continue;
          }
          if (c2 == 0) {
            isstr = 1;
            break;
          }
        }

        
        break;
      }while(1);


      if (str - d >= 3 && str - d < 300 && isstr == 1)
      {
          
          MakeUnknown(d, str-d, DOUNK_EXPAND);
          res = MakeStr(d, str);

          Message( "Str found: %x-%d (%d) %s\n", d, str-d, res, getString(d));

          cnt = cnt+1;
          a = str-1;
          //if (a != str) a = a+4;
          //a = a-4;
          //if (cnt > 2)
          //  break;
      }

    }
  }
  Message( "Refs found %d times\n", cnt);
}
