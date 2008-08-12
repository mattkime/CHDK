
#include <idc.idc>

#include "scan-lib.idc"

#define CODE_START 0x04000000
#define CODE_END   0x04306898

#define ROM_START 0x4C8A6840
#define ROM_END   0x4CB97064

//#define TABLE 0x4C8B4D80
#define TABLE 0x4C8B52D0
#define ITEM_SIZE 0x44
#define PREFIX "shell_"

#define TABLE 0x4C8DCB60
#define ITEM_SIZE 0x44
#define PREFIX "shell_ctest_"


static main()
{
  auto sb, se, a, c, w, d, l;
  sb = TABLE;
  se = ROM_END;

  c = 0;
  
  for (a=sb; a<se; a=a+ITEM_SIZE) {

    w = getString(a);
    l = strlen(w);
    if (l < 2)
    {
      Message("Bad name: %s\n", w);
      break;
    }
    
    d = Dword(a + ITEM_SIZE-4);
    if (d < CODE_START || d > CODE_END)
    {
      Message("Bad address: %s: %x\n", a, d);
      break;
    }

    MakeNameEx(d, PREFIX + w, SN_NON_PUBLIC);
    MakeFunction(d, BADADDR);

    MakeUnknown(a + ITEM_SIZE-4, 4, DOUNK_EXPAND);
    MakeDword(a + ITEM_SIZE-4);
    MakeStr(a, a+l+1);

    MakeArray(a+l+1, ITEM_SIZE-l-1-4);

       
    Message( "Ref found: %x=%s\n", d, w);
    c = c+1;

    if (a % 0x100000 == 0) Message("scanning: %x\n", a);
  }
  Message( "Refs found %d times\n", c);
}
