#ifndef GUI_DEBUG_H
#define GUI_DEBUG_H

//-------------------------------------------------------------------
//-------------------------------------------------------------------
extern void gui_debug_init(void* st_addr);
extern void gui_debug_kbd_process();
extern void gui_debug_draw();

extern void debug_dump_information();
extern void debug_dump_arm();

extern int prefetch_count;
extern int data_count;


//-------------------------------------------------------------------
#endif
