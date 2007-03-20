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
#include "histogram.h"

//-------------------------------------------------------------------

// forward declarations
//-------------------------------------------------------------------
static void gui_draw_histo();

static void gui_draw_osd();
static void gui_draw_splash();
static void gui_draw_histo();

static void gui_show_build_info();
static void gui_show_memory_info();
static void gui_draw_palette();
static void gui_draw_reversi();
static void gui_test();
static void gui_draw_debug();
static void gui_draw_fselect();
static void gui_load_script();

static void gui_menuproc_save();

// Menu definition
//-------------------------------------------------------------------
CMenu script_submenu = { "Script", {
    {"Load script from file...", MENUITEM_PROC, (int*)gui_load_script },
    {"Script shoot delay (.1s)", MENUITEM_INT|MENUITEM_F_UNSIGNED, &conf_script_shoot_delay },
    {"Var. a value", MENUITEM_INT, &conf_ubasic_var_a },
    {"Var. b value", MENUITEM_INT, &conf_ubasic_var_b },
    {"Var. c value", MENUITEM_INT, &conf_ubasic_var_c },
    {"<- Back", MENUITEM_UP, NULL },
    {0}
}};

CMenu misc_submenu = { "Miscellaneous", {
    {"Show build info", MENUITEM_PROC, (int*)gui_show_build_info },
    {"Show memory info", MENUITEM_PROC, (int*)gui_show_memory_info },
    {"File browser", MENUITEM_PROC, (int*)gui_draw_fselect },
    {"Draw palette", MENUITEM_PROC, (int*)gui_draw_palette },
    {"MessageBox test", MENUITEM_PROC, (int*)gui_test },
    {"GAME: Reversi", MENUITEM_PROC, (int*)gui_draw_reversi },
    {"<- Back", MENUITEM_UP, NULL },
    {0}
}};

CMenu m1_submenu = { "Menu 1", {
    {"Item 1", MENUITEM_PROC, NULL },
    {"Item 2", MENUITEM_PROC, NULL },
    {"<- Back", MENUITEM_UP, NULL },
    {0}
}};

CMenu m2_submenu = { "Menu 2", {
    {"Item 1", MENUITEM_PROC, NULL },
    {"Item 2", MENUITEM_PROC, NULL },
    {"Item 3", MENUITEM_PROC, NULL },
    {"Item 4", MENUITEM_PROC, NULL },
    {"Item 5", MENUITEM_PROC, NULL },
    {"Item 6", MENUITEM_PROC, NULL },
    {"Item 7", MENUITEM_PROC, NULL },
    {"Item 8", MENUITEM_PROC, NULL },
    {"Item 9", MENUITEM_PROC, NULL },
    {"Item 10", MENUITEM_PROC, NULL },
    {"Item 11", MENUITEM_PROC, NULL },
    {"Item 12", MENUITEM_PROC, NULL },
    {"<- Back", MENUITEM_UP, NULL },
    {0}
}};

CMenu debug_submenu = { "Debug", {
    {"Show PropCases", MENUITEM_BOOL, &debug_propcase_show },
    {"PropCase page", MENUITEM_INT, &debug_propcase_page },
    {"Show misc. values", MENUITEM_BOOL, &debug_vals_show },
    {"Memory browser", MENUITEM_PROC, (int*)gui_draw_debug },
    {"Menu 1", MENUITEM_SUBMENU, (int*)&m1_submenu },
    {"Menu 2", MENUITEM_SUBMENU, (int*)&m2_submenu },
    {"<- Back", MENUITEM_UP, NULL },
    {0}
}};

CMenu root_menu = { "Main", {
    {"Show OSD", MENUITEM_BOOL, &conf_show_osd },
    {"Save RAW", MENUITEM_BOOL, &conf_save_raw },
    {"Show live histogram", MENUITEM_BOOL, &conf_show_histo },
    {"Scripting parameters ->", MENUITEM_SUBMENU, (int*)&script_submenu },
    {"Miscellaneous stuff ->", MENUITEM_SUBMENU, (int*)&misc_submenu },
    {"Debug parameters ->", MENUITEM_SUBMENU, (int*)&debug_submenu },
    {"Save options now...", MENUITEM_PROC, (int*)gui_menuproc_save },
    {0}
}};

//-------------------------------------------------------------------
static volatile enum Gui_Mode gui_mode;
static volatile int gui_restore;
static volatile int gui_in_redraw;
static int gui_splash = 50;
static int charge_max, charge_min;

//-------------------------------------------------------------------
void gui_init()
{
    gui_mode = GUI_MODE_NONE;
    gui_restore = 0;
    gui_in_redraw = 0;
    charge_min = get_vbatt_min();
    charge_max = get_vbatt_max();
    draw_init();
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
        //          {
        //              void (*f)(long a, long b, long c) = 0xFFC1408C;
        //              long p = 0;
        //              f(40,&p,2);
        //          }
        //          lens_set_focus_pos(2000);
        //          makedump();
        //          shooting_set_tv_rel(2);
        //          shooting_set_av_rel(2);
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
    if (/*(mode_get()&MODE_MASK) == MODE_REC &&*/ (gui_mode==GUI_MODE_NONE || gui_mode==GUI_MODE_NONE) && 
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
static long calc_average_vbatt() {
    #define VOLTS_N 		100
    static unsigned short	volts[VOLTS_N] = {0};
    static unsigned int   	n = 0, rn = 0;
    static unsigned long	volt_aver = 0;

    volt_aver-=volts[n];
    volts[n]=(unsigned short)stat_get_vbatt();
    volt_aver+=volts[n];
    if (++n>rn) rn=n;
    if (n>=VOLTS_N) n=0;
    return volt_aver/rn;
}

//-------------------------------------------------------------------

extern long physw_status[3];
extern long GetPropertyCase(long opt_id, void *buf, long bufsize);
static char osd_buf[32];
//-------------------------------------------------------------------
void gui_draw_osd() {
    unsigned int i, n = 0;
    unsigned long v;
    static const coord bx=170, by=4;
    coord x;
    
    if (!conf_show_osd) return;

    i = mode_get();
    if ((i&MODE_MASK) == MODE_REC) {
        i &= MODE_SHOOTING_MASK;
        if (i==MODE_SCN_WATER || i==MODE_SCN_NIGHT || i==MODE_SCN_CHILD || i==MODE_SCN_PARTY || i==MODE_STITCH ||
            i==MODE_SCN_GRASS || i==MODE_SCN_SNOW  || i==MODE_SCN_BEACH || i==MODE_SCN_FIREWORK || i==MODE_VIDEO)
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
    }

    n=6;
    if ((mode_get()&MODE_MASK) == MODE_REC) {
        sprintf(osd_buf, "Z:%ld/%ld%8s", lens_get_zoom_point(), lens_get_zoom_pos(), "");
        osd_buf[8]=0;
        draw_txt_string(35, n++, osd_buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
        sprintf(osd_buf, "F:%ld%8s", lens_get_focus_pos(), "");
        osd_buf[8]=0;
        draw_txt_string(35, n++, osd_buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
    }

    v = calc_average_vbatt();
    sprintf(osd_buf, "V:%ld.%03ld", v/1000, v%1000);
    osd_buf[8]=0;
    draw_string(screen_width-7*FONT_WIDTH-2, screen_height-64, osd_buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
    // battery icon
    draw_rect(bx-1, by, bx+25+1, by+10, COLOR_WHITE);
    draw_rect(bx-3, by+2, bx-2, by+8, COLOR_WHITE);
    draw_line(bx, by+11, bx+25+2, by+11, COLOR_BLACK);
    draw_line(bx+25+2, by+1, bx+25+2, by+10, COLOR_BLACK);
    // battery fill
    if (v>charge_max) v=charge_max;
    if (v<charge_min) v=charge_min; else v-=charge_min;
    x=bx+1+25-(v*25/(charge_max-charge_min));
    if (x<=bx) x=bx+1;
    if (x>bx+25+1) x=bx+25+1;
    draw_filled_rect(bx, by+1, x-1, by+9, MAKE_COLOR(COLOR_TRANSPARENT, COLOR_TRANSPARENT));
    draw_filled_rect(x, by+1, bx+25, by+9, MAKE_COLOR(COLOR_WHITE, COLOR_WHITE));


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
void gui_menuproc_save()
{
    conf_save(1);
}

//-------------------------------------------------------------------
void gui_draw_palette() {
    draw_restore();
    gui_palette_init();
    gui_mode = GUI_MODE_PALETTE;
}

//-------------------------------------------------------------------
void gui_show_build_info() {
    gui_mbox_init("*** Build Info ***", "Date:    " __DATE__ "\nTime:    " __TIME__ "\nCamera:  " PLATFORM "\nFW Vers: " PLATFORMSUB, MBOX_FUNC_RESTORE|MBOX_TEXT_LEFT);
}

//-------------------------------------------------------------------
void gui_show_memory_info() {
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
void gui_draw_reversi() {
    if ((mode_get()&MODE_MASK) != MODE_PLAY) {
        gui_mbox_init("*** Information ***", "Please switch your camera\nto PLAY mode\nand try again. :)" , MBOX_FUNC_RESTORE|MBOX_TEXT_CENTER);
        return;
    }
    gui_mode = GUI_MODE_REVERSI;
    gui_reversi_init();
}

//-------------------------------------------------------------------
void gui_test() {
    gui_mbox_init("*** Information ***", "Test multibuttons" , MBOX_FUNC_RESTORE|MBOX_TEXT_CENTER|MBOX_BTN_YES_NO_CANCEL);
}

//-------------------------------------------------------------------
void gui_draw_debug() {
//    gui_debug_init(0x2510);
    gui_debug_init(0x127E0);
//    gui_debug_init(0x7F5B8);
}

//-------------------------------------------------------------------
void gui_draw_splash() {
    coord w, h, x, y;
    static const char *text[] = {"HDK Firmware", 
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
        draw_string(x+((w-strlen(text[i])*FONT_WIDTH)>>1)+5, y+i*FONT_HEIGHT+4, text[i], MAKE_COLOR(0xD9, COLOR_WHITE));
    }
}

//-------------------------------------------------------------------
void gui_draw_fselect() {
    gui_fselect_init("A", NULL);
}

//-------------------------------------------------------------------
static void gui_load_script_selected(const char *fn) {
    if (fn)
        load_script(fn);
}
void gui_load_script() {
    gui_fselect_init("A", gui_load_script_selected);
}

//-------------------------------------------------------------------
