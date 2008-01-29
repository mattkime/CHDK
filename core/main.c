#include "platform.h"
#include "core.h"
#include "conf.h"
#include "keyboard.h"
#include "stdlib.h"
#include "gui.h"
#include "histogram.h"
#include "raw.h"
#include "motion_detector.h"

static int raw_need_postprocess;
static volatile int spytask_can_start;

void core_hook_task_create(void *tcb)
{
}

void core_hook_task_delete(void *tcb)
{
char *name = (char*)(*(long*)((char*)tcb+0x34));
/*
#if defined(CAMERA_ixus700_sd500) || defined(CAMERA_a710)
 if (strcmp(name,"tStartupIm")==0) spytask_can_start=1;
#endif
*/
}


long core_get_noise_reduction_value()
{
    return conf.raw_nr;
}

static volatile long raw_data_available;

/* called from another process */
void core_rawdata_available()
{
    raw_data_available = 1;
}

void core_spytask()
{
    int cnt = 1;
    int i=0;

    raw_need_postprocess = 0;

    spytask_can_start=0;

    while((i++<200) && !spytask_can_start) msleep(10);

    started();
    msleep(50);
    finished();

    conf_restore();
    gui_init();
    md_init();

    mkdir("A/CHDK");
    mkdir("A/CHDK/FONTS");
    mkdir("A/CHDK/SCRIPTS");
    mkdir("A/CHDK/LANG");
    mkdir("A/CHDK/BOOKS");
    mkdir("A/CHDK/GRIDS");
    auto_started = 0;
    
    clear_override_values();
    
    if (conf.script_startup) script_autostart();				// remote autostart
    while (1){

	if (raw_data_available){
            raw_need_postprocess = raw_savefile();
	    hook_raw_save_complete();
	    raw_data_available = 0;
	    continue;
	}

	if (state_shooting_progress != SHOOTING_PROGRESS_PROCESSING) {
	    if (((cnt++) & 3) == 0)
	        gui_redraw();

	    histogram_process();
	}

	if ((state_shooting_progress == SHOOTING_PROGRESS_PROCESSING) && (!shooting_in_progress())) {
	    state_shooting_progress = SHOOTING_PROGRESS_DONE;
            if (raw_need_postprocess) raw_postprocess();
        }

	msleep(20);
    }
}

