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
#define MENUSTACK_MAXDEPTH  3

#define NUM_LINES           8

//-------------------------------------------------------------------
typedef struct {
    CMenu       *menu;
    int         curpos;
    int         toppos;
} CMenuStacked;

//-------------------------------------------------------------------

static CMenu        *curr_menu;
static CMenuStacked gui_menu_stack[MENUSTACK_MAXDEPTH];
static unsigned int gui_menu_stack_ptr;
static int          gui_menu_curr_item;
static int          gui_menu_top_item;
static int          gui_menu_redraw;

static coord        x, y, w=37;

//-------------------------------------------------------------------
void gui_menu_init(CMenu *menu_ptr) {
    curr_menu = menu_ptr;
    gui_menu_curr_item = -1;
    gui_menu_top_item = 0;
    gui_menu_stack_ptr = 0;
    
    x = (screen_width/FONT_WIDTH-w)>>1;
    y = (screen_height/FONT_HEIGHT-NUM_LINES)>>1;
    
    gui_menu_redraw=2;
}

//-------------------------------------------------------------------
void gui_menu_kbd_process() {
    switch (kbd_get_clicked_key()) {
        case KEY_UP:
            if (gui_menu_curr_item>0) {
                if (gui_menu_curr_item-1==gui_menu_top_item && gui_menu_top_item>0) 
                    --gui_menu_top_item;
                --gui_menu_curr_item;
            } else {
                int i;
                while (curr_menu->menu[gui_menu_curr_item+1].text)
                    ++gui_menu_curr_item;
                gui_menu_top_item = gui_menu_curr_item - NUM_LINES +1;
                if (gui_menu_top_item<0) gui_menu_top_item=0;
            }
            gui_menu_redraw=1;
            break;
        case KEY_DOWN:
            if (curr_menu->menu[gui_menu_curr_item+1].text) {
                int i;
                for (i=0; i<NUM_LINES-1 && curr_menu->menu[gui_menu_top_item+i].text; ++i);
                if (i==NUM_LINES-1 && curr_menu->menu[gui_menu_top_item+i].text 
                    && gui_menu_top_item+i-1==gui_menu_curr_item && curr_menu->menu[gui_menu_top_item+i+1].text)
                    ++gui_menu_top_item;
                ++gui_menu_curr_item;
            } else {
                gui_menu_curr_item = gui_menu_top_item = 0;
            }
            gui_menu_redraw=1;
            break;
        case KEY_LEFT:
            if (gui_menu_curr_item>=0) {
                switch (curr_menu->menu[gui_menu_curr_item].type & MENUITEM_MASK) {
                    case MENUITEM_INT:
                        *(curr_menu->menu[gui_menu_curr_item].value) -= 1;
                        if ( curr_menu->menu[gui_menu_curr_item].type & MENUITEM_F_UNSIGNED) {
                            if (*(curr_menu->menu[gui_menu_curr_item].value) < 0) 
                                *(curr_menu->menu[gui_menu_curr_item].value) = 0;
                        }
                        gui_menu_redraw=1;
                        break;
                    }
            }
            break;
        case KEY_RIGHT:
            if (gui_menu_curr_item>=0) {
                switch (curr_menu->menu[gui_menu_curr_item].type & MENUITEM_MASK){
                    case MENUITEM_INT:
                        *(curr_menu->menu[gui_menu_curr_item].value) += 1;
                        gui_menu_redraw=1;
                        break;
                }
            }
            break;
        case KEY_SET:
            if (gui_menu_curr_item>=0) {
                switch (curr_menu->menu[gui_menu_curr_item].type & MENUITEM_MASK){
                    case MENUITEM_BOOL:
                        *(curr_menu->menu[gui_menu_curr_item].value) =
                                !(*(curr_menu->menu[gui_menu_curr_item].value));
                        gui_menu_redraw=1;
                        break;
                    case MENUITEM_PROC:
                    	if (curr_menu->menu[gui_menu_curr_item].value) {
                            ((void (*)())(curr_menu->menu[gui_menu_curr_item].value))();
                            gui_menu_curr_item = -1;
                            gui_menu_redraw=2;
                        }
                        break;
                    case MENUITEM_SUBMENU:
                        gui_menu_stack[gui_menu_stack_ptr].menu = curr_menu;
                        gui_menu_stack[gui_menu_stack_ptr].curpos = gui_menu_curr_item;
                        gui_menu_stack[gui_menu_stack_ptr].toppos = gui_menu_top_item;
                        curr_menu = (void*)(curr_menu->menu[gui_menu_curr_item].value);
                        gui_menu_curr_item = -1;
                        gui_menu_stack_ptr++;
                        // FIXME check on stack overrun;
                        if (gui_menu_stack_ptr > MENUSTACK_MAXDEPTH){
                            draw_txt_string(0, 0, "E1", MAKE_COLOR(COLOR_RED, COLOR_YELLOW));
                            gui_menu_stack_ptr = 0;
                        }
                        gui_menu_redraw=2;
                        draw_restore();
                        gui_force_restore();
                        break;
                    case MENUITEM_UP:
                        if (gui_menu_stack_ptr > 0){
                            gui_menu_stack_ptr--;
                            curr_menu = gui_menu_stack[gui_menu_stack_ptr].menu;
                            gui_menu_curr_item = gui_menu_stack[gui_menu_stack_ptr].curpos;
                            gui_menu_top_item  = gui_menu_stack[gui_menu_stack_ptr].toppos;
                            gui_menu_redraw=2;
                            draw_restore();
                            gui_force_restore();
                        }
                        break;
                }
            }
            break;
    }
}

//-------------------------------------------------------------------
void gui_menu_draw_initial() {
    static const char *f=" *** ";
    int l, xx;
    
    l = strlen(curr_menu->title);
    xx=x+((w-l)>>1);
    draw_txt_string(xx-5, y-2, f, MAKE_COLOR(COLOR_BG, COLOR_FG));
    draw_txt_string(xx, y-2, curr_menu->title, MAKE_COLOR(COLOR_BG, COLOR_FG));
    draw_txt_string(xx+l, y-2, f, MAKE_COLOR(COLOR_BG, COLOR_FG));
}

//-------------------------------------------------------------------
void gui_menu_draw() {
    static char tbuf[64];
    int imenu, i;
    color cl;
    char cb, ce;

    if (gui_menu_redraw) {
        if (gui_menu_redraw==2)
            gui_menu_draw_initial();

        for (imenu=gui_menu_top_item, i=0; curr_menu->menu[imenu].text && i<NUM_LINES; ++imenu, ++i){
            cl = (gui_menu_curr_item==imenu)?MAKE_COLOR(COLOR_SELECTED_BG, COLOR_SELECTED_FG):MAKE_COLOR(COLOR_BG, COLOR_FG);
            cb = (gui_menu_curr_item==imenu)?'\x10':' ';
            ce = (gui_menu_curr_item==imenu)?'\x11':' ';

            switch (curr_menu->menu[imenu].type & MENUITEM_MASK) {
            case MENUITEM_BOOL:
                sprintf(tbuf, "%c%-31s [%c]%c", cb, curr_menu->menu[imenu].text,
                    (*(curr_menu->menu[imenu].value))?'\xfe':' ', ce);
                draw_txt_string(x, y+i, tbuf, cl);
                break;
            case MENUITEM_INT:
                sprintf(tbuf, "%c%-27s [%5d]%c", cb, curr_menu->menu[imenu].text,
                    *(curr_menu->menu[imenu].value), ce);
                draw_txt_string(x, y+i, tbuf, cl);
                break;
            case MENUITEM_UP:
            case MENUITEM_SUBMENU:
            case MENUITEM_PROC:
            case MENUITEM_TEXT:
                sprintf(tbuf, "%c%-35s%c", cb, curr_menu->menu[imenu].text, ce);
                draw_txt_string(x, y+i, tbuf, cl);
                break;
            }
        }
        
        gui_menu_redraw=0;
    }
}

