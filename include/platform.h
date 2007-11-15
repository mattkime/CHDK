#ifndef PLATFORM_H
#define PLATFORM_H

#define SSID_INVALID (-32767)
#define ASID_INVALID (-32767)

#define MODE_MASK               0x0300
#define MODE_REC                0x0100
#define MODE_PLAY               0x0200

#define MODE_SHOOTING_MASK      0x00FF

enum {
MODE_AUTO               =1,
MODE_P                  ,
MODE_TV                 ,
MODE_AV                 ,
MODE_M                  ,
MODE_PORTRAIT           ,
MODE_NIGHT              ,
MODE_LANDSCAPE          ,
MODE_VIDEO_STD          ,
MODE_VIDEO_SPEED        ,
MODE_VIDEO_COMPACT      ,
MODE_VIDEO_MY_COLORS    ,
MODE_VIDEO_COLOR_ACCENT ,
MODE_STITCH             ,
MODE_MY_COLORS          ,
MODE_SCN_WATER          ,
MODE_SCN_NIGHT          ,
MODE_SCN_CHILD          ,
MODE_SCN_PARTY          ,
MODE_SCN_GRASS          ,
MODE_SCN_SNOW           ,
MODE_SCN_BEACH          ,
MODE_SCN_FIREWORK       ,
MODE_SCN_COLOR_ACCENT   ,
MODE_VIDEO_HIRES        ,
MODE_SCN_AQUARIUM       ,

MODE_SCN_NIGHT1         ,
MODE_SCN_ISO_3200       ,
MODE_SCN_SPORT          ,

MODE_INDOOR             ,
MODE_KIDS_PETS          ,
MODE_NIGHT_SNAPSHOT     ,
MODE_DIGITAL_MACRO      ,
};

#define MODE_SCREEN_MASK        0x0C00
#define MODE_SCREEN_OPENED      0x0400
#define MODE_SCREEN_ROTATED     0x0800

typedef struct {
    short int id; // hacks id
    short int prop_id; // Canons id
    char name[8];
    short int shutter_dfs_value; // shutter speed to use dark frame substraction
} ISOTable;

typedef struct {
    short int id; // hacks id
    short int prop_id; // Canons id
    char name[8];
    long usec;
} ShutterSpeed;

typedef struct {
    short int id; // hacks id
    short int prop_id; // Canons id
    char name[8];
} ApertureSize;

/******************************************************************/

int get_focal_length(int zp);
int get_effective_focal_length(int zp);
int get_zoom_x(int zp);

/******************************************************************/

long get_tick_count();

void remount_filesystem();
void mark_filesystem_bootable();

/******************************************************************/

long get_parameter_data(long id, void *buf, long bufsize);
long set_parameter_data(long id, void *buf, long bufsize);

long get_property_case(long id, void *buf, long bufsize);
long set_property_case(long id, void *buf, long bufsize);

long get_file_counter();
long get_file_next_counter();
long get_target_dir_num();
long get_target_file_num();

/******************************************************************/

void kbd_key_press(long key);
void kbd_key_release(long key);
void kbd_key_release_all();
long kbd_is_key_pressed(long key);
long kbd_is_key_clicked(long key);
long kbd_get_pressed_key();
long kbd_get_clicked_key();
long kbd_get_autoclicked_key();
void kbd_reset_autoclicked_key();
long kbd_use_zoom_as_mf();
void kbd_set_alt_mode_key_mask(long key);

/******************************************************************/

long vid_is_bitmap_shown();
void *vid_get_bitmap_fb();
long vid_get_bitmap_width();
long vid_get_bitmap_height();
void *vid_get_viewport_fb();
void *vid_get_viewport_fb_d();
void *vid_get_viewport_live_fb();
void vid_bitmap_refresh();
long vid_get_viewport_height();

/******************************************************************/

void *hook_raw_fptr();
void *hook_raw_ret_addr();
char *hook_raw_image_addr();
long hook_raw_size();
void hook_raw_install();
void hook_raw_save_complete();

/******************************************************************/

long lens_get_zoom_pos();
void lens_set_zoom_pos(long newpos);
long lens_get_zoom_point();
void lens_set_zoom_point(long newpt);
void lens_set_zoom_speed(long newspd); //for S-series
long lens_get_focus_pos();
void lens_set_focus_pos(long newpos);
long lens_get_target_distance();

/******************************************************************/

int shooting_in_progress();
int shooting_is_flash_ready();

int shooting_get_tv();
char* shooting_get_tv_str();
void shooting_set_tv(int v);
void shooting_set_tv_rel(int v);
const ShutterSpeed *shooting_get_tv_line();

int shooting_get_av();
char* shooting_get_av_str();
void shooting_set_av(int v);
void shooting_set_av_rel(int v);

int shooting_get_real_av();

extern int circle_of_confusion;

extern const int zoom_points;
int shooting_get_zoom();
void shooting_set_zoom(int v);
void shooting_set_zoom_rel(int v);
void shooting_set_zoom_speed(int v);

int shooting_get_focus();
void shooting_set_focus(int v);

int shooting_get_iso();
void shooting_set_iso(int v);
void shooting_set_iso_direct(int v);

void shooting_video_bitrate_change(int v);

/******************************************************************/

int mode_get();

/******************************************************************/

long stat_get_vbatt();
long get_vbatt_min();
long get_vbatt_max();

void disable_shutdown();
void enable_shutdown();
void JogDial_CW(void);
void JogDial_CCW(void);
void change_video_tables(int a, int b);

/******************************************************************/
void __attribute__((noreturn)) shutdown();
void debug_led(int state);
#define started() debug_led(1)
#define finished() debug_led(0)

#endif
