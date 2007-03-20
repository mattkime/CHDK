#ifndef GUI_MENU_H
#define GUI_MENU_H

//-------------------------------------------------------------------
#define MENUITEM_MASK       0x0f
#define MENUITEM_BOOL       1
#define MENUITEM_INT        2
#define MENUITEM_SUBMENU    3
#define MENUITEM_PROC       4
#define MENUITEM_UP         5
#define MENUITEM_TEXT       6

#define MENUITEM_F_MASK     0xf0
#define MENUITEM_F_UNSIGNED 0x10

//-------------------------------------------------------------------
typedef struct {
    const char          *text;
    int                 type;
    int                 *value;
} CMenuItem;

typedef struct {
    const char          *title;
    const CMenuItem     menu[];
} CMenu;


//-------------------------------------------------------------------
extern void gui_menu_init(CMenu *menu_ptr);
extern void gui_menu_kbd_process();
extern void gui_menu_draw();

//-------------------------------------------------------------------
#endif
