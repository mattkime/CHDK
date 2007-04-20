#ifndef GUI_OSD_H
#define GUI_OSD_H

//-------------------------------------------------------------------
// A - RGB
#define OSD_HISTO_LAYOUT_A              0
#define OSD_HISTO_LAYOUT_Y              1
#define OSD_HISTO_LAYOUT_A_Y            2
#define OSD_HISTO_LAYOUT_R_G_B          3
#define OSD_HISTO_LAYOUT_A_yrgb         4
#define OSD_HISTO_LAYOUT_Y_argb         5
#define OSD_HISTO_LAYOUT_BLEND          6

//-------------------------------------------------------------------
extern void gui_osd_init();
extern void gui_osd_kbd_process();
extern void gui_osd_draw();

extern void gui_osd_zebra_init();

extern void gui_osd_draw_histo();
extern void gui_osd_draw_dof();
extern void gui_osd_draw_state();
extern void gui_osd_draw_values();
extern void gui_osd_draw_clock();
extern int  gui_osd_draw_zebra();

//-------------------------------------------------------------------
#endif
