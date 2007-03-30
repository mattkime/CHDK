#include "stdlib.h"
#include "keyboard.h"
#include "platform.h"
#include "histogram.h"
#include "core.h"
#include "conf.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_batt.h"
#include "gui_osd.h"


//-------------------------------------------------------------------
typedef struct {
    char    *title;
    OSD_pos *pos;
    OSD_pos size;
} OSD_elem;

static OSD_elem osd[]={
    {"Histogram",       &conf.histo_pos,        {HISTO_WIDTH, HISTO_HEIGHT}     },
    {"DOF calc",        &conf.dof_pos,          {17*FONT_WIDTH, 2*FONT_HEIGHT}  },
    {"RAW/SCR/EXP",     &conf.mode_state_pos,   {3*FONT_WIDTH, 3*FONT_HEIGHT}   },
    {"Misc values",     &conf.values_pos,       {8*FONT_WIDTH, 3*FONT_HEIGHT}   },
    {"Batt icon",       &conf.batt_icon_pos,    {28, 12}                        },
    {"Batt text",       &conf.batt_txt_pos,     {8*FONT_WIDTH, FONT_HEIGHT}     },
    {0}
};
static int osd_to_draw;
static int curr_item;
static char osd_buf[40];
static int step;

//-------------------------------------------------------------------
void gui_osd_init() {
    osd_to_draw = 1;
    curr_item = 0;
    step = 10;
    draw_restore();
}

//-------------------------------------------------------------------
void gui_osd_draw() {
    if (osd_to_draw) {
        int i;
        draw_restore();
        gui_osd_draw_histo();
        gui_osd_draw_dof();
        gui_batt_draw_osd();
        gui_osd_draw_state();
        gui_osd_draw_values();
        for (i=1; i<=2; ++i) {
            draw_rect((osd[curr_item].pos->x>=i)?osd[curr_item].pos->x-i:0, (osd[curr_item].pos->y>=i)?osd[curr_item].pos->y-i:0, 
                      osd[curr_item].pos->x+osd[curr_item].size.x+i-1, osd[curr_item].pos->y+osd[curr_item].size.y+i-1,
                      COLOR_GREEN);
        }
        sprintf(osd_buf, " %s:  x:%d y:%d s:%d ", osd[curr_item].title, osd[curr_item].pos->x, osd[curr_item].pos->y, step);
        draw_string(0, (osd[curr_item].pos->x<strlen(osd_buf)*FONT_WIDTH+4 && osd[curr_item].pos->y<FONT_HEIGHT+4)?screen_height-FONT_HEIGHT:0,
                    osd_buf, MAKE_COLOR(COLOR_RED, COLOR_WHITE));
        osd_to_draw = 0;
    }
}

//-------------------------------------------------------------------
void gui_osd_kbd_process() {
    switch (kbd_get_clicked_key()) {
    case KEY_LEFT:
        if (osd[curr_item].pos->x > 0) {
            osd[curr_item].pos->x-=(osd[curr_item].pos->x>=step)?step:osd[curr_item].pos->x;
            osd_to_draw = 1;
        }
        break;
    case KEY_RIGHT:
        if (osd[curr_item].pos->x < screen_width-osd[curr_item].size.x) {
            osd[curr_item].pos->x+=(screen_width-osd[curr_item].size.x-osd[curr_item].pos->x>step)?step:screen_width-osd[curr_item].size.x-osd[curr_item].pos->x;
            osd_to_draw = 1;
        }
        break;
    case KEY_UP:
        if (osd[curr_item].pos->y > 0) {
            osd[curr_item].pos->y-=(osd[curr_item].pos->y>=step)?step:osd[curr_item].pos->y;
            osd_to_draw = 1;
        }
        break;
    case KEY_DOWN:
        if (osd[curr_item].pos->y < screen_height-osd[curr_item].size.y) {
            osd[curr_item].pos->y+=(screen_height-osd[curr_item].size.y-osd[curr_item].pos->y>step)?step:screen_height-osd[curr_item].size.y-osd[curr_item].pos->y;
            osd_to_draw = 1;
        }
        break;
    case KEY_SET:
        ++curr_item;
        if (!osd[curr_item].pos) 
            curr_item = 0;
        osd_to_draw = 1;
        break;
    case KEY_DISPLAY:
        step=(step==1)?10:1;
        osd_to_draw = 1;
        break;
    }
}

//-------------------------------------------------------------------
static void gui_osd_draw_single_histo(int hist, coord x, coord y, int small) {
    register unsigned int i, v, threshold;
    register color cl, cl_over, cl_bg=conf.histo_color>>8;
    coord w=HISTO_WIDTH, h=HISTO_HEIGHT;

    switch (hist) {
        case HISTO_R: 
            cl=COLOR_RED; 
            break;
        case HISTO_G: 
            cl=COLOR_GREEN; 
            break;
        case HISTO_B: 
            cl=((mode_get()&MODE_MASK) == MODE_REC)?0xDF:0xCC; 
            break;
        case HISTO_RGB:
        case HISTO_Y:
        default:
            cl=conf.histo_color; 
            break;
    }

    if (small) {
        h>>=1; w>>=1;
        for (i=0; i<w; ++i) {
            threshold = (histogram[hist][i<<1]+histogram[hist][(i<<1)+1])>>2;

            for (v=1; v<h-1; ++v)
                draw_pixel(x+i, y+h-v, (v<=threshold)?cl:cl_bg);
            cl_over = (threshold==h && conf.show_overexp)?COLOR_RED:cl;
            for (; v<h; ++v)
                draw_pixel(x+i, y+h-v, (v<=threshold)?cl_over:cl_bg);
        }
    } else {
        for (i=0; i<w; ++i) {
            threshold = histogram[hist][i];

            for (v=1; v<h-3; ++v)
                draw_pixel(x+i, y+h-v, (v<=threshold)?cl:cl_bg);
            cl_over = (threshold==h && conf.show_overexp)?COLOR_RED:cl;
            for (; v<h; ++v)
                draw_pixel(x+i, y+h-v, (v<=threshold)?cl_over:cl_bg);
        }
    }
      
    draw_rect(x-1, y, x+w, y+h, COLOR_WHITE);

}

//-------------------------------------------------------------------
void gui_osd_draw_histo() {
/*
    // "zebra"
    register unsigned int i;
    unsigned char *img;

    img=vid_get_viewport_fb();
    for (i=0;i<screen_size;++i) {
        draw_pixel(i%360, i/360, (img[i*3+1]==255)?COLOR_RED:((img[i*3+1]==0)?COLOR_RED:COLOR_TRANSPARENT));
    }
    return;
// */

    switch (conf.histo_layout) {
        case OSD_HISTO_LAYOUT_Y:
                gui_osd_draw_single_histo(HISTO_Y, conf.histo_pos.x, conf.histo_pos.y, 0);
                break;
        case OSD_HISTO_LAYOUT_A_Y:
                gui_osd_draw_single_histo(HISTO_RGB, conf.histo_pos.x, conf.histo_pos.y, 0);
                gui_osd_draw_single_histo(HISTO_Y, conf.histo_pos.x, conf.histo_pos.y+HISTO_HEIGHT, 0);
                break;
        case OSD_HISTO_LAYOUT_R_G_B:
                gui_osd_draw_single_histo(HISTO_R, conf.histo_pos.x, conf.histo_pos.y, 0);
                gui_osd_draw_single_histo(HISTO_G, conf.histo_pos.x, conf.histo_pos.y+HISTO_HEIGHT, 0);
                gui_osd_draw_single_histo(HISTO_B, conf.histo_pos.x, conf.histo_pos.y+HISTO_HEIGHT*2, 0);
                break;
        case OSD_HISTO_LAYOUT_A_yrgb:
                gui_osd_draw_single_histo(HISTO_RGB, conf.histo_pos.x, conf.histo_pos.y, 0);
                gui_osd_draw_single_histo(HISTO_Y, conf.histo_pos.x, conf.histo_pos.y+HISTO_HEIGHT, 1);
                gui_osd_draw_single_histo(HISTO_R, conf.histo_pos.x+HISTO_WIDTH/2+1, conf.histo_pos.y+HISTO_HEIGHT, 1);
                gui_osd_draw_single_histo(HISTO_G, conf.histo_pos.x, conf.histo_pos.y+HISTO_HEIGHT+HISTO_HEIGHT/2, 1);
                gui_osd_draw_single_histo(HISTO_B, conf.histo_pos.x+HISTO_WIDTH/2+1, conf.histo_pos.y+HISTO_HEIGHT+HISTO_HEIGHT/2, 1);
                break;
        case OSD_HISTO_LAYOUT_Y_argb:
                gui_osd_draw_single_histo(HISTO_Y, conf.histo_pos.x, conf.histo_pos.y, 0);
                gui_osd_draw_single_histo(HISTO_RGB, conf.histo_pos.x, conf.histo_pos.y+HISTO_HEIGHT, 1);
                gui_osd_draw_single_histo(HISTO_R, conf.histo_pos.x+HISTO_WIDTH/2+1, conf.histo_pos.y+HISTO_HEIGHT, 1);
                gui_osd_draw_single_histo(HISTO_G, conf.histo_pos.x, conf.histo_pos.y+HISTO_HEIGHT+HISTO_HEIGHT/2, 1);
                gui_osd_draw_single_histo(HISTO_B, conf.histo_pos.x+HISTO_WIDTH/2+1, conf.histo_pos.y+HISTO_HEIGHT+HISTO_HEIGHT/2, 1);
                break;
        case OSD_HISTO_LAYOUT_A:
        default:
                gui_osd_draw_single_histo(HISTO_RGB, conf.histo_pos.x, conf.histo_pos.y, 0);
                break;
    }

    if (conf.histo_layout != OSD_HISTO_LAYOUT_R_G_B) {
        if (under_exposed && conf.show_overexp) {
            draw_filled_ellipse(conf.histo_pos.x+5, conf.histo_pos.y+5, 3, 3, MAKE_COLOR(COLOR_RED, COLOR_RED));
        }

        if (over_exposed && conf.show_overexp) {
            draw_filled_ellipse(conf.histo_pos.x+HISTO_WIDTH-5, conf.histo_pos.y+5, 3, 3, MAKE_COLOR(COLOR_RED, COLOR_RED));
        }
    }

    if (histo_magnification) {
        sprintf(osd_buf, " %d.%02dx ", histo_magnification/1000, histo_magnification/10%100);
        draw_string(conf.histo_pos.x, conf.histo_pos.y-FONT_HEIGHT, osd_buf, conf.histo_color);
    } else {
        draw_filled_rect(conf.histo_pos.x, conf.histo_pos.y-FONT_HEIGHT, conf.histo_pos.x+8*FONT_WIDTH, conf.histo_pos.y-1, MAKE_COLOR(COLOR_TRANSPARENT, COLOR_TRANSPARENT));
    }
}

//-------------------------------------------------------------------
static void sprintf_dist(char *buf, float dist) {
// length of printed string is always 4
    if (dist<0) {
        sprintf(buf, " inf");
//    } else if (dist<1000) {
//        sprintf(buf, ".%03d", (int)dist);
    } else if (dist<10000) {
        sprintf(buf, "%d.%02d", (int)(dist/1000), (int)(dist/10)%100);
    } else if (dist<100000) {
        sprintf(buf, "%02d.%d", (int)(dist/1000), (int)(dist/100)%10);
    } else {
        sprintf(buf, "%4d", (int)(dist/1000));
    }
}

//-------------------------------------------------------------------
static int get_fl() {
    long zp;

    zp=lens_get_zoom_point();
    if (zp<0) zp=0;
    if (zp>=dof_tbl_size) zp=dof_tbl_size-1;
    return dof_tbl[zp].f;
}

//-------------------------------------------------------------------
void gui_osd_draw_dof() {
    long av, fp; 
    float r1, r2, hyp, fl;
    
    fl=get_fl();
    
    av=shooting_get_real_av();
    
    fp=lens_get_focus_pos();
    hyp=(fl*fl)/(10*6*av);
    r1=(hyp*fp)/(hyp+fp);
    r2=(hyp*fp)/(hyp-fp);

    draw_string(conf.dof_pos.x, conf.dof_pos.y, "R1/R2:", conf.osd_color);
    sprintf_dist(osd_buf, r1);
    osd_buf[4]='/';
    sprintf_dist(osd_buf+5, r2);
    draw_string(conf.dof_pos.x+6*FONT_WIDTH, conf.dof_pos.y, osd_buf, conf.osd_color);
        
    draw_string(conf.dof_pos.x, conf.dof_pos.y+FONT_HEIGHT, "DOF/HYP:", conf.osd_color);
    sprintf_dist(osd_buf, r2-r1);
    osd_buf[4]='/';
    sprintf_dist(osd_buf+5, hyp);
    draw_string(conf.dof_pos.x+8*FONT_WIDTH, conf.dof_pos.y+FONT_HEIGHT, osd_buf, conf.osd_color);
}

//-------------------------------------------------------------------
void gui_osd_draw_state() {
    int n=0, gui_mode=gui_get_mode();

    if (conf.save_raw || gui_mode==GUI_MODE_OSD){
        draw_string(conf.mode_state_pos.x, conf.mode_state_pos.y, "RAW", conf.osd_color);
        n+=FONT_HEIGHT;
    }
    if (state_kbd_script_run || gui_mode==GUI_MODE_OSD){
        draw_string(conf.mode_state_pos.x, conf.mode_state_pos.y+n, "SCR", conf.osd_color);
        n+=FONT_HEIGHT;
    }
    if (((gui_mode==GUI_MODE_NONE || gui_mode==GUI_MODE_ALT) && conf.show_histo && conf.show_overexp && kbd_is_key_pressed(KEY_SHOOT_HALF)) || gui_mode==GUI_MODE_OSD) {
        draw_string(conf.mode_state_pos.x, conf.mode_state_pos.y+n, (under_exposed || over_exposed)?"EXP":"   ", conf.osd_color);
    }
}
//-------------------------------------------------------------------
void gui_osd_draw_values() {
    int av=shooting_get_real_av(), fl=get_fl()*10/dof_tbl[0].f;

    sprintf(osd_buf, "Z:%ld/%d.%dx%8s", lens_get_zoom_point(), fl/10, fl%10, "");
    osd_buf[8]=0;
    draw_string(conf.values_pos.x, conf.values_pos.y, osd_buf, conf.osd_color);

    sprintf(osd_buf, "F:%ld%8s", lens_get_focus_pos(), "");
    osd_buf[8]=0;
    draw_string(conf.values_pos.x, conf.values_pos.y+FONT_HEIGHT, osd_buf, conf.osd_color);

    sprintf(osd_buf, "Av:%d.%02d ", av/100, av%100);
    osd_buf[8]=0;
    draw_string(conf.values_pos.x, conf.values_pos.y+FONT_HEIGHT*2, osd_buf, conf.osd_color);
}
//-------------------------------------------------------------------
//-------------------------------------------------------------------
