#include <idc.idc>

#include "scan-lib.idc"

#define CODE_START 0x04000000
#define CODE_END   0x04400000

/**
 * Common script to make a code.
 * Seems to make it too often and sometimes incorrectly.
 */

static main()
{
  auto sb, se, a, c, w, d, y;
  auto lr, push;

  sb = CODE_START;
  se = CODE_END;

  c = 0;

  for (a=sb; a<se; a=a+2) {
    
    lr = 0;
    push = 0;

    d = Word(a);
    
    if ( (d&0xFF00) == 0x8f00 || (d&0xFF00) == 0x8e00)
      lr = 1;

    if ( d == 0x9F8C )
      lr = 1;

    if (d == 0x1781) 
      lr = 1;
    if (d == 0x1708) 
      lr = 1;

/*
    if (d == 0x287f) 
      push = 1;
*/

    if (!lr && !push) continue;

    if (!isUnknown(GetFlags(a))) continue;

    if (RfirstB0(a) == BADADDR && DfirstB(a) == BADADDR)  continue;

    for(y = DfirstB(a); y != BADADDR; y=DnextB(a,y) )
    {
        Message("%08x: %s\n", y, GetDisasm(y));
    }

//    Message("lr:%x, push:%x\n",lr, push);

    MakeFunction(a, BADADDR);

      //
/*    else if (isUnknown(GetFlags(a)))
    {
      MakeCode(a);
    }
*/
    Message( "Code: %x\n", a);
    c = c+1;

    if (a % 0x100000 == 0) Message("scanning: %x\n", a);
  }
  Message( "Code found %d times\n", c);
}
