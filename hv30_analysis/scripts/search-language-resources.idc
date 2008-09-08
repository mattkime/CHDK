
#include <idc.idc>

#include "scan-lib.idc"

#define CODE_START 0x041AA698
#define CODE_END   0x04400000

#define LANG_NUM 17

/*
 * Search for the HV30 Language OSD resources (17 languages blocks of pointers in Unicode)
 */
static main()
{
  auto sb, se, a, c, w, d;
  auto lang_idx;
  auto label;
  auto suff;
  auto labelmod;
  auto ptr;
  auto uis_null;
  auto have_refs;
  
  sb = CODE_START;
  se = CODE_END;

//  sb = 0x041E07E8;
//  se = sb+17*4;

  c = 0;
  for (a=sb; a<se; a=a+4)
  {

    uis_null = 0;
    have_refs = 0;
    
    for(lang_idx = 0; lang_idx < LANG_NUM; lang_idx = lang_idx+1)
    {
        ptr = Dword(a+lang_idx*4);
        
        if (ptr < CODE_START || ptr > CODE_END)
            break;
        // string length sanity
        if (Word(ptr) < 0 || Word(ptr) > 100)
            break;
        if (Word(ptr) == 0)
            uis_null = uis_null+1;
        if (lang_idx > 0 && (DfirstB(a+lang_idx*4) != BADADDR))
            have_refs = 1;
    };
    // All are valid pointers
    if (lang_idx != LANG_NUM)
    {
        continue;
    }
    // There should be a data reference to language block
    if (DfirstB(a) == BADADDR) continue;

//    if (strstr(Name(a), "uis_") == 0 ) continue;
    
    // Most part are nulls
    if (uis_null > 14 && Word(Dword(a+1*4)) == 0)
    {
      label = "NULLATMOST";
    }else{

      w = a+1*4;
      if (Word(Dword(w)) == 0) w = a + 5*4;
      if (Word(Dword(w)) == 0) w = a + 10*4;

      label = GetStringPascal(Dword(w));
      if (label == 0 || label == "") continue;

      MakeUnknown(a, LANG_NUM*4, DOUNK_SIMPLE);
      
      SetLongPrm(INF_STRTYPE, ASCSTR_ULEN2);
      for(lang_idx = 0; lang_idx < LANG_NUM; lang_idx = lang_idx+1)
      {
          MakeDword(a+lang_idx*4);
          ptr = Dword(a+lang_idx*4);
          if (0 == MakeStr(ptr, -1)) {
              MakeWord(ptr);
              MakeArray(ptr, Word(ptr)+1);
          }
      };
      SetLongPrm(INF_STRTYPE, ASCSTR_C);
    }

    Message("%08x Found: %s\n", a, label);

    suff = 1;
    labelmod = label;
    while( MakeNameEx(a, "uis_"+labelmod, SN_NOCHECK) == 0 && suff < 50) {
        labelmod = label + "_" + form("%d", suff);
        suff = suff+1;
    }

    if (have_refs == 0)
        MakeArray(a, LANG_NUM);

    c = c+1;
    if (have_refs == 0)
        a = a + LANG_NUM*4-4;
    
    if (a % 0x100000 == 0) Message("scanning: %x\n", a);
  }
  Message( "Refs found %d times\n", c);
}
