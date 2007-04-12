#include "stdlib.h"
#include "keyboard.h"
#include "platform.h"
#include "core.h"
#include "conf.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_calendar.h"

//-------------------------------------------------------------------
#define SCREEN_COLOR            0xDB

//-------------------------------------------------------------------
static int need_redraw;
static int year, month;

//-------------------------------------------------------------------
static void calendar_goto_today() {
    unsigned long t;
    struct tm *ttm;

    t = time(NULL);
    ttm = localtime(&t);
    year = ttm->tm_year;
    month = ttm->tm_mon;
}

//-------------------------------------------------------------------
static int calendar_calc() {
    int t_month=month+1, t_year=year, days;
    int a, res;

    a = (14 - t_month) / 12;
    t_year = t_year - a;
    t_month = t_month + a*12 - 2;

    switch (month) {
        case 2: 
            days = ((year%4==0 && year%100!=0) || year%400==0)?29:28;
            break;
        case 4: case 6: case 9: case 11:
            days = 30;
            break;
        default:
            days = 31;
            break;
    }

    res = (7000 + (1 + t_year + t_year/4 - t_year/100 + t_year/400 + 31*t_month/12)) % 7;
    return (days<<8)|res;
}
//-------------------------------------------------------------------
void gui_calendar_init() {
    calendar_goto_today();
    need_redraw = 1;
}

//-------------------------------------------------------------------
void gui_calendar_kbd_process() {
    switch (kbd_get_clicked_key()) {
        case KEY_UP:
            if (year>1) --year;
            need_redraw = 1;
            break;
        case KEY_DOWN:
            ++year;
            need_redraw = 1;
            break;
        case KEY_LEFT:
            if (--month<1) month=12;
            need_redraw = 1;
            break;
        case KEY_RIGHT:
            if (++month>12) month=1;
            need_redraw = 1;
            break;
        case KEY_ERASE:
            calendar_goto_today();
            need_redraw = 1;
            break;
    }
}

//-------------------------------------------------------------------
void gui_calendar_draw() {
    int y, x;
    static char str[16];
    int w, d, i;

    if (need_redraw) {
        need_redraw = 0;

        draw_filled_rect(0, 0, screen_width-1, screen_height-1, MAKE_COLOR(SCREEN_COLOR, SCREEN_COLOR));

        d = calendar_calc();
        w = d&0xFF;
        d >>=8;

        x=w; y=1;

        for (i=1; i<=d; ++i) {
            sprintf(str, "%2d", i);
            draw_txt_string(x*4, y*2, str, MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            
            if (++x>6) {
              x=0; ++y;
            }
        }


    }
}

