#include "stdlib.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"
#include "conf.h"
#include "ubasic.h"
#include "font.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_menu.h"
#include "gui_palette.h"
#include "gui_mbox.h"
#include "gui_reversi.h"
#include "gui_debug.h"
#include "gui_fselect.h"
#include "gui_batt.h"
#include "gui_osd.h"
#include "gui_read.h"
#include "histogram.h"
#include "script.h"

//-------------------------------------------------------------------

#define OPTIONS_AUTOSAVE

// forward declarations
//-------------------------------------------------------------------
void dump_memory();

static void gui_draw_osd();
static void gui_draw_splash();

// Menu procs
//-------------------------------------------------------------------
static void gui_show_build_info(int arg);
static void gui_show_memory_info(int arg);
static void gui_draw_palette(int arg);
static void gui_draw_reversi(int arg);
static void gui_test(int arg);
static void gui_draw_debug(int arg);
static void gui_draw_fselect(int arg);
static void gui_draw_osd_le(int arg);
static void gui_load_script(int arg);
static void gui_draw_read(int arg);
#ifndef OPTIONS_AUTOSAVE
static void gui_menuproc_save(int arg);
#endif
static void gui_menuproc_reset(int arg);
static const char* gui_histo_mode_enum(int change, int arg);
static const char* gui_histo_layout_enum(int change, int arg);
static const char* gui_font_enum(int change, int arg);

// Menu callbacks
//-------------------------------------------------------------------
static void cb_step_25();
static void cb_perc();
static void cb_volts();
static void cb_battery_menu_change(unsigned int item);

// Menu definition
//-------------------------------------------------------------------
static CMenuItem script_submenu_items_top[] = {
    {"Load script from file...",    MENUITEM_PROC,                      (int*)gui_load_script },
    {"Script shoot delay (.1s)",    MENUITEM_INT|MENUITEM_F_UNSIGNED,   &conf.script_shoot_delay },
    {"Current script",              MENUITEM_SEPARATOR },
    {script_title,                  MENUITEM_TEXT },
    {"Script parameters",           MENUITEM_SEPARATOR }
};

static CMenuItem script_submenu_items_bottom[] = {
    {"<- Back",                     MENUITEM_UP },
    {0}
};

static CMenuItem script_submenu_items[sizeof(script_submenu_items_top)/sizeof(script_submenu_items_top[0])+SCRIPT_NUM_PARAMS+
                               sizeof(script_submenu_items_bottom)/sizeof(script_submenu_items_bottom[0])];
static CMenu script_submenu = { "Script", NULL, script_submenu_items };


static CMenuItem misc_submenu_items[] = {
    {"Show build info",             MENUITEM_PROC,  (int*)gui_show_build_info },
    {"Show memory info",            MENUITEM_PROC,  (int*)gui_show_memory_info },
    {"File browser",                MENUITEM_PROC,  (int*)gui_draw_fselect },
    {"Draw palette",                MENUITEM_PROC,  (int*)gui_draw_palette },
    {"Text file reader",            MENUITEM_PROC,  (int*)gui_draw_read },
    {"MessageBox test",             MENUITEM_PROC,  (int*)gui_test },
    {"GAME: Reversi",               MENUITEM_PROC,  (int*)gui_draw_reversi },
    {"<- Back",                     MENUITEM_UP },
    {0}
};
static CMenu misc_submenu = { "Miscellaneous", NULL, misc_submenu_items };


static CMenuItem debug_submenu_items[] = {
    {"Show PropCases",              MENUITEM_BOOL,                      &debug_propcase_show },
    {"PropCase page",               MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,   &debug_propcase_page, MENU_MINMAX(0, 128) },
    {"Show misc. values",           MENUITEM_BOOL,                      &debug_vals_show },
    {"Memory browser",              MENUITEM_PROC,                      (int*)gui_draw_debug },
    {"Dump RAM on ALT +/- press",   MENUITEM_BOOL,                      &conf.ns_enable_memdump },
    {"<- Back",                     MENUITEM_UP },
    {0}
};
static CMenu debug_submenu = { "Debug", NULL, debug_submenu_items };


static int voltage_step;
static CMenuItem battery_submenu_items[] = {
    {"Voltage MAX",                 MENUITEM_INT|MENUITEM_ARG_ADDR_INC,     &conf.batt_volts_max,   (int)&voltage_step },
    {"Voltage MIN",                 MENUITEM_INT|MENUITEM_ARG_ADDR_INC,     &conf.batt_volts_min,   (int)&voltage_step },
    {"25+ step",                    MENUITEM_BOOL|MENUITEM_ARG_CALLBACK,    &conf.batt_step_25,     (int)cb_step_25 },	
    {"",                            MENUITEM_SEPARATOR },
    {"Show percent",                MENUITEM_BOOL|MENUITEM_ARG_CALLBACK,    &conf.batt_perc_show,   (int)cb_perc },
    {"Show volts",                  MENUITEM_BOOL|MENUITEM_ARG_CALLBACK,    &conf.batt_volts_show,  (int)cb_volts },
    {"Show icon",                   MENUITEM_BOOL,                          &conf.batt_icon_show },	
    {"<- Back",                     MENUITEM_UP },
    {0}
};
static CMenu battery_submenu = { "Battery", cb_battery_menu_change, battery_submenu_items };


static CMenuItem visual_submenu_items[] = {
    {"Font",                        MENUITEM_ENUM,      (int*)gui_font_enum },
    {"Colors",                      MENUITEM_SEPARATOR },
    {"OSD text",                    MENUITEM_COLOR_FG,  (int*)&conf.osd_color },
    {"OSD background",              MENUITEM_COLOR_BG,  (int*)&conf.osd_color },
    {"Histogram",                   MENUITEM_COLOR_FG,  (int*)&conf.histo_color },
    {"Histogram background",        MENUITEM_COLOR_BG,  (int*)&conf.histo_color },
    {"Battery icon",                MENUITEM_COLOR_FG,  (int*)&conf.batt_icon_color },
    {"Menu text",                   MENUITEM_COLOR_FG,  (int*)&conf.menu_color },
    {"Menu background",             MENUITEM_COLOR_BG,  (int*)&conf.menu_color },
    {"<- Back",                     MENUITEM_UP },
    {0}
};
static CMenu visual_submenu = { "Visual settings", NULL, visual_submenu_items };


static CMenuItem osd_submenu_items[] = {
    {"Show OSD",                    MENUITEM_BOOL,      &conf.show_osd },
    {"Show RAW/SCR/EXP state",      MENUITEM_BOOL,      &conf.show_state },
    {"Show misc values",            MENUITEM_BOOL,      &conf.show_values },
    {"Show DOF calculator",         MENUITEM_BOOL,      &conf.show_dof },
    {"OSD layout editor",           MENUITEM_PROC,      (int*)gui_draw_osd_le },
    {"Battery parameters ->",       MENUITEM_SUBMENU,   (int*)&battery_submenu },
#ifndef OPTIONS_AUTOSAVE
    {"Save options now...",         MENUITEM_PROC,      (int*)gui_menuproc_save },
#endif
    {"<- Back",                     MENUITEM_UP },
    {0}
};
static CMenu osd_submenu = { "OSD", NULL, osd_submenu_items };


static CMenuItem histo_submenu_items[] = {
    {"Show live histogram",         MENUITEM_BOOL,      &conf.show_histo },
    {"Histogram layout",            MENUITEM_ENUM,      (int*)gui_histo_layout_enum },
    {"Histogram mode",              MENUITEM_ENUM,      (int*)gui_histo_mode_enum },
    {"Show histogram over/under EXP", MENUITEM_BOOL,    &conf.show_overexp },
    {"Ignore boundary peaks",       MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,  &conf.histo_ignore_boundary,   MENU_MINMAX(0, 32)},
    {"Auto magnify",                MENUITEM_BOOL,      &conf.histo_auto_ajust },
    {"<- Back",                     MENUITEM_UP },
    {0}
};
static CMenu histo_submenu = { "Histogram", NULL, histo_submenu_items };


static CMenuItem root_menu_items[] = {
    {"Save RAW",                    MENUITEM_BOOL,      &conf.save_raw },
    {"OSD parameters ->",           MENUITEM_SUBMENU,   (int*)&osd_submenu },
    {"Histogram parameters ->",     MENUITEM_SUBMENU,   (int*)&histo_submenu },
    {"Scripting parameters ->",     MENUITEM_SUBMENU,   (int*)&script_submenu },
    {"Visual settings ->",           MENUITEM_SUBMENU,   (int*)&visual_submenu },
    {"Miscellaneous stuff ->",      MENUITEM_SUBMENU,   (int*)&misc_submenu },
    {"Debug parameters ->",         MENUITEM_SUBMENU,   (int*)&debug_submenu },
    {"Reset options to default...", MENUITEM_PROC,      (int*)gui_menuproc_reset },
#ifndef OPTIONS_AUTOSAVE
    {"Save options now...",         MENUITEM_PROC,      (int*)gui_menuproc_save },
#endif
    {0}
};
static CMenu root_menu = { "Main", NULL, root_menu_items };

//-------------------------------------------------------------------
void cb_step_25() {
    voltage_step = (conf.batt_step_25)?25:1;
}

void cb_perc() {
    conf.batt_volts_show=0;
}

void cb_volts() {
    conf.batt_perc_show=0;
}

void cb_battery_menu_change(unsigned int item) {
    switch (item) {
        case 0: //Voltage MAX
            if (conf.batt_volts_max<conf.batt_volts_min+25) {
                conf.batt_volts_min = conf.batt_volts_max-25;
            }
            break;
        case 1: //Voltage MIN
            if (conf.batt_volts_min>conf.batt_volts_max-25) {
                conf.batt_volts_max = conf.batt_volts_min+25;
            }
            break;
        default:
            break;
    }
}

//-------------------------------------------------------------------
const char* gui_histo_mode_enum(int change, int arg) {
    static const char* modes[]={ "Linear", "Log" };

    conf.histo_mode+=change;
    if (conf.histo_mode<0)
        conf.histo_mode=(sizeof(modes)/sizeof(modes[0]))-1;
    else if (conf.histo_mode>=(sizeof(modes)/sizeof(modes[0])))
        conf.histo_mode=0;

    histogram_set_mode(conf.histo_mode);

    return modes[conf.histo_mode];
}

//-------------------------------------------------------------------
const char* gui_histo_layout_enum(int change, int arg) {
    static const char* modes[]={ "RGB", "Y", "RGB Y",  "R G B", "RGB all", "Y all"};

    conf.histo_layout+=change;
    if (conf.histo_layout<0)
        conf.histo_layout=(sizeof(modes)/sizeof(modes[0]))-1;
    else if (conf.histo_layout>=(sizeof(modes)/sizeof(modes[0])))
        conf.histo_layout=0;

    if (conf.histo_layout==OSD_HISTO_LAYOUT_Y || conf.histo_layout==OSD_HISTO_LAYOUT_Y_argb) {
        histogram_set_main(HISTO_Y);
    } else {
        histogram_set_main(HISTO_RGB);
    }

    return modes[conf.histo_layout];
}

//-------------------------------------------------------------------
const char* gui_font_enum(int change, int arg) {
    static const char* fonts[]={ "Default", "UniRus", "VgaKbr"};

    conf.font+=change;
    if (conf.font<0)
        conf.font=(sizeof(fonts)/sizeof(fonts[0]))-1;
    else if (conf.font>=(sizeof(fonts)/sizeof(fonts[0])))
        conf.font=0;

    font_set(conf.font);

    return fonts[conf.font];
}

//-------------------------------------------------------------------
void gui_update_script_submenu() {
    register int p=0, i;

    for (i=0; i<sizeof(script_submenu_items_top)/sizeof(script_submenu_items_top[0]); ++p, ++i) {
        script_submenu_items[p]=script_submenu_items_top[i];
    }
    for (i=0; i<SCRIPT_NUM_PARAMS; ++i) {
        if (script_params[i][0]) {
            script_submenu_items[p].text=script_params[i];
            script_submenu_items[p].type=MENUITEM_INT;
            script_submenu_items[p].value=&conf.ubasic_vars[i];
            ++p;
        }
    }
    for (i=0; i<sizeof(script_submenu_items_bottom)/sizeof(script_submenu_items_bottom[0]); ++p, ++i) {
        script_submenu_items[p]=script_submenu_items_bottom[i];
    }
}

//-------------------------------------------------------------------
static volatile enum Gui_Mode gui_mode;
static volatile int gui_restore;
static volatile int gui_in_redraw;
static int gui_splash = 50;
static char osd_buf[32];
#ifdef OPTIONS_AUTOSAVE
static Conf old_conf;
#endif

//-------------------------------------------------------------------
void gui_init()
{
    gui_mode = GUI_MODE_NONE;
    gui_restore = 0;
    gui_in_redraw = 0;
    draw_init();

    exposition_thresh = screen_size/500;
    voltage_step = (conf.batt_step_25)?25:1;
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
    static int show_script_console=0;

    if (gui_splash) {
        if (gui_splash>46) {
            gui_draw_splash();
        } else if (gui_splash==1 && (mode_get()&MODE_MASK) == MODE_PLAY && (gui_mode==GUI_MODE_NONE || gui_mode==GUI_MODE_ALT)) {
            draw_restore();
        }
        --gui_splash;
    }

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
            if ((mode_get()&MODE_MASK) == MODE_REC) {
                draw_txt_string(0, 14, script_title, MAKE_COLOR(COLOR_ALT_BG, COLOR_FG));
                if (state_kbd_script_run) show_script_console=5;
                if (show_script_console) {
                    --show_script_console;
                    script_console_draw();
                }
            }
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
        case GUI_MODE_READ:
            gui_read_draw();
            break;
        case GUI_MODE_OSD:
            gui_osd_draw();
//            draw_txt_string(20, 14, "<OSD>", MAKE_COLOR(COLOR_ALT_BG, COLOR_FG));
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

#ifdef OPTIONS_AUTOSAVE
//-------------------------------------------------------------------
static inline void conf_store_old_settings() {
    old_conf=conf;
}

//-------------------------------------------------------------------
static inline int conf_save_new_settings_if_changed() {
    if (memcmp(&old_conf, &conf, sizeof(Conf)) != 0) {
        conf_save(1);
        return 1;
    }
    return 0;
}
#endif

//-------------------------------------------------------------------
void gui_kbd_process()
{
    int clicked_key;

    if (kbd_is_key_clicked(KEY_MENU)){
        switch (gui_mode) {
            case GUI_MODE_ALT:
#ifdef OPTIONS_AUTOSAVE
                conf_store_old_settings();
#endif
                gui_menu_init(&root_menu);
                gui_mode = GUI_MODE_MENU;
                draw_restore();
                break;
            case GUI_MODE_MENU:
#ifdef OPTIONS_AUTOSAVE
                conf_save_new_settings_if_changed();
#endif
                gui_mode = GUI_MODE_ALT;
                draw_restore();
                break;
            case GUI_MODE_PALETTE:
            case GUI_MODE_REVERSI:
            case GUI_MODE_DEBUG:
            case GUI_MODE_OSD:
                draw_restore();
                gui_mode = GUI_MODE_MENU;
                break;
            case GUI_MODE_FSELECT:
                gui_fselect_kbd_process();
                break;
            case GUI_MODE_READ:
                gui_read_kbd_process();
                draw_restore();
                gui_mode = GUI_MODE_MENU;
                break;
            default:
                break;
        }
        return;
    }
    
    switch (gui_mode) {
        case GUI_MODE_ALT:
            if (kbd_is_key_clicked(KEY_ERASE) && conf.ns_enable_memdump) {
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
    	case GUI_MODE_READ:
            gui_read_kbd_process();
            break;
    	case GUI_MODE_OSD:
            gui_osd_kbd_process();
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
#ifdef OPTIONS_AUTOSAVE
    conf_save_new_settings_if_changed();
#endif
    ubasic_error = 0;
    draw_restore();
    gui_mode = GUI_MODE_NONE;
}

//-------------------------------------------------------------------
extern long physw_status[3];
extern long GetPropertyCase(long opt_id, void *buf, long bufsize);
//-------------------------------------------------------------------
void gui_draw_osd() {
    unsigned int m, n = 0;
    coord x;
    
    if (conf.show_histo && (gui_mode==GUI_MODE_NONE || gui_mode==GUI_MODE_ALT) && kbd_is_key_pressed(KEY_SHOOT_HALF)) {
        gui_osd_draw_histo();
    }

    if (!conf.show_osd) return;

    m = mode_get();
    
    if ((m&MODE_MASK) == MODE_REC) {
        m &= MODE_SHOOTING_MASK;
//        if (m==MODE_SCN_WATER || m==MODE_SCN_NIGHT || m==MODE_SCN_CHILD || m==MODE_SCN_PARTY || m==MODE_STITCH ||
//            m==MODE_SCN_GRASS || m==MODE_SCN_SNOW  || m==MODE_SCN_BEACH || m==MODE_SCN_FIREWORK || m==MODE_VIDEO)
//            ++n;

        if (conf.show_dof && (gui_mode==GUI_MODE_NONE /*|| gui_mode==GUI_MODE_ALT*/) && kbd_is_key_pressed(KEY_SHOOT_HALF)) {
            gui_osd_draw_dof();
        }

        if (conf.show_state) {
            gui_osd_draw_state();
        }

        if (conf.show_values) {
            gui_osd_draw_values();
        }
    }

    gui_batt_draw_osd();

    if (debug_vals_show) {
        long v=get_file_counter();
	sprintf(osd_buf, "1:%03d-%04d  ", (v>>18)&0x3FF, (v>>4)&0x3FFF);
//	sprintf(osd_buf, "1:%8lx  ", ~physw_status[2]);
	draw_txt_string(28, 10, osd_buf, conf.osd_color);

	sprintf(osd_buf, "2:%8ld  ", get_tick_count());
	draw_txt_string(28, 11, osd_buf, conf.osd_color);

	sprintf(osd_buf, "3:%d %d ", state_expos_under, state_expos_over);
	draw_txt_string(28, 12, osd_buf, conf.osd_color);
    }

    if (debug_propcase_show){
	static char sbuf[100];
	int r,i, p;

	for (i=0;i<10;i++){
	    r = 0;
	    p = debug_propcase_page*10+i;
	    GetPropertyCase(p, &r, 4);
	    sprintf(sbuf, "%3d: %d              ", p, r);sbuf[20]=0;
	    draw_string(64,16+16*i,sbuf, conf.osd_color);
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

#ifndef OPTIONS_AUTOSAVE
//-------------------------------------------------------------------
void gui_menuproc_save(int arg)
{
    conf_save(1);
}
#endif

//-------------------------------------------------------------------
static void gui_menuproc_reset_selected(unsigned int btn) {
    if (btn==MBOX_BTN_YES)
        conf_load_defaults();
}

void gui_menuproc_reset(int arg)
{
    gui_mbox_init("*** Reset options ***", 
                  "Are you SURE to reset\noptions to default?",
                  MBOX_FUNC_RESTORE|MBOX_TEXT_CENTER|MBOX_BTN_YES_NO|MBOX_DEF_BTN2, gui_menuproc_reset_selected);
}

//-------------------------------------------------------------------
void gui_draw_palette(int arg) {
    draw_restore();
    gui_palette_init(PALETTE_MODE_DEFAULT, 0x00, NULL);
    gui_mode = GUI_MODE_PALETTE;
}

//-------------------------------------------------------------------
void gui_show_build_info(int arg) {
    gui_mbox_init("*** Build Info ***", 
                  "Date:    "   __DATE__ 
                  "\nTime:    " __TIME__ 
                  "\nCamera:  " PLATFORM 
                  "\nFW Vers: " PLATFORMSUB, MBOX_FUNC_RESTORE|MBOX_TEXT_LEFT, NULL);
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
    gui_mbox_init("*** Memory Info ***", buf, MBOX_FUNC_RESTORE|MBOX_TEXT_CENTER, NULL);
}

//-------------------------------------------------------------------
void gui_draw_reversi(int arg) {
    if ((mode_get()&MODE_MASK) != MODE_PLAY) {
        gui_mbox_init("*** Information ***", "Please switch your camera\nto PLAY mode\nand try again. :)",
                      MBOX_FUNC_RESTORE|MBOX_TEXT_CENTER, NULL);
        return;
    }
    gui_mode = GUI_MODE_REVERSI;
    gui_reversi_init();
}

//-------------------------------------------------------------------
void gui_test(int arg) {
    gui_mbox_init("*** Information ***", "Test multibuttons", 
                  MBOX_FUNC_RESTORE|MBOX_TEXT_CENTER|MBOX_BTN_YES_NO_CANCEL, NULL);
}

//-------------------------------------------------------------------
void gui_draw_debug(int arg) {
//    gui_debug_init(0x2510);
//    gui_debug_init(0x127E0);
//    gui_debug_init(0x7F5B8);
//    gui_debug_init(malloc(16));
    gui_debug_init((void*)0xB054);
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
        script_load(fn);
}
void gui_load_script(int arg) {
    DIR   *d;
    char  *path="A/SCRIPTS";

    // if exists "A/SCRIPTS" go into
    d=opendir("A/SCRIPTS");
    if (d) {
        closedir(d);
    } else {
        path="A";
    }

    gui_fselect_init(path, gui_load_script_selected);
}

//-------------------------------------------------------------------
void gui_draw_osd_le(int arg) {
    gui_mode = GUI_MODE_OSD;
    gui_osd_init();
}

//-------------------------------------------------------------------
static void gui_draw_read_selected(const char *fn) {
    if (fn) {
        gui_mode = GUI_MODE_READ;
        gui_read_init(fn);
    }
}
void gui_draw_read(int arg) {
    gui_fselect_init("A", gui_draw_read_selected);
}

//-------------------------------------------------------------------
