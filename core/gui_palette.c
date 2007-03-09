#include "stdlib.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"
#include "conf.h"
#include "ubasic.h"
#include "gui_draw.h"
#include "gui_palette.h"

//-------------------------------------------------------------------
static volatile int full_palette;
static unsigned char cl;
static volatile char counter;
#define COUNTER_N 100
//-------------------------------------------------------------------
void gui_palette_init() {
    full_palette = 1;
    cl = 0x00;
    counter = COUNTER_N;
}

//-------------------------------------------------------------------
void gui_palette_kbd_process() {
    switch (kbd_get_clicked_key()) {
    case KEY_UP:
    	if (!full_palette) {
            cl = (((cl>>4)+1)<<4)|(cl&0x0f);
        }
        break;
    case KEY_DOWN:
    	if (!full_palette) {
            cl = (((cl>>4)-1)<<4)|(cl&0x0f);
        }
        break;
    case KEY_LEFT:
    	if (!full_palette) {
            cl = (((cl&0x0f)-1)&0x0f)|(cl&0xf0);
        }
        break;
    case KEY_RIGHT:
    	if (!full_palette) {
            cl = (((cl&0x0f)+1)&0x0f)|(cl&0xf0);
        }
        break;
    case KEY_SET:
    	full_palette = !full_palette;
    	counter = 0;
        break;
    }
}

//-------------------------------------------------------------------
void gui_palette_draw() {
    unsigned int x, y;
    char c, f=0;

    if (full_palette) {
        if (!counter || counter == COUNTER_N) {
            for (y=0; y<screen_height; ++y) {
                for (x=0; x<screen_width; ++x) {
                    c = ((y*16/screen_height)<<4)|(x*16/screen_width);
                    draw_pixel(x, y, c);
                }
            }
            if (counter) {
                draw_txt_string(6, 7, "Press SET to draw particular color", MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));
                draw_txt_string(6, 8, "       Press MENU to exit         ", MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));
            }
        }
        if (counter)
            --counter;
        f=1;
    }
    
    if (!full_palette) {
        char buf[16];
        sprintf(buf, " Color: 0x%02X ", cl);
        draw_txt_string(0, 0, buf, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));
        draw_filled_rect(20, 20, screen_width-20, screen_height-20, MAKE_COLOR(cl, COLOR_WHITE));
        draw_txt_string(0, 14, "Use \x18\x19\x1b\x1a to change color", MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));
    }
}

