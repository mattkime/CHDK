#include "platform.h"
#include "conf.h"
#include "histogram.h"
#include "gui_draw.h"
#include "gui_osd.h"
#include "stdlib.h"
#include "script.h"

#define FN_COUNTER  "A/RCFG.BIN"
#define CNF_MAGICK_VALUE (0x32204741)

Conf conf;

int state_shooting_progress;
int state_save_raw_nth_only;
int state_expos_recalculated;
int state_expos_under;
int state_expos_over;

int state_debug1;
int debug_propcase_show;
int debug_propcase_page;
int debug_vals_show;

static int dfirst;

void conf_load_defaults()
{
    register int i;

    conf.show_osd = 1;
    conf.save_raw = 0;
    conf.script_shoot_delay = 20;
    conf.show_histo = 0;
    conf.raw_fileno = 1000;
    for (i=0; i<SCRIPT_NUM_PARAMS; ++i) {
        conf.ubasic_vars[i] = 0;
    }
    conf.script_file[0]=0;

    conf.show_dof = 0;
    conf.batt_volts_max = get_vbatt_max();
    conf.batt_volts_min = get_vbatt_min();
    conf.batt_step_25 = 1;
    conf.batt_perc_show = 1;
    conf.batt_volts_show = 0;
    conf.batt_icon_show = 1;

    conf.show_state = 1;
    conf.show_values = 0;
    conf.show_overexp = 1;

    conf.histo_mode = HISTO_MODE_LINEAR;
    histogram_set_mode(conf.histo_mode);
    conf.histo_auto_ajust = 1;
    conf.histo_ignore_boundary = 5;
    conf.histo_layout = OSD_HISTO_LAYOUT_A;
    if (conf.histo_layout==OSD_HISTO_LAYOUT_Y || conf.histo_layout==OSD_HISTO_LAYOUT_Y_argb) {
        histogram_set_main(HISTO_Y);
    } else {
        histogram_set_main(HISTO_RGB);
    }

    conf.histo_pos.x=319-HISTO_WIDTH;
    conf.histo_pos.y=45;
    conf.dof_pos.x=5*FONT_WIDTH;
    conf.dof_pos.y=0;
    conf.batt_icon_pos.x=178;
    conf.batt_icon_pos.y=4;
    conf.batt_txt_pos.x=vid_get_bitmap_width()-8*FONT_WIDTH-2;
    conf.batt_txt_pos.y=vid_get_bitmap_height()-64;
    conf.mode_state_pos.x=vid_get_bitmap_width()-4*FONT_WIDTH;
    conf.mode_state_pos.y=45;
    conf.values_pos.x=vid_get_bitmap_width()-9*FONT_WIDTH;
    conf.values_pos.y=6*FONT_HEIGHT;

    conf.histo_color = MAKE_COLOR(COLOR_BG, COLOR_WHITE);
    conf.osd_color = MAKE_COLOR(COLOR_BG, COLOR_FG);
    conf.batt_icon_color = COLOR_WHITE;
    conf.menu_color = MAKE_COLOR(COLOR_BG, COLOR_FG);
}

static void do_save(int fd)
{
    long t;
    t = CNF_MAGICK_VALUE;
    write(fd, &t, 4);
    write(fd, &conf, sizeof(Conf));
    write(fd, &t, 4);
}

static int do_restore(int fd)
{
    int rcnt;
    long t;
    Conf conf_tmp;

    /* read magick value */
    rcnt = read(fd, &t, 4);
    if ((rcnt != 4) || (t != CNF_MAGICK_VALUE))
        return 1;

    /* read raw file number counter */
    rcnt = read(fd, &conf_tmp, sizeof(Conf));
    if (rcnt != sizeof(Conf))
        return 1;

    /* read magick value */
    t=0;
    rcnt = read(fd, &t, 4);
    if ((rcnt != 4) || (t != CNF_MAGICK_VALUE))
        return 1;

    conf_tmp.raw_fileno = (conf_tmp.raw_fileno|3) + 1;
    conf=conf_tmp;

    return 0;
}


void conf_save(int force)
{
    int fd;

    if (((conf.raw_fileno & 3) == 0) || (dfirst == 1) || force){
	dfirst = 0;

	fd = open(FN_COUNTER, O_WRONLY|O_CREAT, 0777);
	if (fd >= 0){
	    do_save(fd);
	    close(fd);
	}
    }
}


void conf_restore()
{
    int fd;

    fd = open(FN_COUNTER, O_RDONLY, 0777);
    if (fd >= 0){
	if (do_restore(fd))
	    conf_load_defaults();
        else {
            histogram_set_mode(conf.histo_mode);
            if (conf.histo_layout==OSD_HISTO_LAYOUT_Y || conf.histo_layout==OSD_HISTO_LAYOUT_Y_argb) {
                histogram_set_main(HISTO_Y);
            } else {
                histogram_set_main(HISTO_RGB);
            }
        }
	close(fd);
    } else {
	conf_load_defaults();
    }
    dfirst = 1;

    script_load(conf.script_file);
}

