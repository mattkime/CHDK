
#include <idc.idc>

#include "scan-lib.idc"

#define ROM_START 0x043090E8
//0x04306898
#define ROM_END   0x04309148
//0x045F7343

static main()
{
  auto sb, se, a, c, w, d;
  sb = ROM_START;
  se = ROM_END; //GetSegmentAttr( sb, SEGATTR_END);
BAD
  c = 0;
  for (a=sb; a<se; a=a+4) {

    if (  isCode(a)  ) {
      MakeUnknown(a, 2, DOUNK_EXPAND);
      MakeUnknown(a, 4, DOUNK_EXPAND);
      MakeDword(a);
      MakeWord(a);
      MakeByte(a);
      MakeByte(a+1);
      Message( "code found: %x=%s\n", a, GetDisasm(a));
      c = c+1;
    }
    if (a % 0x100000 == 0) Message("scanning: %x\n", a);
  }
  Message( "Refs found %d times\n", c);
}
