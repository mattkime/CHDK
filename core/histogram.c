#include "stdlib.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"
#include "conf.h"
#include "math.h"
#include "ubasic.h"
#include "gui.h"
#include "gui_draw.h"
#include "histogram.h"

#define HISTOGRAM_IDLE_STAGE (6)

static float identity(float x);
static float locarithmic(float x);


unsigned char histogram[HISTO_WIDTH];
long exposition_thresh;
long under_exposed;
long over_exposed;
long histo_magnification;

static unsigned int histogram_proc[HISTO_WIDTH];
static float histo_max_invw, histo_max_center_invw;
static long histogram_stage;
static unsigned int histo_max, histo_max_center;
static float (*histogram_transform)(float) = identity;


float identity(float x)
{
    return x;
}

float locarithmic(float x) {
    return log(x);
}

void histogram_set_mode(unsigned int mode) {
    switch (mode) {
        case HISTO_MODE_LOG: 
            histogram_transform = locarithmic; 
            break;
        case HISTO_MODE_LINEAR: 
        default:
            histogram_transform = identity; 
            break;
    }
}


extern int mkf;
void histogram_process()
{
    unsigned char *img;
    int i, hi;

//    if (kbd_is_key_pressed(KEY_SHOOT_HALF)){
	img = vid_get_viewport_fb();
//    } else {
//	img = vid_get_viewport_live_fb();
//    }

    switch (histogram_stage) {
    case 0:
	for (i=0;i<HISTO_WIDTH;i++){
	    histogram_proc[i]=0;
	}
	histo_max = histo_max_center = 0;

	histogram_stage=1;
	break;
    case 1:

	for (i=0;i<screen_size;i+=3){
	    hi = img[i*3+1]*HISTO_WIDTH/256;
	    histogram_proc[hi]++;

	    if (histo_max<histogram_proc[hi])
		histo_max=histogram_proc[hi];
            if (histo_max_center<histogram_proc[hi] && hi>=conf.histo_ignore_boundary && hi<HISTO_WIDTH-conf.histo_ignore_boundary)
		histo_max_center=histogram_proc[hi];
	}

	histogram_stage=2;
	break;
    case 2:

	for (i=1;i<screen_size;i+=3){
	    hi = img[i*3+1]*HISTO_WIDTH/256;
	    histogram_proc[hi]++;

	    if (histo_max<histogram_proc[hi])
		histo_max=histogram_proc[hi];
            if (histo_max_center<histogram_proc[hi] && hi>=conf.histo_ignore_boundary && hi<HISTO_WIDTH-conf.histo_ignore_boundary)
		histo_max_center=histogram_proc[hi];
	}

	histogram_stage=3;
	break;
    case 3:

	for (i=2;i<screen_size;i+=3){
	    hi = img[i*3+1]*HISTO_WIDTH/256;
	    histogram_proc[hi]++;

	    if (histo_max<histogram_proc[hi])
		histo_max=histogram_proc[hi];
            if (histo_max_center<histogram_proc[hi] && hi>=conf.histo_ignore_boundary && hi<HISTO_WIDTH-conf.histo_ignore_boundary)
		histo_max_center=histogram_proc[hi];
	}

	histogram_stage=4;
	break;
    case 4:

	if (histo_max > 0){
	    histo_max_invw = ((float)HISTO_HEIGHT)/histogram_transform((float)histo_max);

	    under_exposed = (histogram_proc[0]*8+histogram_proc[1]*4+histogram_proc[2]) >
		    exposition_thresh;

	    over_exposed = (histogram_proc[HISTO_WIDTH-3]+histogram_proc[HISTO_WIDTH-2]*4+
		    histogram_proc[HISTO_WIDTH-1]*8) > exposition_thresh;
	} else {
	    histo_max_invw = 0.0f;
	    over_exposed = 0;
	    under_exposed = 1;
	}
        if (histo_max_center > 0){
            histo_max_center_invw = ((float)HISTO_HEIGHT)/histogram_transform((float)histo_max_center);
        } else {
            histo_max_center_invw = 0.0f;
        }
	histogram_stage=5;
	state_expos_recalculated = 1;
	break;
    case 5:

        hi=0;
	for (i=0;i<HISTO_WIDTH;i++){
	    histogram[i] = (histogram_transform((float)histogram_proc[i]))*histo_max_center_invw;
            if (histogram[i] > HISTO_HEIGHT)
                histogram[i] = HISTO_HEIGHT;
            hi+=histogram[i];
	}

        if (conf.histo_auto_ajust) {
            histo_magnification = hi*1000/(HISTO_HEIGHT*HISTO_WIDTH);
            if (histo_magnification<200) { // try to ajust if average level is less than 20%
                histo_magnification=200*1000/histo_magnification;
                for (i=0;i<HISTO_WIDTH;i++) {
                    histogram[i] = (histogram_transform((float)histogram_proc[i]))*histo_max_center_invw*histo_magnification/1000;
                    if (histogram[i] > HISTO_HEIGHT)
                        histogram[i] = HISTO_HEIGHT;
                }
            } else 
                histo_magnification=0;
        } else {
            histo_magnification=0;
        }

	histogram_stage=0;
	break;
    case HISTOGRAM_IDLE_STAGE:
	break;
    }

}

void histogram_stop()
{
    histogram_stage=HISTOGRAM_IDLE_STAGE;
}


void histogram_restart()
{
    histogram_stage = 0;
}


