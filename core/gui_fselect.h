#ifndef GUI_FSELECT_H
#define GUI_FSELECT_H

//-------------------------------------------------------------------
//-------------------------------------------------------------------
extern void gui_fselect_init(const char* dir, void (*on_select)());
extern char* gui_fselect_result();
extern void gui_fselect_kbd_process();
extern void gui_fselect_draw();

//-------------------------------------------------------------------
#endif