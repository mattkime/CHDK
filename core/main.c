#include "platform.h"
#include "core.h"
#include "conf.h"
#include "keyboard.h"
#include "stdlib.h"
#include "gui.h"
#include "histogram.h"
#include "raw.h"

static long (*prev_hhandler)(long a);
static int raw_need_postprocess;

#if 0
int taskop_txt_p;
char taskop_txt[6][32];
#endif

void core_hook_task_create(void *tcb)
{
#if 0
    char *name = (char*)(*(long*)((char*)tcb+0x34));
    strcpy(taskop_txt[taskop_txt_p]+1, name);
    taskop_txt[taskop_txt_p][0] = 'S';
    taskop_txt_p++;
    if (taskop_txt_p>5)
	taskop_txt_p = 0;
#endif
}

void core_hook_task_delete(void *tcb)
{
#if 0
    char *name = (char*)(*(long*)((char*)tcb+0x34));
    strcpy(taskop_txt[taskop_txt_p]+1, name);
    taskop_txt[taskop_txt_p][0] = 'E';

    taskop_txt_p++;
    if (taskop_txt_p>5)
	taskop_txt_p = 0;
#endif
}

void dump_memory()
{
    int fd;
    static int cnt=0;
    static char fn[32];

//((void (*)(int v))(0xFFC5BCC0))(0x7F); //Make_BOOTDISK
    started();

	sprintf(fn, "A/DCIM/100CANON/CRW_%04d.JPG", cnt++);
	fd = fopen(fn, "w+");
	if (fd) {
//            fwrite((void*)vid_get_viewport_fb(), 360*240*3, 1, fd);
//            fwrite((void*)vid_get_bitmap_fb(), 360*240, 1, fd);
	    fwrite((void*)0, 1, 0x1900, fd);
	    fwrite((void*)0x1900, 1, 32*1024*1024-0x1900, fd);
	    fclose(fd);
	}
    finished();
}

static void myhook1(long a)
{
    // only this caller allowed
    if (__builtin_return_address(0) == hook_raw_ret_addr()){
	raw_need_postprocess = raw_savefile();
    }
    prev_hhandler(a);
}

void core_spytask()
{
    long *p = hook_raw_fptr();
    int cnt = 0;

    raw_need_postprocess = 0;

    SleepTask(1000);

    conf_restore();
    gui_init();

    started();
    SleepTask(50);
    finished();

    while (1){
	if (((cnt++) & 3) == 0)
	    gui_redraw();

	histogram_process();

	taskLock();
	if ((*p) != (long)myhook1){
	    prev_hhandler = (void*)*p;
	    *p=(long)myhook1;
	}
	taskUnlock();

	if ((state_shooting_progress == SHOOTING_PROGRESS_PROCESSING) && (!shooting_in_progress())) {
	    state_shooting_progress = SHOOTING_PROGRESS_DONE;
            if (raw_need_postprocess) raw_postprocess();
        }

	SleepTask(20);
    }
}

