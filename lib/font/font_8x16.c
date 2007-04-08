#include "font.h"

//-------------------------------------------------------------------
#define FONTDATAMAX     4096
#define FONTS_NUM       (sizeof(fontdata_8x16)/FONTDATAMAX)

//-------------------------------------------------------------------
static const unsigned char fontdata_8x16[][FONTDATAMAX] = {
    {
        #include "font_8x16_def.h"
    },
    {
        #include "font_8x16_uni.h"
    },
    {
        #include "font_8x16_kbr.h"
    },
    {
        #include "font_8x16_rus.h"
    }
};
const unsigned char *current_font = fontdata_8x16[FONT_DEFAULT];

//-------------------------------------------------------------------
void font_set(int font) {
    current_font = fontdata_8x16[(font>=0 && font<FONTS_NUM)?font:FONT_DEFAULT];
}

//-------------------------------------------------------------------
