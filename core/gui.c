#include "stdlib.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"
#include "conf.h"
#include "ubasic.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_menu.h"
#include "gui_palette.h"
#include "gui_mbox.h"
#include "gui_reversi.h"
#include "gui_debug.h"
#include "gui_fselect.h"
#include "gui_batt.h"
#include "histogram.h"

//-------------------------------------------------------------------

// forward declarations
//-------------------------------------------------------------------
void dump_memory();

static void gui_draw_histo();

static void gui_draw_osd();
static void gui_draw_splash();
static void gui_draw_histo();

// Menu procs
//-------------------------------------------------------------------
static void gui_show_build_info(int arg);
static void gui_show_memory_info(int arg);
static void gui_draw_palette(int arg);
static void gui_draw_reversi(int arg);
static void gui_test(int arg);
static void gui_draw_debug(int arg);
static void gui_draw_fselect(int arg);
static void gui_load_script(int arg);
static void gui_menuproc_save(int arg);

// Menu callbacks
//-------------------------------------------------------------------
static void cb_step_25();
static void cb_perc();
static void cb_volts();

// Menu definition
//-------------------------------------------------------------------
CMenu script_submenu = { "Script", {
    {"Load script from file...",    MENUITEM_PROC,                      (int*)gui_load_script },
    {"Script shoot delay (.1s)",    MENUITEM_INT|MENUITEM_F_UNSIGNED,   &conf_script_shoot_delay },
    {"Var. a value",                MENUITEM_INT,                       &conf_ubasic_var_a },
    {"Var. b value",                MENUITEM_INT,                       &conf_ubasic_var_b },
    {"Var. c value",                MENUITEM_INT,                       &conf_ubasic_var_c },
    {"<- Back",                     MENUITEM_UP },
    {0}
}};

CMenu misc_submenu = { "Miscellaneous", {
    {"Show build info",             MENUITEM_PROC,  (int*)gui_show_build_info },
    {"Show memory info",            MENUITEM_PROC,  (int*)gui_show_memory_info },
    {"File browser",                MENUITEM_PROC,  (int*)gui_draw_fselect },
    {"Draw palette",                MENUITEM_PROC,  (int*)gui_draw_palette },
    {"MessageBox test",             MENUITEM_PROC,  (int*)gui_test },
    {"GAME: Reversi",               MENUITEM_PROC,  (int*)gui_draw_reversi },
    {"<- Back",                     MENUITEM_UP },
    {0}
}};

CMenu debug_submenu = { "Debug", {
    {"Show PropCases",              MENUITEM_BOOL,                      &debug_propcase_show },
    {"PropCase page",               MENUITEM_INT|MENUITEM_F_UNSIGNED,   &debug_propcase_page },
    {"Show misc. values",           MENUITEM_BOOL,                      &debug_vals_show },
    {"Memory browser",              MENUITEM_PROC,                      (int*)gui_draw_debug },
    {"Dump RAM on ALT +/- press",   MENUITEM_BOOL,                      &confns_enable_memdump },
    {"<- Back",                     MENUITEM_UP },
    {0}
}};


static int voltage_step;
CMenu battery_submenu = { "Battery", {
    {"Voltage MAX",                 MENUITEM_INT|MENUITEM_ARG_ADDR_INC,     &conf_batt_volts_max,   (int)&voltage_step },
    {"Voltage MIN",                 MENUITEM_INT|MENUITEM_ARG_ADDR_INC,     &conf_batt_volts_min,   (int)&voltage_step },
    {"25+ step",                    MENUITEM_BOOL|MENUITEM_ARG_CALLBACK,    &conf_batt_step_25,     (int)cb_step_25 },	
    {"-",                           MENUITEM_TEXT },
    {"Show percent",                MENUITEM_BOOL|MENUITEM_ARG_CALLBACK,    &conf_batt_perc_show,   (int)cb_perc },
    {"Show volts",                  MENUITEM_BOOL|MENUITEM_ARG_CALLBACK,    &conf_batt_volts_show,  (int)cb_volts },
    {"Show icon",                   MENUITEM_BOOL,                          &conf_batt_icon_show },	
    {"<- Back",                     MENUITEM_UP },
    {0}
}};

CMenu root_menu = { "Main", {
    {"Show OSD",                    MENUITEM_BOOL,      &conf_show_osd },
    {"Save RAW",                    MENUITEM_BOOL,      &conf_save_raw },
    {"Show live histogram",         MENUITEM_BOOL,      &conf_show_histo },
    {"Show DOF calculator",         MENUITEM_BOOL,      &conf_show_dof },
    {"Scripting parameters ->",     MENUITEM_SUBMENU,   (int*)&script_submenu },
    {"Battery parameters ->",       MENUITEM_SUBMENU,   (int*)&battery_submenu },
    {"Miscellaneous stuff ->",      MENUITEM_SUBMENU,   (int*)&misc_submenu },
    {"Debug parameters ->",         MENUITEM_SUBMENU,   (int*)&debug_submenu },
    {"Save options now...",         MENUITEM_PROC,      (int*)gui_menuproc_save },
    {0}
}};

void cb_step_25() {
    voltage_step = (conf_batt_step_25)?25:1;
}

void cb_perc() {
    conf_batt_volts_show=0;
}

void cb_volts() {
    conf_batt_perc_show=0;
}

//-------------------------------------------------------------------
static volatile enum Gui_Mode gui_mode;
static volatile int gui_restore;
static volatile int gui_in_redraw;
static int gui_splash = 50;
static char osd_buf[32];

//-------------------------------------------------------------------
void gui_init()
{
    gui_mode = GUI_MODE_NONE;
    gui_restore = 0;
    gui_in_redraw = 0;
    draw_init();

    voltage_step = (conf_batt_step_25)?25:1;
}

//-------------------------------------------------------------------
enum Gui_Mode gui_get_mode() {
    return gui_mode;
}

//-------------------------------------------------------------------
void gui_set_mode(enum Gui_Mode mode) {
    gui_mode = mode;
}

//-------------------------------------------------------------------
void gui_force_restore() {
    gui_restore = gui_in_redraw;
}

//-------------------------------------------------------------------
void gui_redraw()
{
    int i,j;
    enum Gui_Mode gui_mode_old;

    if (gui_splash) {
        if (gui_splash>46) {
            gui_draw_splash();
        } else if (gui_splash==1 && (mode_get()&MODE_MASK) == MODE_PLAY && (gui_mode==GUI_MODE_NONE || gui_mode==GUI_MODE_ALT)) {
            draw_restore();
        }
        --gui_splash;
    }

    gui_draw_histo();

    gui_in_redraw = 1;
    gui_mode_old = gui_mode;

    switch (gui_mode) {
        case GUI_MODE_MENU:
            gui_menu_draw();
            draw_txt_string(20, 14, "<CNF>", MAKE_COLOR(COLOR_ALT_BG, COLOR_FG));
            break;
        case GUI_MODE_ALT:
            gui_draw_osd();
            draw_txt_string(20, 14, "<ALT>", MAKE_COLOR(COLOR_ALT_BG, COLOR_FG));
            break;
        case GUI_MODE_NONE:
            gui_draw_osd();
            break;
        case GUI_MODE_PALETTE:
            gui_palette_draw();
            break;
        case GUI_MODE_MBOX:
            gui_mbox_draw();
            break;
        case GUI_MODE_REVERSI:
            gui_reversi_draw();
            break;
        case GUI_MODE_DEBUG:
            gui_debug_draw();
            break;
        case GUI_MODE_FSELECT:
            gui_fselect_draw();
            break;
        default:
            break;
    }
    
    gui_in_redraw = 0;
    if ((gui_mode_old != gui_mode && (gui_mode_old != GUI_MODE_NONE && gui_mode_old != GUI_MODE_ALT) && (gui_mode != GUI_MODE_MBOX)) || gui_restore) {
        gui_restore = 0;
        if (gui_mode != GUI_MODE_REVERSI)
            draw_restore();
    }
}

//-------------------------------------------------------------------
void gui_kbd_process()
{
    int clicked_key;

    if (kbd_is_key_clicked(KEY_MENU)){
        switch (gui_mode) {
            case GUI_MODE_ALT:
                gui_menu_init(&root_menu);
                gui_mode = GUI_MODE_MENU;
                draw_restore();
                break;
            case GUI_MODE_MENU:
                gui_mode = GUI_MODE_ALT;
                draw_restore();
                break;
            case GUI_MODE_PALETTE:
            case GUI_MODE_REVERSI:
            case GUI_MODE_DEBUG:
                draw_restore();
                gui_mode = GUI_MODE_MENU;
                break;
            case GUI_MODE_FSELECT:
                gui_fselect_kbd_process();
                break;
            default:
                break;
        }
        return;
    }
    
    switch (gui_mode) {
        case GUI_MODE_ALT:
            if (kbd_is_key_clicked(KEY_ERASE)) {
                dump_memory();
            }
            break;
    	case GUI_MODE_MENU:
            gui_menu_kbd_process();
            break;
    	case GUI_MODE_PALETTE:
            gui_palette_kbd_process();
            break;
    	case GUI_MODE_MBOX:
            gui_mbox_kbd_process();
            break;
    	case GUI_MODE_REVERSI:
            gui_reversi_kbd_process();
            break;
    	case GUI_MODE_DEBUG:
            gui_debug_kbd_process();
            break;
    	case GUI_MODE_FSELECT:
            gui_fselect_kbd_process();
            break;
        default:
            break;
    }
}

//-------------------------------------------------------------------
void gui_kbd_enter()
{
    // XXX set custom palette
    gui_mode = GUI_MODE_ALT;
}

//-------------------------------------------------------------------
void gui_kbd_leave()
{
    // XXX restore palette
    ubasic_error = 0;
    draw_restore();
    gui_mode = GUI_MODE_NONE;
}

//-------------------------------------------------------------------
void gui_draw_histo() {
    if (/*(mode_get()&MODE_MASK) == MODE_REC &&*/ (gui_mode==GUI_MODE_NONE || gui_mode==GUI_MODE_ALT) && 
         conf_show_histo && kbd_is_key_pressed(KEY_SHOOT_HALF)) {
        static const int hx=319-HISTO_WIDTH;
        static const int hy=45;
        register unsigned int i, v, threshold;

//        draw_rect(hx-1, hy, hx+HISTO_WIDTH, hy+HISTO_HEIGHT, COLOR_WHITE);
        draw_line(hx, hy, hx+HISTO_WIDTH-1, hy, COLOR_WHITE); //top
        draw_line(hx, hy+HISTO_HEIGHT, hx+HISTO_WIDTH-1, hy+HISTO_HEIGHT, COLOR_WHITE); //bottom
        draw_line(hx-1, hy, hx-1, hy+HISTO_HEIGHT, (under_exposed)?COLOR_RED:COLOR_WHITE); //left
        draw_line(hx+HISTO_WIDTH, hy, hx+HISTO_WIDTH, hy+HISTO_HEIGHT, (over_exposed)?COLOR_RED:COLOR_WHITE); //right

        /* histogram */
        for (i=0; i<HISTO_WIDTH; i++) {
            threshold = histogram[i];

            for (v=1; v<HISTO_HEIGHT; v++)
                draw_pixel(hx+i, hy+HISTO_HEIGHT-v, (v<=threshold)?COLOR_WHITE:COLOR_BG);
        }

        if (under_exposed) {
            draw_filled_ellipse(hx+5, hy+5, 3, 3, MAKE_COLOR(COLOR_RED, COLOR_RED));
        }

        if (over_exposed) {
            draw_filled_ellipse(hx+HISTO_WIDTH-5, hy+5, 3, 3, MAKE_COLOR(COLOR_RED, COLOR_RED));
        }
    }
}

//-------------------------------------------------------------------
static void gui_draw_dof() {
    long zp, av, fp; 
    int r1, r2, hyp, fl;
    
    zp=lens_get_zoom_point();
    if (zp<0) zp=0;
    if (zp>8) zp=8;
    fl=dof_tbl[zp].f;
    
    av=shooting_get_av()-9;
    if (av<0) av=0;
    if (av>9) av=9;
    av=(dof_av_tbl[av]>=dof_tbl[zp].av)?dof_av_tbl[av]:dof_tbl[zp].av;
    
    fp=lens_get_focus_pos();
    hyp=(fl*fl)/(100*6*av);
    r1=(hyp*fp)/(hyp+fp);
    r2=(hyp*fp)/(hyp-fp);

    draw_txt_string(1, 0, "R1/R2:",   MAKE_COLOR(COLOR_BG, COLOR_FG));
    draw_txt_string(1, 1, "DOF/HYP:", MAKE_COLOR(COLOR_BG, COLOR_FG));
    if (r2<0) sprintf(osd_buf, "%d/inf%11s", r1, "");
    else      sprintf(osd_buf, "%d/%d%11s", r1, r2, "");
    osd_buf[12]=0;
    draw_txt_string(1+6, 0, osd_buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
        
    if (r2<0) sprintf(osd_buf, "inf/%d%9s", hyp, "");
    else      sprintf(osd_buf, "%d/%d%9s", r2-r1, hyp, "");
    osd_buf[12]=0;
    draw_txt_string(1+8, 1, osd_buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
}

//-------------------------------------------------------------------

extern long physw_status[3];
extern long GetPropertyCase(long opt_id, void *buf, long bufsize);
//-------------------------------------------------------------------
void gui_draw_osd() {
    unsigned int m, n = 0;
    coord x;
    
    if (!conf_show_osd) return;

    m = mode_get();
    
    if ((m&MODE_MASK) == MODE_REC) {
        m &= MODE_SHOOTING_MASK;
        if (m==MODE_SCN_WATER || m==MODE_SCN_NIGHT || m==MODE_SCN_CHILD || m==MODE_SCN_PARTY || m==MODE_STITCH ||
            m==MODE_SCN_GRASS || m==MODE_SCN_SNOW  || m==MODE_SCN_BEACH || m==MODE_SCN_FIREWORK || m==MODE_VIDEO)
            ++n;

        if (conf_save_raw){
    	    draw_txt_string(40, 3+n, "RAW", MAKE_COLOR(COLOR_BG, COLOR_FG));
    	    ++n;
        }
        if (state_kbd_script_run){
    	    draw_txt_string(40, 3+n, "SCR", MAKE_COLOR(COLOR_BG, COLOR_FG));
    	    ++n;
        }
        if (/*(mode_get()&MODE_MASK) == MODE_REC &&*/ (gui_mode==GUI_MODE_NONE || gui_mode==GUI_MODE_NONE) && 
             conf_show_histo && kbd_is_key_pressed(KEY_SHOOT_HALF)) {
            draw_txt_string(40, 3+n, (under_exposed || over_exposed)?"EXP":"   ", MAKE_COLOR(COLOR_BG, COLOR_FG));
            ++n;
        }

        n=6;
        sprintf(osd_buf, "Z:%ld/%ld%8s", lens_get_zoom_point(), lens_get_zoom_pos(), "");
        osd_buf[8]=0;
        draw_txt_string(35, n++, osd_buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
        sprintf(osd_buf, "F:%ld%8s", lens_get_focus_pos(), "");
        osd_buf[8]=0;
        draw_txt_string(35, n++, osd_buf, MAKE_COLOR(COLOR_BG, COLOR_FG));

        if (conf_show_dof && ( m==MODE_P || m==MODE_M || m==MODE_AV ) && kbd_is_key_pressed(KEY_SHOOT_HALF)){
            gui_draw_dof();
        }
    }

    gui_batt_draw_osd();

    if (debug_vals_show) {
	sprintf(osd_buf, "1:%8lx  ", ~physw_status[2]);
	draw_txt_string(28, 10, osd_buf, MAKE_COLOR(COLOR_BG, COLOR_FG));

	sprintf(osd_buf, "2:%8ld  ", get_tick_count());
	draw_txt_string(28, 11, osd_buf, MAKE_COLOR(COLOR_BG, COLOR_FG));

	sprintf(osd_buf, "3:%d %d ", state_expos_under, state_expos_over);
	draw_txt_string(28, 12, osd_buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
    }

    if (debug_propcase_show){
	static char sbuf[100];
	int r,i, p;

	for (i=0;i<10;i++){
	    r = 0;
	    p = debug_propcase_page*10+i;
	    GetPropertyCase(p, &r, 4);
	    sprintf(sbuf, "%3d: %d              ", p, r);sbuf[20]=0;
	    draw_string(64,16+16*i,sbuf, MAKE_COLOR(COLOR_BG, COLOR_FG));
	}
    }


    if (ubasic_error){
	const char *msg;
        if (ubasic_error >= UBASIC_E_ENDMARK) {
            msg = ubasic_errstrings[UBASIC_E_UNKNOWN_ERROR];
        } else {
	    msg = ubasic_errstrings[ubasic_error];
	}
	sprintf(osd_buf, "uBASIC:%d %s ", ubasic_linenumber(), msg);
	draw_txt_string(0, 0, osd_buf, MAKE_COLOR(COLOR_RED, COLOR_YELLOW));
    }
}

//-------------------------------------------------------------------
void gui_menuproc_save(int arg)
{
    conf_save(1);
}

//-------------------------------------------------------------------
void gui_draw_palette(int arg) {
    draw_restore();
    gui_palette_init();
    gui_mode = GUI_MODE_PALETTE;
}

//-------------------------------------------------------------------
void gui_show_build_info(int arg) {
    gui_mbox_init("*** Build Info ***", "Date:    " __DATE__ "\nTime:    " __TIME__ "\nCamera:  " PLATFORM "\nFW Vers: " PLATFORMSUB, MBOX_FUNC_RESTORE|MBOX_TEXT_LEFT);
}

//-------------------------------------------------------------------
void gui_show_memory_info(int arg) {
    static char buf[128];
    int size, l_size, d;
    char* ptr;

    size = 16;
    while (1) {
        ptr= malloc(size);
        if (ptr) {
            free(ptr);
            size <<= 1;
        } else
            break;
    }

    l_size = size;
    size >>= 1;
    d=1024;
    while (d) {
        ptr = malloc(size);
        if (ptr) {
            free(ptr);
            d = l_size-size;
            if (d<0) d=-d;
            l_size = size;
            size += d>>1;
        } else {
            d = size-l_size;
            if (d<0) d=-d;
            l_size = size;
            size -= d>>1;
        }
        
    }
    
    sprintf(buf, "Free memory: %d bytes", size);
    gui_mbox_init("*** Memory Info ***", buf, 1);
}

//-------------------------------------------------------------------
void gui_draw_reversi(int arg) {
    if ((mode_get()&MODE_MASK) != MODE_PLAY) {
        gui_mbox_init("*** Information ***", "Please switch your camera\nto PLAY mode\nand try again. :)" , MBOX_FUNC_RESTORE|MBOX_TEXT_CENTER);
        return;
    }
    gui_mode = GUI_MODE_REVERSI;
    gui_reversi_init();
}

//-------------------------------------------------------------------
void gui_test(int arg) {
    gui_mbox_init("*** Information ***", "Test multibuttons" , MBOX_FUNC_RESTORE|MBOX_TEXT_CENTER|MBOX_BTN_YES_NO_CANCEL);
}

//-------------------------------------------------------------------
void gui_draw_debug(int arg) {
//    gui_debug_init(0x2510);
    gui_debug_init(0x127E0);
//    gui_debug_init(0x7F5B8);
}

//-------------------------------------------------------------------
void gui_draw_splash() {
    coord w, h, x, y;
    static const char *text[] = {
        "HDK Firmware '" HDK_VERSION "'" , 
        "Build: " __DATE__ " " __TIME__ ,
        "Camera: " PLATFORM " - " PLATFORMSUB };
    int i, l;

    h=sizeof(text)/sizeof(text[0])*FONT_HEIGHT+8;
    w=0;
    for (i=0; i<sizeof(text)/sizeof(text[0]); ++i) {
        l=strlen(text[i]);
        if (l>w) w=l;
    }
    w=w*FONT_WIDTH+10;

    x = (screen_width-w)>>1; y = (screen_height-h)>>1;
    draw_filled_rect(x, y, x+w, y+h, MAKE_COLOR(0xD9, COLOR_WHITE));
    for (i=0; i<sizeof(text)/sizeof(text[0]); ++i) {
        draw_string(x+((w-strlen(text[i])*FONT_WIDTH)>>1), y+i*FONT_HEIGHT+4, text[i], MAKE_COLOR(0xD9, COLOR_WHITE));
    }
}

//-------------------------------------------------------------------
void gui_draw_fselect(int arg) {
    gui_fselect_init("A", NULL);
}

//-------------------------------------------------------------------
static void gui_load_script_selected(const char *fn) {
    if (fn)
        load_script(fn);
}
void gui_load_script(int arg) {
    gui_fselect_init("A", gui_load_script_selected);
}

//-------------------------------------------------------------------
