#ifndef FONT_H
#define FONT_H
//-------------------------------------------------------------------

#define FONT_DEFAULT    0
#define FONT_UNIRUS     1
#define FONT_VGAKBR     2
#define FONT_KEYRUS     3

//-------------------------------------------------------------------
extern const unsigned char *current_font;

//-------------------------------------------------------------------
extern void font_set(int font);

//-------------------------------------------------------------------
#endif

