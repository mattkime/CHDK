#include "stdlib.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"
#include "conf.h"
#include "ubasic.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_palette.h"
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

static int          count;
static coord        x, y, w=37;
static unsigned char *item_color;

//-------------------------------------------------------------------
static void gui_menu_set_curr_menu(CMenu *menu_ptr, int top_item, int curr_item) {
    curr_menu = menu_ptr;
    gui_menu_top_item = top_item;
    gui_menu_curr_item = curr_item;
}

//-------------------------------------------------------------------
void gui_menu_init(CMenu *menu_ptr) {
    gui_menu_set_curr_menu(menu_ptr, 0, -1);
    gui_menu_stack_ptr = 0;
    
    x = (screen_width/FONT_WIDTH-w)>>1;
    y = (screen_height/FONT_HEIGHT-NUM_LINES)>>1;
    
    gui_menu_redraw=2;
}

//-------------------------------------------------------------------
static void gui_menu_color_selected(color clr) {
    *item_color = (unsigned char)(clr&0xFF);
    gui_menu_redraw=2;
    draw_restore();
    gui_force_restore();
}

//-------------------------------------------------------------------
void gui_menu_kbd_process() {
    switch (kbd_get_clicked_key()) {
        case KEY_UP:
            do {
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
            } while ((curr_menu->menu[gui_menu_curr_item].type & MENUITEM_MASK)==MENUITEM_TEXT || 
                     (curr_menu->menu[gui_menu_curr_item].type & MENUITEM_MASK)==MENUITEM_SEPARATOR);
            gui_menu_redraw=1;
            break;
        case KEY_DOWN:
            do {
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
            } while ((curr_menu->menu[gui_menu_curr_item].type & MENUITEM_MASK)==MENUITEM_TEXT || 
                     (curr_menu->menu[gui_menu_curr_item].type & MENUITEM_MASK)==MENUITEM_SEPARATOR);
            gui_menu_redraw=1;
            break;
        case KEY_LEFT:
            if (gui_menu_curr_item>=0) {
                switch (curr_menu->menu[gui_menu_curr_item].type & MENUITEM_MASK) {
                    case MENUITEM_INT:
                        switch (curr_menu->menu[gui_menu_curr_item].type & MENUITEM_ARG_MASK) {
                            case MENUITEM_ARG_INC:
                                *(curr_menu->menu[gui_menu_curr_item].value) -= curr_menu->menu[gui_menu_curr_item].arg;
                                break;
                            case MENUITEM_ARG_ADDR_INC:
                                *(curr_menu->menu[gui_menu_curr_item].value) -= *(int *)(curr_menu->menu[gui_menu_curr_item].arg);
                                break;
                            default:
                                *(curr_menu->menu[gui_menu_curr_item].value) -= 1;
                                break;
                        }
                        if ( curr_menu->menu[gui_menu_curr_item].type & MENUITEM_F_UNSIGNED) {
                            if (*(curr_menu->menu[gui_menu_curr_item].value) < 0) 
                                *(curr_menu->menu[gui_menu_curr_item].value) = 0;
                            if ( curr_menu->menu[gui_menu_curr_item].type & MENUITEM_F_MIN) {
                                if (*(curr_menu->menu[gui_menu_curr_item].value) < (unsigned short)(curr_menu->menu[gui_menu_curr_item].arg & 0xFFFF)) 
                                    *(curr_menu->menu[gui_menu_curr_item].value) = (unsigned short)(curr_menu->menu[gui_menu_curr_item].arg & 0xFFFF);
                            }
                        } else {
                            if ( curr_menu->menu[gui_menu_curr_item].type & MENUITEM_F_MIN) {
                                if (*(curr_menu->menu[gui_menu_curr_item].value) < (short)(curr_menu->menu[gui_menu_curr_item].arg & 0xFFFF)) 
                                    *(curr_menu->menu[gui_menu_curr_item].value) = (short)(curr_menu->menu[gui_menu_curr_item].arg & 0xFFFF);
                            }
                        }
                        if ((curr_menu->menu[gui_menu_curr_item].type & MENUITEM_ARG_MASK) == MENUITEM_ARG_CALLBACK && curr_menu->menu[gui_menu_curr_item].arg) {
                            ((void (*)())(curr_menu->menu[gui_menu_curr_item].arg))();
                        }
                        if (curr_menu->on_change) {
                            curr_menu->on_change(gui_menu_curr_item);
                        }
                        gui_menu_redraw=1;
                        break;
                    case MENUITEM_ENUM:
                        if (curr_menu->menu[gui_menu_curr_item].value) {
                            ((const char* (*)(int change, int arg))(curr_menu->menu[gui_menu_curr_item].value))(-1, curr_menu->menu[gui_menu_curr_item].arg);
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
                        switch (curr_menu->menu[gui_menu_curr_item].type & MENUITEM_ARG_MASK) {
                            case MENUITEM_ARG_INC:
                                *(curr_menu->menu[gui_menu_curr_item].value) += curr_menu->menu[gui_menu_curr_item].arg;
                                break;
                            case MENUITEM_ARG_ADDR_INC:
                                *(curr_menu->menu[gui_menu_curr_item].value) += *(int *)(curr_menu->menu[gui_menu_curr_item].arg);
                                break;
                            default:
                                *(curr_menu->menu[gui_menu_curr_item].value) += 1;
                                break;
                        }
                        if ( curr_menu->menu[gui_menu_curr_item].type & MENUITEM_F_UNSIGNED) {
                            if ( curr_menu->menu[gui_menu_curr_item].type & MENUITEM_F_MAX) {
                                if (*(curr_menu->menu[gui_menu_curr_item].value) > (unsigned short)((curr_menu->menu[gui_menu_curr_item].arg>>16) & 0xFFFF)) 
                                    *(curr_menu->menu[gui_menu_curr_item].value) = (unsigned short)((curr_menu->menu[gui_menu_curr_item].arg>>16) & 0xFFFF);
                            }
                        } else {
                            if ( curr_menu->menu[gui_menu_curr_item].type & MENUITEM_F_MAX) {
                                if (*(curr_menu->menu[gui_menu_curr_item].value) > (short)((curr_menu->menu[gui_menu_curr_item].arg>>16) & 0xFFFF)) 
                                    *(curr_menu->menu[gui_menu_curr_item].value) = (short)((curr_menu->menu[gui_menu_curr_item].arg>>16) & 0xFFFF);
                            }
                        }
                        if ((curr_menu->menu[gui_menu_curr_item].type & MENUITEM_ARG_MASK) == MENUITEM_ARG_CALLBACK && curr_menu->menu[gui_menu_curr_item].arg) {
                            ((void (*)())(curr_menu->menu[gui_menu_curr_item].arg))();
                        }
                        if (curr_menu->on_change) {
                            curr_menu->on_change(gui_menu_curr_item);
                        }
                        gui_menu_redraw=1;
                        break;
                    case MENUITEM_ENUM:
                        if (curr_menu->menu[gui_menu_curr_item].value) {
                            ((const char* (*)(int change, int arg))(curr_menu->menu[gui_menu_curr_item].value))(+1, curr_menu->menu[gui_menu_curr_item].arg);
                        }
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
                        if ((curr_menu->menu[gui_menu_curr_item].type & MENUITEM_ARG_MASK) == MENUITEM_ARG_CALLBACK && curr_menu->menu[gui_menu_curr_item].arg) {
                            ((void (*)())(curr_menu->menu[gui_menu_curr_item].arg))();
                        }
                        if (curr_menu->on_change) {
                            curr_menu->on_change(gui_menu_curr_item);
                        }
                        gui_menu_redraw=1;
                        break;
                    case MENUITEM_PROC:
                    	if (curr_menu->menu[gui_menu_curr_item].value) {
                            ((void (*)(int arg))(curr_menu->menu[gui_menu_curr_item].value))(curr_menu->menu[gui_menu_curr_item].arg);
                            if (curr_menu->on_change) {
                                curr_menu->on_change(gui_menu_curr_item);
                            }
                            gui_menu_set_curr_menu(curr_menu, 0, -1);
                            gui_menu_redraw=2;
                        }
                        break;
                    case MENUITEM_SUBMENU:
                        gui_menu_stack[gui_menu_stack_ptr].menu = curr_menu;
                        gui_menu_stack[gui_menu_stack_ptr].curpos = gui_menu_curr_item;
                        gui_menu_stack[gui_menu_stack_ptr].toppos = gui_menu_top_item;
                        gui_menu_set_curr_menu((CMenu*)(curr_menu->menu[gui_menu_curr_item].value), 0, -1);
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
                            gui_menu_set_curr_menu(gui_menu_stack[gui_menu_stack_ptr].menu, gui_menu_stack[gui_menu_stack_ptr].toppos, gui_menu_stack[gui_menu_stack_ptr].curpos);
                            gui_menu_redraw=2;
                            draw_restore();
                            gui_force_restore();
                        }
                        break;
                    case MENUITEM_COLOR_FG:
                    case MENUITEM_COLOR_BG:
                        draw_restore();
                        item_color=((unsigned char*)(curr_menu->menu[gui_menu_curr_item].value)) + (((curr_menu->menu[gui_menu_curr_item].type & MENUITEM_MASK)==MENUITEM_COLOR_BG)?1:0);
                        gui_palette_init(PALETTE_MODE_SELECT, (*item_color)&0xFF, gui_menu_color_selected);
                        gui_set_mode(GUI_MODE_PALETTE);
                        gui_menu_redraw=2;
                        break;
                    case MENUITEM_ENUM:
                        if (curr_menu->menu[gui_menu_curr_item].value) {
                            ((const char* (*)(int change, int arg))(curr_menu->menu[gui_menu_curr_item].value))(+1, curr_menu->menu[gui_menu_curr_item].arg);
                        }
                        gui_menu_redraw=1;
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
    draw_txt_string(xx-5, y-2, f, conf.menu_color);
    draw_txt_string(xx, y-2, curr_menu->title, conf.menu_color);
    draw_txt_string(xx+l, y-2, f, conf.menu_color);

    for (count=0; curr_menu->menu[count].text; ++count);

    // scrollbar background
    if (count>NUM_LINES) {
        draw_filled_rect((x+w)*FONT_WIDTH, y*FONT_HEIGHT, 
                         (x+w)*FONT_WIDTH+8, (y+NUM_LINES)*FONT_HEIGHT-1, MAKE_COLOR((conf.menu_color>>8)&0xFF, (conf.menu_color>>8)&0xFF));
    }
}

//-------------------------------------------------------------------
void gui_menu_draw() {
    static char tbuf[64];
    int imenu, i, j;
    color cl;
    char cb, ce;
    const char *ch = "";

    if (gui_menu_redraw) {
        if (gui_menu_redraw==2)
            gui_menu_draw_initial();

        for (imenu=gui_menu_top_item, i=0; curr_menu->menu[imenu].text && i<NUM_LINES; ++imenu, ++i){
            cl = (gui_menu_curr_item==imenu)?MAKE_COLOR(COLOR_SELECTED_BG, COLOR_SELECTED_FG):conf.menu_color;
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
            case MENUITEM_SEPARATOR:
                strcpy(tbuf, " 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴� ");
                if (curr_menu->menu[imenu].text[0]) {
                    j = strlen(curr_menu->menu[imenu].text);
                    tbuf[((w-j)>>1)-1]=' ';
                    strcpy(tbuf+((w-j)>>1), curr_menu->menu[imenu].text);
                    tbuf[((w-j)>>1)+j]=' ';
                }
                draw_txt_string(x, y+i, tbuf, conf.menu_color);
                break;
            case MENUITEM_COLOR_FG:
            case MENUITEM_COLOR_BG:
                sprintf(tbuf, "%c%-33s", cb, curr_menu->menu[imenu].text);
                draw_txt_string(x, y+i, tbuf, cl);
                draw_txt_string(x+34, y+i, "\xf9\xfa", (cl&0xFF00)|(((*(curr_menu->menu[imenu].value))>>(((curr_menu->menu[imenu].type & MENUITEM_MASK)==MENUITEM_COLOR_BG)?8:0))&0xFF));
                draw_txt_char(x+36, y+i, ce, cl);
                break;
            case MENUITEM_ENUM:
                if (curr_menu->menu[imenu].value) {
                    ch=((const char* (*)(int change, int arg))(curr_menu->menu[imenu].value))(0, curr_menu->menu[imenu].arg);
                }
                sprintf(tbuf, "%c%-25s [%7s]%c", cb, curr_menu->menu[imenu].text, ch, ce);
                draw_txt_string(x, y+i, tbuf, cl);
                break;
            }
        }
        
        // scrollbar
        if (count>NUM_LINES) {
            i=NUM_LINES*FONT_HEIGHT-1 -1;           // full height
            j=i*NUM_LINES/count;                    // bar height
            i=(i-j)*((gui_menu_curr_item<0)?0:gui_menu_curr_item)/(count-1);   // top pos
            draw_filled_rect((x+w)*FONT_WIDTH+2, y*FONT_HEIGHT+1, 
                             (x+w)*FONT_WIDTH+6, y*FONT_HEIGHT+1+i, MAKE_COLOR(COLOR_BLACK, COLOR_BLACK));
            draw_filled_rect((x+w)*FONT_WIDTH+2, y*FONT_HEIGHT+i+j, 
                             (x+w)*FONT_WIDTH+6, (y+NUM_LINES)*FONT_HEIGHT-1-1, MAKE_COLOR(COLOR_BLACK, COLOR_BLACK));
            draw_filled_rect((x+w)*FONT_WIDTH+2, y*FONT_HEIGHT+1+i, 
                             (x+w)*FONT_WIDTH+6, y*FONT_HEIGHT+i+j, MAKE_COLOR(COLOR_WHITE, COLOR_WHITE));
//        } else {
//            draw_filled_rect((x+w)*FONT_WIDTH+2, y*FONT_HEIGHT+1, 
//                             (x+w)*FONT_WIDTH+6, (y+count)*FONT_HEIGHT-1-1, MAKE_COLOR(COLOR_BLACK, COLOR_BLACK));
        }
        
        gui_menu_redraw=0;
    }
}

