#include "platform.h"
#include "keyboard.h"
#include "conf.h"
#include "histogram.h"
#include "font.h"
#include "raw.h"
#include "gui_draw.h"
#include "gui_osd.h"
#include "stdlib.h"
#include "script.h"

//-------------------------------------------------------------------
#define CONF_FILE  "A/RCFG.BIN"
#define CONF_MAGICK_VALUE (0x33204741)

#define CONF_INFO(id, param, type, def, func) { id, sizeof( param ), &param , type, {def}, func }
#define CONF_DEF_PTR    1
#define CONF_DEF_VALUE  2

//-------------------------------------------------------------------
typedef struct {
    unsigned short      id;
    unsigned short      size;
    void                *var;
    int                 type;
    union {
        void            *ptr;
        int             i;
        color           cl;
    };
    void                (*func)();
} ConfInfo;

//-------------------------------------------------------------------
Conf conf;

int state_shooting_progress = SHOOTING_PROGRESS_NONE;
int state_save_raw_nth_only;
int state_expos_recalculated;
int state_expos_under;
int state_expos_over;

int state_debug1;
int debug_propcase_show;
int debug_propcase_page;
int debug_vals_show;

//-------------------------------------------------------------------
static int def_ubasic_vars[SCRIPT_NUM_PARAMS] = {0};
static int def_batt_volts_max, def_batt_volts_min;
static OSD_pos def_histo_pos, def_dof_pos, def_batt_icon_pos, def_batt_txt_pos, 
               def_mode_state_pos, def_values_pos, def_clock_pos;

static void conf_change_script_file();
static void conf_change_histo_mode();
static void conf_change_histo_layout();
static void conf_change_font();
static void conf_change_menu_rbf_file();
static void conf_change_alt_mode_button();

static const ConfInfo conf_info[] = {
/* !!! Do NOT change ID for items defined already! Append a new one at the end! !!! */
    CONF_INFO(  1, conf.show_osd,               CONF_DEF_VALUE, i:1, NULL),
    CONF_INFO(  2, conf.save_raw,               CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO(  3, conf.script_shoot_delay,     CONF_DEF_VALUE, i:20, NULL),
    CONF_INFO(  4, conf.show_histo,             CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO(  5, conf.ubasic_vars,            CONF_DEF_PTR,   ptr:&def_ubasic_vars, NULL),
    CONF_INFO(  6, conf.script_file,            CONF_DEF_PTR,   ptr:"", conf_change_script_file),
    CONF_INFO(  7, conf.show_dof,               CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO(  8, conf.batt_volts_max,         CONF_DEF_PTR,   ptr:&def_batt_volts_max, NULL),
    CONF_INFO(  9, conf.batt_volts_min,         CONF_DEF_PTR,   ptr:&def_batt_volts_min, NULL),
    CONF_INFO( 10, conf.batt_step_25,           CONF_DEF_VALUE, i:1, NULL),
    CONF_INFO( 11, conf.batt_perc_show,         CONF_DEF_VALUE, i:1, NULL),
    CONF_INFO( 12, conf.batt_volts_show,        CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO( 13, conf.batt_icon_show,         CONF_DEF_VALUE, i:1, NULL),
    CONF_INFO( 14, conf.show_state,             CONF_DEF_VALUE, i:1, NULL),
    CONF_INFO( 15, conf.show_values,            CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO( 16, conf.show_overexp,           CONF_DEF_VALUE, i:1, NULL),
    CONF_INFO( 17, conf.histo_mode,             CONF_DEF_VALUE, i:HISTO_MODE_LINEAR, conf_change_histo_mode),
    CONF_INFO( 18, conf.histo_auto_ajust,       CONF_DEF_VALUE, i:1, NULL),
    CONF_INFO( 19, conf.histo_ignore_boundary,  CONF_DEF_VALUE, i:4, NULL),
    CONF_INFO( 20, conf.histo_layout,           CONF_DEF_VALUE, i:OSD_HISTO_LAYOUT_A, conf_change_histo_layout),
    CONF_INFO( 21, conf.histo_pos,              CONF_DEF_PTR,   ptr:&def_histo_pos, NULL),
    CONF_INFO( 22, conf.dof_pos,                CONF_DEF_PTR,   ptr:&def_dof_pos, NULL),
    CONF_INFO( 23, conf.batt_icon_pos,          CONF_DEF_PTR,   ptr:&def_batt_icon_pos, NULL),
    CONF_INFO( 24, conf.batt_txt_pos,           CONF_DEF_PTR,   ptr:&def_batt_txt_pos , NULL),
    CONF_INFO( 25, conf.mode_state_pos,         CONF_DEF_PTR,   ptr:&def_mode_state_pos , NULL),
    CONF_INFO( 26, conf.values_pos,             CONF_DEF_PTR,   ptr:&def_values_pos , NULL),
    CONF_INFO( 27, conf.histo_color,            CONF_DEF_VALUE, cl:MAKE_COLOR(COLOR_BG, COLOR_WHITE), NULL),
    CONF_INFO( 28, conf.osd_color,              CONF_DEF_VALUE, cl:MAKE_COLOR(COLOR_BG, COLOR_FG), NULL),
    CONF_INFO( 29, conf.batt_icon_color,        CONF_DEF_VALUE, cl:COLOR_WHITE, NULL),
    CONF_INFO( 30, conf.menu_color,             CONF_DEF_VALUE, cl:MAKE_COLOR(COLOR_BG, COLOR_FG), NULL),
    CONF_INFO( 31, conf.reader_color,           CONF_DEF_VALUE, cl:MAKE_COLOR(COLOR_GREY, COLOR_WHITE), NULL),
    CONF_INFO( 32, conf.font,                   CONF_DEF_VALUE, i:FONT_DEFAULT, conf_change_font),
    CONF_INFO( 33, conf.flashlight,             CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO( 34, conf.ns_enable_memdump,      CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO( 35, conf.raw_in_dir,             CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO( 36, conf.raw_prefix,             CONF_DEF_VALUE, i:RAW_PREFIX_CRW, NULL),
    CONF_INFO( 37, conf.raw_ext,                CONF_DEF_VALUE, i:RAW_EXT_CRW, NULL),
    CONF_INFO( 38, conf.reader_file,            CONF_DEF_PTR,   ptr:"", conf_change_script_file),
    CONF_INFO( 39, conf.reader_pos,             CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO( 40, conf.sokoban_level,          CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO( 41, conf.show_clock,             CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO( 42, conf.clock_pos,              CONF_DEF_PTR,   ptr:&def_clock_pos , NULL),
    CONF_INFO( 43, conf.reader_autoscroll,      CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO( 44, conf.reader_autoscroll_delay, CONF_DEF_VALUE, i:5, NULL),
    CONF_INFO( 45, conf.reader_rbf_file,        CONF_DEF_PTR,   ptr:"", NULL),
    CONF_INFO( 46, conf.reader_codepage,        CONF_DEF_VALUE, i:FONT_CP_WIN, NULL),
    CONF_INFO( 47, conf.splash_show,            CONF_DEF_VALUE, i:1, NULL),
    CONF_INFO( 48, conf.histo_color2,           CONF_DEF_VALUE, cl:MAKE_COLOR(COLOR_RED, COLOR_WHITE), NULL),
    CONF_INFO( 49, conf.zebra_draw,             CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO( 50, conf.zebra_mode,             CONF_DEF_VALUE, i:ZEBRA_MODE_BLINKED_2, NULL),
    CONF_INFO( 51, conf.zebra_restore_screen,   CONF_DEF_VALUE, i:1, NULL),
    CONF_INFO( 52, conf.zebra_restore_osd,      CONF_DEF_VALUE, i:1, NULL),
    CONF_INFO( 53, conf.zebra_over,             CONF_DEF_VALUE, i:1, NULL),
    CONF_INFO( 54, conf.zebra_under,            CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO( 55, conf.zebra_color,            CONF_DEF_VALUE, cl:MAKE_COLOR(COLOR_RED, COLOR_RED), NULL),
    CONF_INFO( 56, conf.zebra_draw_osd,         CONF_DEF_VALUE, i:ZEBRA_DRAW_HISTO, NULL),
    CONF_INFO( 57, conf.menu_rbf_file,          CONF_DEF_PTR,   ptr:"", conf_change_menu_rbf_file),
    CONF_INFO( 58, conf.zoom_value,             CONF_DEF_VALUE, i:ZOOM_SHOW_X, NULL),
    CONF_INFO( 59, conf.use_zoom_mf,            CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO( 60, conf.raw_save_first_only,    CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO( 61, conf.reader_wrap_by_words,   CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO( 62, conf.raw_save_second,        CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO( 63, conf.alt_mode_button,        CONF_DEF_VALUE, i:KEY_PRINT, conf_change_alt_mode_button),
};
#define CONF_NUM (sizeof(conf_info)/sizeof(conf_info[0]))

//-------------------------------------------------------------------
static void conf_change_histo_mode() {
    histogram_set_mode(conf.histo_mode);
}

static void conf_change_histo_layout() {
    if (conf.histo_layout==OSD_HISTO_LAYOUT_Y || conf.histo_layout==OSD_HISTO_LAYOUT_Y_argb) {
        histogram_set_main(HISTO_Y);
    } else {
        histogram_set_main(HISTO_RGB);
    }
}

static void conf_change_font() {
    font_set(conf.font);
}

static void conf_change_script_file() {
    script_load(conf.script_file);
}

static void conf_change_menu_rbf_file() {
    if (!rbf_load(conf.menu_rbf_file))
        rbf_load_from_8x16(current_font);
    rbf_set_codepage(FONT_CP_DOS);
}

static void conf_change_alt_mode_button() {
#if defined(CAMERA_s2is) || defined(CAMERA_s3is)
    kbd_set_alt_mode_key_mask(conf.alt_mode_button);
#else
    conf.alt_mode_button = KEY_PRINT;
#endif
}

//-------------------------------------------------------------------
static void conf_init_defaults() {
    // init some defaults values
    def_batt_volts_max = get_vbatt_max();
    def_batt_volts_min = get_vbatt_min();
    def_histo_pos.x = 319-HISTO_WIDTH;
    def_histo_pos.y = 45;
    def_dof_pos.x = 5*FONT_WIDTH;
    def_dof_pos.y = 0;
    def_batt_icon_pos.x = 178;
    def_batt_icon_pos.y = 4;
    def_batt_txt_pos.x=vid_get_bitmap_width()-8*FONT_WIDTH-2;
    def_batt_txt_pos.y=vid_get_bitmap_height()-64;
    def_mode_state_pos.x=vid_get_bitmap_width()-4*FONT_WIDTH;
    def_mode_state_pos.y=45;
    def_values_pos.x=vid_get_bitmap_width()-9*FONT_WIDTH;
    def_values_pos.y=6*FONT_HEIGHT;
    def_clock_pos.x=vid_get_bitmap_width()-5*FONT_WIDTH-2;
    def_clock_pos.y=0;
}

//-------------------------------------------------------------------
void conf_load_defaults() {
    register int i;

    for (i=0; i<CONF_NUM; ++i) {
        switch (conf_info[i].type) {
            case CONF_DEF_VALUE:
                memcpy(conf_info[i].var, &(conf_info[i].i), conf_info[i].size);
                break;
            case CONF_DEF_PTR:
                memcpy(conf_info[i].var, conf_info[i].ptr, conf_info[i].size);
                break;
        }
        if (conf_info[i].func) {
            conf_info[i].func();
        }
    }
}

//-------------------------------------------------------------------
void conf_save() {
    static const long t=CONF_MAGICK_VALUE;
    register int i;
    int fd;
    static char buf[sizeof(t)+CONF_NUM*(sizeof(conf_info[0].id)+sizeof(conf_info[0].size))+sizeof(conf)];
    char *p=buf;

    fd = open(CONF_FILE, O_WRONLY|O_CREAT, 0777); 
    if (fd>=0){
        memcpy(p, &t, sizeof(t));
        p+=sizeof(t);
        for (i=0; i<CONF_NUM; ++i) {
            memcpy(p, &(conf_info[i].id), sizeof(conf_info[i].id));
            p+=sizeof(conf_info[i].id);
            memcpy(p, &(conf_info[i].size), sizeof(conf_info[i].size));
            p+=sizeof(conf_info[i].size);
            memcpy(p, conf_info[i].var, conf_info[i].size);
            p+=conf_info[i].size;
        }

        write(fd, buf, p-buf);
        close(fd);
    }
}

//-------------------------------------------------------------------
void conf_restore() {
    int fd, rcnt, i;
    long t;
    unsigned short id, size;
    void *ptr;

    conf_init_defaults();

    conf_load_defaults();

    fd = open(CONF_FILE, O_RDONLY, 0777); 
    if (fd>=0){
        // read magick value
        rcnt = read(fd, &t, sizeof(t));
        if (rcnt==sizeof(t) && t==CONF_MAGICK_VALUE) {
            while (1) {
                rcnt = read(fd, &id, sizeof(id));
                if (rcnt!=sizeof(id)) break;

                rcnt = read(fd, &size, sizeof(size));
                if (rcnt!=sizeof(size)) break;

                for (i=0; i<CONF_NUM; ++i) {
                    if (conf_info[i].id==id && conf_info[i].size==size) {
                        ptr=malloc(size);
                        if (ptr) {
                            rcnt = read(fd, ptr, size);
                            if (rcnt == size) {
                               memcpy(conf_info[i].var, ptr, size);
                               if (conf_info[i].func) {
                                   conf_info[i].func();
                               }
                            }
                            free(ptr);
                        }
                        break;
                    }
                }
                if (i == CONF_NUM) { // unknown id, just skip data
                    lseek(fd, size, SEEK_CUR);
                }
            }
        }
	close(fd);
    }
}

//-------------------------------------------------------------------
