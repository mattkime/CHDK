
#include <idc.idc>

#include "scan-lib.idc"

#define CODE_START 0x04000000
#define CODE_END   0x04400000

#define RANGE_START 0xBFA00000
#define RANGE_END   0xBFF00000

/*
 * Search for the data range
 */
static main()
{
  auto sb, se, a, c, w, d;
  sb = CODE_START;
  se = CODE_END;

  c = 0;
  for (a=sb; a<se; a=a+4)
  {
    d = Dword(a);
    
    if (d > RANGE_START && d < RANGE_END)
    {

      {
        Message( "%x Ref found: %s\n", a, GetDisasm(a));
      }

      c = c+1;
    }
    if (a % 0x100000 == 0) Message("scanning: %x\n", a);
  }
  Message( "Refs found %d times\n", c);
}
