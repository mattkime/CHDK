#ifndef GUI_H
#define GUI_H

enum Gui_Mode { GUI_MODE_NONE = 0,
                GUI_MODE_ALT,
                GUI_MODE_MENU,
                GUI_MODE_PALETTE,
                GUI_MODE_MBOX,
                GUI_MODE_REVERSI,
                GUI_MODE_DEBUG,
                GUI_MODE_FSELECT };

extern void gui_redraw();
extern void gui_force_restore();

extern enum Gui_Mode gui_get_mode();
extern void gui_set_mode(enum Gui_Mode mode);


#endif
