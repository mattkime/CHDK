
#include <idc.idc>

#include "scan-lib.idc"

#define ROM_START 0x04000000
//#define ROM_START 0x04306898
#define ROM_END   0x045F7343

static main()
{
  auto sb, se, a, c, w, d;
  auto minn, maxx;

  sb = ROM_START;
  se = ROM_END;

  minn = 0x7FFFFFFF;
  maxx = 0;

  c = 0;
  for (a=sb; a<se; a=a+4) {
    
    d = GetDisasm(a);                                                      //&& isData(GetFlags(a))
    
    if ( substr(d, 0, 3) == "or3" ) {

      w = strstr(d, ", 0x4C");

      if (w == -1) continue;

      w = substr(d, w+2, w+12);
      
      //Message( "Ref found: %x=%d\n", a, xtol(w));
      //c = c+1;
      if (minn > w) minn = w;
      if (maxx < w) maxx = w;

    }
    if (a % 0x100000 == 0) Message("scanning: %x\n", a);
  }
  Message( "Const: min: %x, max: %x\n", minn, maxx);
}
