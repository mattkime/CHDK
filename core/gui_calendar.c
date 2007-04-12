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
static int cal_year, cal_month;
static coord cal_x, cal_y, cal_w, cal_h;
static char *months[] = {"January", "February", "March", "April",
                            "May", "June", "July", "August",
                            "September", "October", "November", "December"};
static char *days[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};                            
//-------------------------------------------------------------------
static void calendar_goto_today() {
    unsigned long t;
    struct tm *ttm;

    t = time(NULL);
    ttm = localtime(&t);
    cal_year = ttm->tm_year;
    cal_month = ttm->tm_mon;
}

//-------------------------------------------------------------------
static int calendar_days_in_month(int month, int year) {
    switch (month) {
        case 2: 
            return ((year%4==0 && year%100!=0) || year%400==0)?29:28;
        case 4: case 6: case 9: case 11:
            return 30;
        default:
            return 31;
    }
}
//-------------------------------------------------------------------
static int calendar_day_of_week(int day /*1-31*/, int month /*1-12*/, int year) {
    register int a;

    a = (14 - month) / 12;
    year -= a;
    month += a*12 - 2;

    return (((7000 + day + year + year/4 - year/100 + year/400 + 31*month/12) % 7) + 6) % 7;
}

//-------------------------------------------------------------------
static void gui_calendar_initial_draw() {
    draw_filled_rect(0, 0, screen_width-1, screen_height-1, MAKE_COLOR(SCREEN_COLOR, SCREEN_COLOR));
    draw_txt_string(1, 0, "Today: ", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
    draw_rect(cal_x-1, cal_y-1, cal_x+cal_w, cal_y+cal_h, COLOR_WHITE);
    draw_rect(cal_x-3, cal_y-3, cal_x+cal_w+2, cal_y+cal_h+2, COLOR_WHITE);
    draw_line(cal_x-1, cal_y+FONT_HEIGHT+8, cal_x+cal_w, cal_y+FONT_HEIGHT+8, COLOR_WHITE);
    
}

//-------------------------------------------------------------------
void gui_calendar_init() {
    calendar_goto_today();
    cal_w = FONT_WIDTH*4*7;
    cal_h = 4+FONT_HEIGHT+4+4+FONT_HEIGHT+4+(FONT_HEIGHT+4)*5;
    cal_x = (screen_width-cal_w)/2;
    cal_y = (screen_height-FONT_HEIGHT-cal_h)/2;
    gui_calendar_initial_draw();
    need_redraw = 1;
}

//-------------------------------------------------------------------
void gui_calendar_kbd_process() {
    switch (kbd_get_clicked_key()) {
        case KEY_UP:
            if (cal_year>1) --cal_year;
            need_redraw = 1;
            break;
        case KEY_DOWN:
            ++cal_year;
            need_redraw = 1;
            break;
        case KEY_LEFT:
            if (--cal_month<1) cal_month=12;
            need_redraw = 1;
            break;
        case KEY_RIGHT:
            if (++cal_month>12) cal_month=1;
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
    int x, y;
    static char str[16];
    int w, d, i;

    if (need_redraw) {
        need_redraw = 0;
        
        i = strlen(months[cal_month]);
        x = (cal_w-FONT_WIDTH-FONT_WIDTH*4-FONT_WIDTH-i*FONT_WIDTH)/2;
        y = cal_y+4;
        draw_string(cal_x+x, y, months[cal_month], MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
        
        sprintf(str, "%04d", cal_year);
        draw_string(cal_x+cal_w-FONT_WIDTH-FONT_WIDTH*4, y, str, MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));

        d = calendar_days_in_month(cal_month+1, cal_year);
        w = calendar_day_of_week(1, cal_month+1, cal_year);

        y += FONT_HEIGHT+4+4;
        for (x=cal_x+FONT_WIDTH/2, i=0; i<7; x+=FONT_WIDTH*4, ++i) {
            draw_string(x, y, days[i], MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
        }

        y += FONT_HEIGHT+4;
        for (x=0; x<w; ++x) {
            draw_txt_string(cal_x+x*FONT_WIDTH*4, y, "    ", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
        }
        
        for (i=1; i<=d; ++i) {
            sprintf(str, " %2d ", i);
            draw_txt_string(cal_x+x*FONT_WIDTH*4, y, str, MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            
            if (++x>6) {
              x=0;
              y += FONT_HEIGHT+4;
            }
        }

        for (; x<7; ++x) {
            draw_txt_string(cal_x+x*FONT_WIDTH*4, y, "    ", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
        }
    }
}

