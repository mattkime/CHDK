/*
 * Searches for the List of locations within a code segment (jump table of func tables)
 */

#include <idc.idc>

#include "scan-lib.idc"

#define CODE_START 0x04000000
#define CODE_END   0x04400000

//#define CODE_START 0x4065FFE
//#define CODE_END   0x4065FFE+1000

#define ROM_START 0x4C8A6840
#define ROM_END   0x4CB97064

static isIn(addr)
{
  return addr > CODE_START && addr < CODE_END;
}

static main()
{
  auto sb, se, a, c, w, d;
  sb = CODE_START;
  se = CODE_END;

  c = 0;
  for (a=sb; a<se; a=a+4)
  {
    if (   isIn(Dword(a+0))
        && isIn(Dword(a+4))
        && isIn(Dword(a+8))
        )
    {
       Message("Table: %x\n", a);
       //MakeUnknown(a, 4, DOUNK_EXPAND);
       c = c+3;

       MakeDword(a+0);
       MakeDword(a+4);
       MakeDword(a+8);
       a = a + 8;
    }

    if (a % 0x100000 == 0) Message("scanning: %x\n", a);
  }
  Message( "Refs found %d times\n", c);
}
