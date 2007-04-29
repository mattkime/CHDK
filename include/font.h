#ifndef FONT_H
#define FONT_H

#include "gui.h"

//-------------------------------------------------------------------
#define FONT_DEFAULT    0
#define FONT_UNIRUS     1
#define FONT_VGAKBR     2
#define FONT_KEYRUS     3

#define FONT_CP_WIN     0
#define FONT_CP_DOS     1

//-------------------------------------------------------------------
extern const unsigned char *current_font;

//-------------------------------------------------------------------
extern void font_set(int font);

extern int rbf_load(char *file);
extern void rbf_load_from_8x16(const char *font);
extern int rbf_font_height();
extern int rbf_char_width(int ch);
extern int rbf_str_width(const char *str);
extern void rbf_set_codepage(int codepage);
extern int rbf_draw_char(int x, int y, int ch, color cl);
extern int rbf_draw_string(int x, int y, const char *str, color cl);
extern int rbf_draw_string_len(int x, int y, int len, const char *str, color cl);
extern int rbf_draw_string_right_len(int x, int y, int len, const char *str, color cl);

//-------------------------------------------------------------------
#endif

