#ifndef CONF_H
#define CONF_H

#include "gui.h"

typedef struct {
    unsigned short  x, y;
} OSD_pos;

typedef struct {
    int show_osd;
    int save_raw;
    int script_shoot_delay;
    int show_histo;
    int raw_fileno;
    int ubasic_var_a;
    int ubasic_var_b;
    int ubasic_var_c;

    int show_dof;
    int batt_volts_max;
    int batt_volts_min;
    int batt_step_25;
    int batt_perc_show;
    int batt_volts_show;
    int batt_icon_show;

    int show_state;
    int show_values;
    int show_overexp;

    int histo_mode;
    int histo_auto_ajust;
    int histo_ignore_boundary;
    int histo_layout;

    OSD_pos histo_pos;
    OSD_pos dof_pos;
    OSD_pos batt_icon_pos;
    OSD_pos batt_txt_pos;
    OSD_pos mode_state_pos;
    OSD_pos values_pos;

    color histo_color;
    color osd_color;
    color batt_icon_color;
    color menu_color;

    int ns_enable_memdump;
} Conf;

extern Conf conf;

#define SHOOTING_PROGRESS_NONE 0
#define SHOOTING_PROGRESS_STARTED 1
#define SHOOTING_PROGRESS_PROCESSING 2
#define SHOOTING_PROGRESS_DONE 3

extern int state_kbd_script_run;
extern int state_shooting_progress;
extern int state_save_raw_nth_only;
extern int state_expos_recalculated;
extern const char *state_ubasic_script;
extern int state_expos_under;
extern int state_expos_over;

extern int state_debug1;
extern int debug_propcase_show;
extern int debug_propcase_page;
extern int debug_vals_show;

extern void conf_save(int force);
extern void conf_restore();
extern void conf_load_defaults();

extern void load_script(const char *fn);

#endif
