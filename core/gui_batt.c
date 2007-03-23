#include "stdlib.h"
#include "keyboard.h"
#include "platform.h"
#include "core.h"
#include "conf.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_batt.h"
//-------------------------------------------------------------------

static char osd_buf[32];

//-------------------------------------------------------------------
static long get_batt_average() {
    #define VOLTS_N         100
    static unsigned short   volts[VOLTS_N] = {0};
    static unsigned int     n = 0, rn = 0;
    static unsigned long    volt_aver = 0;

    volt_aver-=volts[n];
    volts[n]=(unsigned short)stat_get_vbatt();
    volt_aver+=volts[n];
    if (++n>rn) rn=n;
    if (n>=VOLTS_N) n=0;
    return volt_aver/rn;
}

//-------------------------------------------------------------------
static unsigned long get_batt_perc() {
    unsigned long v;

    v = get_batt_average();
    if (v>conf_batt_volts_max) v=conf_batt_volts_max;
    if (v<conf_batt_volts_min) v=conf_batt_volts_min;
    return (v-conf_batt_volts_min)*100/(conf_batt_volts_max-conf_batt_volts_min);
}

//-------------------------------------------------------------------
static void gui_batt_draw_icon () {
    static const coord bx=170, by=4;
    coord x;

    // battery icon
    draw_rect(bx-1, by, bx+25+1, by+10, COLOR_WHITE);
    draw_rect(bx-3, by+2, bx-2, by+8, COLOR_WHITE);
    draw_line(bx, by+11, bx+25+2, by+11, COLOR_BLACK);
    draw_line(bx+25+2, by+1, bx+25+2, by+10, COLOR_BLACK);
    
    // battery fill
    x=bx+1+25-(get_batt_perc()/4);
    if (x<=bx) x=bx+1;
    if (x>bx+25+1) x=bx+25+1;
    draw_filled_rect(bx, by+1, x-1, by+9, MAKE_COLOR(COLOR_TRANSPARENT, COLOR_TRANSPARENT));
    draw_filled_rect(x, by+1, bx+25, by+9, MAKE_COLOR(COLOR_WHITE, COLOR_WHITE));
}

//-------------------------------------------------------------------
static void gui_batt_draw_charge(){
    sprintf(osd_buf, "Chg:%3d%%", get_batt_perc());
    osd_buf[8]=0;
    draw_string(screen_width-8*FONT_WIDTH-2, screen_height-64, osd_buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
}

//-------------------------------------------------------------------
static void gui_batt_draw_volts() {
    unsigned long v;

    v = get_batt_average();
    sprintf(osd_buf, "V:%ld.%03ld", v/1000, v%1000);
    osd_buf[7]=0;
    draw_string(screen_width-7*FONT_WIDTH-2, screen_height-64, osd_buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
}

//-------------------------------------------------------------------
void gui_batt_draw_osd() {
    if (conf_batt_perc_show) {
        gui_batt_draw_charge();
    } else if (conf_batt_volts_show) {
        gui_batt_draw_volts();
    }
    
    if (conf_batt_icon_show) {
        gui_batt_draw_icon();
    }
}

//-------------------------------------------------------------------
