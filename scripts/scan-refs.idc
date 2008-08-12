
#include <idc.idc>

#include "scan-lib.idc"

#define CODE_START 0x04000000
#define CODE_END   0x04400000

//#define CODE_START 0x4065FFE
//#define CODE_END   0x4065FFE+1000

#define ROM_START 0x4C8A6840
#define ROM_END   0x4CB97064

xxxxxxx badd!!!!!!!
static main()
{
  auto sb, se, a, c, w, d;
  sb = CODE_START;
  se = CODE_END;

  c = 0;
  for (a=sb; a<se; a=a+4) {
    d = Dword(a);                                                      //&& isData(GetFlags(a))
    
    if (d > CODE_START && d < CODE_END
        /* ||
        d > ROM_START && d < ROM_END */
        && isUnknown(GetFlags(a))
       ) {
      
      //MakeUnknown(a, 4, DOUNK_EXPAND);
      MakeDword(a);

      //if (d > CODE_START && d < CODE_END)
      {
      //  MakeCode(d);
        Message( "Ref found: %x=%s\n", a, GetDisasm(a));
      }

      c = c+1;
    }
    if (a % 0x100000 == 0) Message("scanning: %x\n", a);
  }
  Message( "Refs found %d times\n", c);
}
