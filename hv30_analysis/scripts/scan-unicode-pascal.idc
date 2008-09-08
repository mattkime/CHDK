#include <idc.idc>
#include "scan-lib.idc"

#define ROM_START 0x04000000
#define ROM_END   0x04400000

/**
 * Searches for the strings in the area. IDA sometimes incorrectly detects strings as a code
 */

static main()
{
    
//    scan_unicode(0x043681E0, 0x043681D4+100);
    scan_unicode(ROM_START, ROM_END);
}

static scan_unicode(sb, se)
{
  auto a, c, cnt, w, d, str, isstr, res;
  auto suff, labelmod, label;

  cnt = 0;
  for (a=sb; a<se; a=a+2)
  {
    d = a;

//    if (!isUnknown(GetFlags(d))) continue;
//    if (strstr(Name(d), "word_") == 0) continue;
    if (strstr(Name(d), "a") == 0) continue;

    // There should be a data reference to language block
    if (DfirstB(d) == BADADDR) continue;

    str = GetStringPascal(d);

    if (str == "" || str == 0) continue;

    if (strlen(str) > 50) continue;

    isstr = 1;
    for(w = d+2; w < d+2+strlen(str)*2; w = w+2)
    {
        // English only
        if (Word(w) < 0x20 || Word(w) > 0x7F) isstr = 0;
        // There should be a data reference to language block
        if (DfirstB(w) != BADADDR) continue;
    }

    if (isstr == 0) continue;

    Message("%x %s     %s\n", d, Name(d), str);

    SetLongPrm(INF_STRTYPE, ASCSTR_ULEN2);
    if (0 == MakeStr(d, -1)) {
        MakeWord(d);
        MakeArray(d, Word(d)+1);
    }
    SetLongPrm(INF_STRTYPE, ASCSTR_C);

    suff = 1;
    label = str;
    labelmod = label;
    while( MakeNameEx(d, "au_"+labelmod, SN_NOCHECK) == 0 && suff < 50) {
        labelmod = label + "_" + form("%d", suff);
        suff = suff+1;
    }


    a = a + strlen(str)*2;

    cnt++;
    
  }
  Message( "Refs found %d times\n", cnt);
}
