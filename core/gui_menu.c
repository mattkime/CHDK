#include "stdlib.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"
#include "conf.h"
#include "ubasic.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_menu.h"

//-------------------------------------------------------------------
#define MENUITEM_MASK 0xf

#define MENUSTACK_MAXDEPTH 2

//-------------------------------------------------------------------
typedef struct {
    CMenuItem *menu;
    int curpos;
} CMenuItemStacked;

//-------------------------------------------------------------------

static CMenuItem *curr_menu;
static CMenuItemStacked gui_menu_stack[MENUSTACK_MAXDEPTH];
static unsigned int gui_menu_stack_ptr;
static unsigned int gui_menu_curr_item;


//-------------------------------------------------------------------
void gui_menu_init(CMenuItem *menu_ptr) {
    curr_menu = menu_ptr;
    gui_menu_curr_item = 0;
    gui_menu_stack_ptr = 0;
}

//-------------------------------------------------------------------
void gui_menu_kbd_process() {
    switch (kbd_get_clicked_key()) {
    case KEY_UP:
        if (gui_menu_curr_item>1)
            gui_menu_curr_item--;
        else
            while (curr_menu[gui_menu_curr_item+1].text)
               ++gui_menu_curr_item;
        break;
    case KEY_DOWN:
        if (curr_menu[gui_menu_curr_item+1].text)
            gui_menu_curr_item++;
        else 
            gui_menu_curr_item = 1;
        break;
    case KEY_LEFT:{
        long v = *curr_menu[gui_menu_curr_item].value;

        switch (curr_menu[gui_menu_curr_item].type & MENUITEM_MASK){
        case MENUITEM_INT:
            v -= 1;
            if ( curr_menu[gui_menu_curr_item].type & MENUITEM_F_UNSIGNED){
                if (v < 0)
                    v = 0;
            }
            break;
        }
        *curr_menu[gui_menu_curr_item].value = v;
        break;
    }
    case KEY_RIGHT:
        switch (curr_menu[gui_menu_curr_item].type & MENUITEM_MASK){
        case MENUITEM_INT:
            *curr_menu[gui_menu_curr_item].value += 1;
            break;
        }
        break;
    case KEY_SET:
        switch (curr_menu[gui_menu_curr_item].type & MENUITEM_MASK){
        case MENUITEM_BOOL:
            *curr_menu[gui_menu_curr_item].value =
                    !(*curr_menu[gui_menu_curr_item].value);
            break;
        case MENUITEM_PROC:{
            void (*proc)();
            proc = (void*)curr_menu[gui_menu_curr_item].value;
            proc();
            gui_menu_curr_item = 0;
            return;
            }
        case MENUITEM_SUBMENU:
            gui_menu_stack[gui_menu_stack_ptr].menu = curr_menu;
            gui_menu_stack[gui_menu_stack_ptr].curpos = gui_menu_curr_item;
            curr_menu = (void*)curr_menu[gui_menu_curr_item].value;
            gui_menu_curr_item = 0;
            gui_menu_stack_ptr++;
            // FIXME check on stack overrun;
            if (gui_menu_stack_ptr > MENUSTACK_MAXDEPTH){
                draw_txt_string(0, 0, "E1", MAKE_COLOR(COLOR_RED, COLOR_YELLOW));
                gui_menu_stack_ptr = 0;
            }
            draw_restore();
            gui_force_restore();
            break;
        case MENUITEM_UP:
            if (gui_menu_stack_ptr > 0){
                gui_menu_stack_ptr--;
                curr_menu = gui_menu_stack[gui_menu_stack_ptr].menu;
                gui_menu_curr_item = gui_menu_stack[gui_menu_stack_ptr].curpos;
                draw_restore();
                gui_force_restore();
            }
            break;
        }
        break;
    }
}

//-------------------------------------------------------------------
void gui_menu_draw() {
    static char tbuf[64];
    int imenu;
    int c=3,r=2;
    int l;
    int itemh;
    const int itemw = 37;
    color cl;
    char cb, ce;


    for (imenu=0; curr_menu[imenu].text; imenu++){
        itemh = 0;
        cl = (gui_menu_curr_item == imenu) ? MAKE_COLOR(COLOR_SELECTED_BG, COLOR_SELECTED_FG) : MAKE_COLOR(COLOR_BG, COLOR_FG);
        cb = (gui_menu_curr_item==imenu)?'\x10':' ';
        ce = (gui_menu_curr_item==imenu)?'\x11':' ';

        switch (curr_menu[imenu].type & MENUITEM_MASK) {
        case MENUITEM_INFO:
            l = strlen(curr_menu[imenu].text);
            draw_txt_string(c+(itemw-l)/2, r, curr_menu[imenu].text, MAKE_COLOR(COLOR_BG, COLOR_FG));
            itemh=2;
            draw_txt_char(c,r,cb, (gui_menu_curr_item==imenu)?cl:MAKE_COLOR(COLOR_TRANSPARENT, COLOR_TRANSPARENT));
            draw_txt_char(c+itemw-1,r,ce, (gui_menu_curr_item==imenu)?cl:MAKE_COLOR(COLOR_TRANSPARENT, COLOR_TRANSPARENT));
            break;
        case MENUITEM_BOOL:
            sprintf(tbuf, "%c%-31s [%c]%c", cb, curr_menu[imenu].text,
                (*curr_menu[imenu].value) ? '\xfe': ' ', ce);
            draw_txt_string(c, r, tbuf, cl);
            itemh=1;
            break;
        case MENUITEM_INT:
            sprintf(tbuf, "%c%-27s [%5d]%c", cb, curr_menu[imenu].text,
                *curr_menu[imenu].value, ce);
            draw_txt_string(c, r, tbuf, cl);
            itemh=1;
            break;
        case MENUITEM_UP:
        case MENUITEM_SUBMENU:
        case MENUITEM_PROC:
        case MENUITEM_TEXT:
            sprintf(tbuf, "%c%-35s%c", cb, curr_menu[imenu].text, ce);
            draw_txt_string(c, r, tbuf, cl);
            itemh=1;
            break;
        }
        r+=itemh;
    }
}

