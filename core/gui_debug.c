#include "stdlib.h"
#include "keyboard.h"
#include "platform.h"
#include "core.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_debug.h"


//-------------------------------------------------------------------
static unsigned long addr;
static char debug_to_draw;
static char buf[32];

//-------------------------------------------------------------------
#define SCREEN_COLOR            0xDB

//-------------------------------------------------------------------
void gui_debug_init(const unsigned long st_addr) {
    addr = st_addr;
    debug_to_draw = 1;
    gui_set_mode(GUI_MODE_DEBUG);
}

//-------------------------------------------------------------------
static void gui_debug_draw_values(const coord y, const unsigned long addr) {
    int i;

    sprintf(buf, "0x%08X (%10u)", *((unsigned int*)addr), *((unsigned int*)addr));
    draw_txt_string(10, y, buf, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));

    sprintf(buf, "0x%04X (%5hu)", *((unsigned short*)addr), *((unsigned short*)addr));
    draw_txt_string(10, y+1, buf, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));

    sprintf(buf, "0x%02X (%3hu)", *((unsigned char*)addr), *((unsigned char*)addr));
    draw_txt_string(10, y+2, buf, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));

//    sprintf(buf, "0x%lf", *((double*)addr));
//    draw_txt_string(10, y+3, buf, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));

    for (i=0; i<30; ++i) {
        if (*((char*)(addr+i))) buf[i]=*((char*)(addr+i));
        else break;
    }
    while (i<30) {
        buf[i++]=' ';
    }
    buf[i]=0;
    draw_txt_string(10, y+4, buf, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));
}

//-------------------------------------------------------------------
void gui_debug_draw() {
    switch (debug_to_draw) {
        case 1:
            draw_filled_rect(0, 0, screen_width-1, screen_height-1, MAKE_COLOR(SCREEN_COLOR, SCREEN_COLOR));
            draw_txt_string(1, 0, "Address:", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(1, 1, "Values:",  MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(2, 2, "DWORD  :", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(2, 3, "WORD   :", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(2, 4, "BYTE   :", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(2, 5, "DOUBLE :", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(2, 6, "STRING :", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(1, 7, "Dereferencing:",  MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(2, 8, "DWORD  :", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(2, 9, "WORD   :", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(2, 10, "BYTE   :", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(2, 11, "DOUBLE :", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(2, 12, "STRING :", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));

            debug_to_draw = 2;
            break;
        case 2:
            sprintf(buf, "0x%08X", (unsigned int)addr);
            draw_txt_string(10, 0, buf, MAKE_COLOR(COLOR_RED, COLOR_WHITE));
            gui_debug_draw_values(2, addr);
//            gui_debug_draw_values(8, *((unsigned long*)addr));

            debug_to_draw = 0;
            break;
        default:
            debug_to_draw = 0;
            break;
    }
}

//-------------------------------------------------------------------
void gui_debug_kbd_process() {
    switch (kbd_get_clicked_key()) {
    case KEY_DOWN:
        addr-=0xFF;
        debug_to_draw = 2;
        break;
    case KEY_UP:
        addr+=0xFF;
        debug_to_draw = 2;
        break;
    case KEY_LEFT:
        addr-=4;
        debug_to_draw = 2;
        break;
    case KEY_RIGHT:
        addr+=4;
        debug_to_draw = 2;
        break;
    case KEY_SET:
        break;
    }
}

//-------------------------------------------------------------------
