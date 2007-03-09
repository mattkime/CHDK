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

//-------------------------------------------------------------------
#define HISTO

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

static void gui_menuproc_save();

// Menu definition
//-------------------------------------------------------------------
CMenuItem script_submenu[] = {
    {"*** Script ***", MENUITEM_INFO, 0 },
    {"Script shoot delay (.1s)", MENUITEM_INT|MENUITEM_F_UNSIGNED, &conf_script_shoot_delay },
    {"Var. a value", MENUITEM_INT, &conf_ubasic_var_a },
    {"Var. b value", MENUITEM_INT, &conf_ubasic_var_b },
    {"Var. c value", MENUITEM_INT, &conf_ubasic_var_c },
    {"<- Back", MENUITEM_UP, NULL },
    {0}
};

CMenuItem misc_submenu[] = {
    {"*** Miscellaneous ***", MENUITEM_INFO, 0 },
    {"Show build info", MENUITEM_PROC, (int*)gui_show_build_info },
    {"Show memory info", MENUITEM_PROC, (int*)gui_show_memory_info },
    {"Draw palette", MENUITEM_PROC, (int*)gui_draw_palette },
    {"MessageBox test", MENUITEM_PROC, (int*)gui_test },
    {"GAME: Reversi", MENUITEM_PROC, (int*)gui_draw_reversi },
    {"<- Back", MENUITEM_UP, NULL },
    {0}
};

CMenuItem debug_submenu[] = {
    {"*** Debug ***", MENUITEM_INFO, 0 },

    {"Show PropCases", MENUITEM_BOOL, &debug_propcase_show },
    {"PropCase page", MENUITEM_INT, &debug_propcase_page },
    {"Show misc. values", MENUITEM_BOOL, &debug_vals_show },
    {"Memory browser", MENUITEM_PROC, (int*)gui_draw_debug },
    {"<- Back", MENUITEM_UP, NULL },
    {0}
};

CMenuItem root_menu[] = {
    {"*** Main ***", MENUITEM_INFO, 0 },
    {"Show OSD", MENUITEM_BOOL, &conf_show_osd },
    {"Save RAW", MENUITEM_BOOL, &conf_save_raw },
#ifdef HISTO
    {"Show live histo", MENUITEM_BOOL, &conf_show_histo },
#endif
    {"Scripting parameters ->", MENUITEM_SUBMENU, (int*)script_submenu },
    {"Miscellaneous stuff ->", MENUITEM_SUBMENU, (int*)misc_submenu },
    {"Debug parameters ->", MENUITEM_SUBMENU, (int*)debug_submenu },
    {"Save options now...", MENUITEM_PROC, (int*)gui_menuproc_save },
    {0}
};

//-------------------------------------------------------------------
static volatile enum Gui_Mode gui_mode;
static volatile int gui_restore;
static volatile int gui_in_redraw;
static int gui_splash = 50;

//-------------------------------------------------------------------
void gui_init()
{
    gui_mode = GUI_MODE_NONE;
    gui_restore = 0;
    gui_in_redraw = 0;
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

#if 0
    {
	static char sbuf[100];
	volatile long *si = 0x7dd0;
	extern int taskop_txt_p;
	extern char taskop_txt[6][32];
	long (*f)(long prop, void*p, long size);
	int r,i;

	f = 0xFFC141A8;
//	i = 0;
//	f(conf_ubasic_var_a, &i, 4);
/*
1 - effect
5 - color temp
9 - exp. 
14 - drive timeout
21 - iso value 50..400
24 - image size
23 - quality
39 - aperture
40 - time
69 - tv result

*/
// 39 - aperture
// 40 - exp time
// 65 - focus
// 69 - calc. exp time

	for (i=0;i<10;i++){
	    r = 0;
	    f(conf_ubasic_var_a+i, &r, 4);
	    sprintf(sbuf, "%3d: %d               ", conf_ubasic_var_a+i,r);sbuf[20]=0;
	    draw_string(64,16+16*i,sbuf, MAKE_COLOR(COLOR_BG, COLOR_FG));
	
	}
/*
	sprintf(sbuf, "d1: %d               ", i);sbuf[20]=0;
	draw_string(64,16,sbuf);

	sprintf(sbuf, "d1: %d               ", (short)i);sbuf[20]=0;
	draw_string(64,32,sbuf);

	sprintf(sbuf, "d1: %x               ", i);sbuf[20]=0;
	draw_string(64,48,sbuf);
*/

//	sprintf(sbuf, "av: %d               ", shooting_get_av());sbuf[20]=0;
//	draw_string(64,64+16,sbuf);

//	sprintf(sbuf, "w: %d               ", si[2]);sbuf[20]=0;
//	draw_string(64,64+32,sbuf);

//	sprintf(sbuf, "w: %d               ", si[3]);sbuf[20]=0;
//	draw_string(64,64+48,sbuf);

//	for (i=0;i<6;i++){
//	    sprintf(sbuf, "%s                  ", taskop_txt[i]);sbuf[32]=0;
//	    draw_string(8,64+64+i*16,sbuf);
//	}
    }
#endif

    if (gui_splash) {
        if (gui_splash>46) {
            gui_draw_splash();
        } else if (gui_splash==1 && (mode_get()&MODE_MASK) == MODE_PLAY) {
            draw_restore();
        }
        --gui_splash;
    }

#ifdef HISTO
    gui_draw_histo();
#endif

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
                gui_menu_init(root_menu);
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
            default:
                break;
        }
        return;
    }

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
    }
    
    switch (gui_mode) {
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

#ifdef HISTO
#define HISTO_WIDTH     100
#define HISTO_HEIGHT    50
static unsigned int histogram[HISTO_WIDTH];
static unsigned int histo_max;

//-------------------------------------------------------------------
static inline void do_histo() {
    unsigned char *img = vid_get_viewport_fb();
    register int i, hi;

    for (i=0; i<HISTO_WIDTH; i++)
        histogram[i] = 0;
    histo_max = 0;

    for (i=0; i<screen_width*screen_height; i++) {
        hi = img[i*3+1]*HISTO_WIDTH/256;
        histogram[hi]++;

        if (histo_max<histogram[hi])
            histo_max = histogram[hi];
    }
}

//-------------------------------------------------------------------
void gui_draw_histo() {
    if ((mode_get()&MODE_MASK) == MODE_REC && gui_mode==GUI_MODE_NONE && 
         conf_show_histo && kbd_is_key_pressed(KEY_SHOOT_HALF)) {
        static const int hx=219;
        static const int hy=45;
        register unsigned int i, v, threshold;

        draw_rect(hx-1, hy, hx+HISTO_WIDTH, hy+HISTO_HEIGHT, COLOR_WHITE);

        do_histo();

        /* histogram */
        for (i=0; i<HISTO_WIDTH; i++) {
            threshold = (histo_max > 0)?(logf((float)histogram[i]))*HISTO_HEIGHT/logf(histo_max):HISTO_HEIGHT;

            for (v=1; v<HISTO_HEIGHT; v++)
                draw_pixel(hx+i, hy+HISTO_HEIGHT-v, (v<=threshold)?COLOR_WHITE:COLOR_BG);
        }
    }
}
#endif

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
    sprintf(osd_buf, "V:%ld.%03ld%8s", v/1000, v%1000, "");
    osd_buf[8]=0;
    draw_txt_string(35, n++, osd_buf, MAKE_COLOR(COLOR_BG, COLOR_FG));


    if (debug_vals_show) {
	sprintf(osd_buf, "1:%8lx  ", ~physw_status[2]);
	draw_txt_string(28, 10, osd_buf, MAKE_COLOR(COLOR_BG, COLOR_FG));

	sprintf(osd_buf, "2:%8ld  ", get_tick_count());
	draw_txt_string(28, 11, osd_buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
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
//    gui_debug_init(0x127E0);
//    gui_debug_init(0x7F5B8);
     DIR *d;
     struct dirent *dd;
     int i=0, t;
     char buf[128];

     d=opendir("A/DCIM/130CANON");
     if (d) {
         dd = readdir(d);
         while (dd && i<14) {
             sprintf(buf, "%08X %s", dd, dd->name);
             draw_txt_string(1, i++, buf, MAKE_COLOR(COLOR_BLACK, COLOR_FG));
             dd = readdir(d);
         }
         closedir(d);
     }

     t = get_tick_count();
     while (get_tick_count() - t <10000) ;

//    gui_debug_init(d);
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
