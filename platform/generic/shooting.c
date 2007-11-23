#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"
#include "math.h"
#include "stdlib.h"
#include "conf.h"


#define SS_SIZE (sizeof(shutter_speeds_table)/sizeof(shutter_speeds_table[0]))
#define SSID_MIN (shutter_speeds_table[0].id)
#define SSID_MAX (shutter_speeds_table[SS_SIZE-1].id)

#define AS_SIZE (sizeof(aperture_sizes_table)/sizeof(aperture_sizes_table[0]))
#define ASID_MIN (aperture_sizes_table[0].id)
#define ASID_MAX (aperture_sizes_table[AS_SIZE-1].id)

#define ISO_SIZE (sizeof(iso_table)/sizeof(iso_table[0]))
#define ISO_MIN (iso_table[0].id)
#define ISO_MAX (iso_table[ISO_SIZE-1].id)

#if defined(CAMERA_a570) || defined(CAMERA_a560)
 #define PROPCASE_TV		264
 #define PROPCASE_CAMERA_TV	262
 #define PROPCASE_AV		26
 #define PROPCASE_ISO		149
 #define PROPCASE_SHOOTING	206
#else
 #define PROPCASE_TV		40
 #define PROPCASE_CAMERA_TV	69
 #define PROPCASE_AV		39
 #define PROPCASE_ISO		21
 #define PROPCASE_SHOOTING	205
#endif

int shooting_get_tv()
{
    short int tvv;
    long i;
    _GetPropertyCase(PROPCASE_TV, &tvv, sizeof(tvv));
    for (i=0;i<SS_SIZE;i++){
	if (shutter_speeds_table[i].prop_id == tvv)
	    return shutter_speeds_table[i].id;
    }
    return 0;
}

const ShutterSpeed *shooting_get_tv_line()
{
    short int tvv;
    long i;
    _GetPropertyCase(PROPCASE_TV, &tvv, sizeof(tvv));
    for (i=0;i<SS_SIZE;i++){
	if (shutter_speeds_table[i].prop_id == tvv)
	    return &shutter_speeds_table[i];
    }
    return 0;

}

void shooting_set_tv(int v)
{
    long i;
//    if ((v<SSID_MIN) || (v>SSID_MAX))
//	return;


    for (i=0;i<SS_SIZE;i++){
	if (shutter_speeds_table[i].id == v){
	    short int vv = shutter_speeds_table[i].prop_id;
	    _SetPropertyCase(PROPCASE_TV, &vv, sizeof(vv));
	    return;
	}
    }

}

void shooting_set_tv_rel(int v)
{
    int cv = shooting_get_tv();
    shooting_set_tv(cv+v);
}

int shooting_get_av()
{
    short int avv;
    long i;
    _GetPropertyCase(PROPCASE_AV, &avv, sizeof(avv));
    for (i=0;i<AS_SIZE;i++){
	if (aperture_sizes_table[i].prop_id == avv)
	    return aperture_sizes_table[i].id;
    }
    return 0;
}

int shooting_get_real_av() {
    return (int)(((double)pow(1.4142135623730950488016887242097/* sqrt(2) */, ((double)_GetCurrentAvValue())/96.0))*100.0);
}

void shooting_set_av(int v)
{
    long i;

//    if ((v<ASID_MIN) || (v>ASID_MAX))
//	return;

    for (i=0;i<AS_SIZE;i++){
	if (aperture_sizes_table[i].id == v){
	    short int vv = aperture_sizes_table[i].prop_id;
	    _SetPropertyCase(PROPCASE_AV, &vv, sizeof(vv));
	    return;
	}
    }
}

void shooting_set_av_rel(int v)
{
    int cv = shooting_get_av();
    shooting_set_av(cv+v);
}

int shooting_get_iso()
{
    short int isov;
    long i;
    _GetPropertyCase(PROPCASE_ISO, &isov, sizeof(isov));
    for (i=0;i<ISO_SIZE;i++){
	if (iso_table[i].prop_id == isov)
	    return iso_table[i].id;
    }
    return 0;
}

void shooting_set_iso(int v)
{
    long i;

    for (i=0;i<ISO_SIZE;i++){
	if (iso_table[i].id == v){
	    short int vv = iso_table[i].prop_id;
	    _SetPropertyCase(PROPCASE_ISO, &vv, sizeof(vv));
	    return;
	}
    }
}

void shooting_set_iso_direct(int v)
{
    short int vv = v;
    _SetPropertyCase(PROPCASE_ISO, &vv, sizeof(vv));
}

int shooting_in_progress()
{
    int t = 0;
    _GetPropertyCase(PROPCASE_SHOOTING, &t, 4);
    return t != 0;
}

int shooting_is_flash_ready()
{
    int t = 0;
/* well, I'm not sure what's exactly is happening here
 * but it works for a610-100e
 */
    _GetPropertyCase(204, &t, 4);
    if (t == 3){
	_GetPropertyCase(221, &t, 4);
	return (t==1) && _IsStrobeChargeCompleted();
    }
    return 1;
}

long get_file_counter()
{
#ifndef PARAM_FILE_COUNTER
#	error Please define PARAM_FILE_COUNTER in platform`s shooting.c!
#endif

    long v = 0;
    get_parameter_data(PARAM_FILE_COUNTER, &v, 4);
    return v;
}

int shooting_get_zoom() {
    return lens_get_zoom_point();
}

void shooting_set_zoom(int v) {
    long dist;

    dist = lens_get_focus_pos();
    lens_set_zoom_point(v);
    lens_set_focus_pos(dist);
}

void shooting_set_zoom_rel(int v) {
    int cv = shooting_get_zoom();
    shooting_set_zoom(cv+v);
}

void shooting_set_zoom_speed(int v) {
    lens_set_zoom_speed(v);
}

int shooting_get_focus() {
    return lens_get_focus_pos();
}

void shooting_set_focus(int v) {
    lens_set_focus_pos(v);
}

void shooting_video_bitrate_change(int v){
 int m[]={1,2,3,4,5,6,7,8,10,12};
 if (v>=(sizeof(m)/sizeof(m[0]))) v=(sizeof(m)/sizeof(m[0]))-1;
 change_video_tables(m[v],4);
}

short int get_camera_tv(void){
  short int vv;
 _GetPropertyCase(PROPCASE_CAMERA_TV, &vv, sizeof(vv));
 return vv;
}

void set_camera_tv(short int v){
  short int vv=v;
 _SetPropertyCase(PROPCASE_CAMERA_TV, &vv, sizeof(vv));
}


static short save_tv;
static int shoot_counter;
static short delta_tv, step_tv; 

void tv_bracketing(int stage){
 int m=mode_get()&MODE_SHOOTING_MASK;
 if (m==MODE_STITCH) return;
 if (stage!=SHOOTING_PROGRESS_PROCESSING) { // first shoot
  save_tv=get_camera_tv();
  shoot_counter=1;
  step_tv=32*conf.tv_bracketing;
  delta_tv=step_tv;
 }
 else {
  shoot_counter++;      // other shoots
  if (shoot_counter&1) delta_tv+=step_tv;
 }
 set_camera_tv(shoot_counter&1 ? save_tv+delta_tv: save_tv-delta_tv);
}

