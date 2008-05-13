#ifndef DGMOD_H
#define DGMOD_H


//--- Constants -----------------------------------------------------
#define DG_HV_SELTYPE_NONE  0
#define DG_HV_SELTYPE_CHAR  1
#define DG_HV_SELTYPE_SHORT 2
#define DG_HV_SELTYPE_LONG  4
#define DG_HV_SELTYPE_DWORD 8

//--- Macros --------------------------------------------------------

//--- Structs -------------------------------------------------------
typedef struct {
	int led_num;
	int action;
	int brightness;
	int blink_count;
} Led_control;

typedef struct {
	volatile long *addr;
	volatile long *sel_addr;
	long sel_type;
	char *pixbuf;
	char *cambuf;
	// history as circular array?
} Hexviewerdata;

//--- Functions -----------------------------------------------------
extern void dg_init();
extern void dg_bright_submenu_change(unsigned int item);
extern void dg_bright_setcurlcd(int arg);
extern void dg_bright_setcurevf(int arg);

extern void dg_br_turnondisp(int arg);
extern void dg_br_turnoffdisp(int arg);
extern void dg_br_turnonback(int arg);
extern void dg_br_turnoffback(int arg);

extern void dg_adjust_is_init();
extern void dg_adjust_is_kbd_process();
extern void dg_adjust_is_draw();

extern void dg_show_is_init();
extern void dg_show_is_kbd_process();
extern void dg_show_is_draw();

extern void dg_show_is2_init();
extern void dg_show_is2_kbd_process();
extern void dg_show_is2_draw();

extern void dg_orientation_demo_init();
extern void dg_orientation_demo_kbd_process();
extern void dg_orientation_demo_draw();

extern void dg_plm_post(int arg);
extern void dg_plm_brightness(int arg);

extern void dg_quick_debugger(int arg);

extern void dg_disco(int arg);

extern void dg_hexviewer_init();
extern void dg_hexviewer_kbd_process();
extern void dg_hexviewer_draw();

extern void dg_game_test();


extern long *_GetShutterReadyStateVar(long);


//--- Variables -----------------------------------------------------
extern int dgconf_br_canlcdlow;
extern int dgconf_br_canlcdhigh;
extern int dgconf_br_canevflow;
extern int dgconf_br_canevfhigh;
extern int dgconf_br_curlcd;
extern int dgconf_br_curevf;
extern Led_control dgconf_lc;


#endif
