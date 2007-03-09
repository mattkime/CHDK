#ifndef GUI_MENU_H
#define GUI_MENU_H

//-------------------------------------------------------------------
#define MENUITEM_INFO       1
#define MENUITEM_BOOL       2
#define MENUITEM_INT        3
#define MENUITEM_SUBMENU    4
#define MENUITEM_PROC       5
#define MENUITEM_UP         6
#define MENUITEM_TEXT       7

#define MENUITEM_F_MASK     0xf0
#define MENUITEM_F_UNSIGNED 0x10

//-------------------------------------------------------------------
typedef struct {
    const char *text;
    int type;
    int *value;
} CMenuItem;


//-------------------------------------------------------------------
extern void gui_menu_init(CMenuItem *menu_ptr);
extern void gui_menu_kbd_process();
extern void gui_menu_draw();

//-------------------------------------------------------------------
#endif
