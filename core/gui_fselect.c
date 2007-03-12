#include "stdlib.h"
#include "keyboard.h"
#include "platform.h"
#include "core.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_fselect.h"


//-------------------------------------------------------------------
#define NUM_LINES               7
#define NAME_SIZE               16

//-------------------------------------------------------------------
static char current_dir[100];
static enum Gui_Mode    gui_fselect_mode_old;
struct fitem {
    char            *name;
    unsigned char   attr;
    unsigned long   size;
    unsigned long   mtime;
    struct fitem    *prev, *next;
};
static struct fitem *head=NULL, *top, *selected;
static unsigned int count=0;
static coord x, y, w, h;


//-------------------------------------------------------------------
static void gui_fselect_free_data() {
    struct fitem  *ptr = head, *prev;

    while (0 && ptr) { // !!! remove 0 !!!
        if (ptr->name)
            free(ptr->name);
        prev=ptr;
        ptr=ptr->next;
        free(prev);
    }
    head=NULL;
    count=0;
}

//-------------------------------------------------------------------
static void gui_fselect_read_dir(const char* dir) {
    DIR            *d;
    struct dirent *de;
    struct stat   st;
    struct fitem  **ptr = &head, *prev = NULL;
    char   buf[100];

    gui_fselect_free_data();

    d = opendir(dir);
    if (d) {
        de = readdir(d);
        while (de) {
            if (de->name[0] != 0xE5 /* deleted entry */ && (de->name[0]!='.' || de->name[1]!=0)) {
                *ptr = malloc(sizeof(struct fitem));
                if (*ptr) {
                    (*ptr)->name = malloc(strlen(de->name)+1);
                    if ((*ptr)->name)
                        strcpy((*ptr)->name, de->name);
                    sprintf(buf, "%s/%s", dir, de->name);
                    if (stat(buf, &st)==0) {
                        (*ptr)->attr=st.st_attrib;
                        (*ptr)->size=st.st_size;
                        (*ptr)->mtime=st.st_mtime;
                    } else {
                        (*ptr)->attr=0xFF;
                        (*ptr)->size=(*ptr)->mtime=0;
                    }
                    (*ptr)->prev=prev;
                    prev=*ptr;
                    ptr = &((*ptr)->next);
                }   
            }
            de = readdir(d);
        }
        closedir(d);
    }
    *ptr=NULL;
}

//-------------------------------------------------------------------
void gui_fselect_init(const char* dir) {
    int i;
    
    w = (1+NAME_SIZE+2+7+2+11+1)*FONT_WIDTH;
    h = NUM_LINES*FONT_HEIGHT+FONT_HEIGHT+4;
    x = (screen_width-w)>>1;
    y = (screen_height-h)>>1;

    strcpy(current_dir, dir);
    gui_fselect_read_dir(current_dir);
    top = selected = head;
    gui_fselect_mode_old = gui_get_mode();
    gui_set_mode(GUI_MODE_FSELECT);
}

//-------------------------------------------------------------------
void gui_fselect_draw() {
    int i, j;
    struct fitem  *ptr;
    char buf[48];

    draw_rect(x-3, y-3, x+w+1, y+h+1, COLOR_BLACK); //shadow
    draw_rect(x-2, y-2, x+w+2, y+h+2, COLOR_BLACK); //shadow
    draw_rect(x-1, y-1, x+w+3, y+h+3, COLOR_BLACK); //shadow
    draw_filled_rect(x-4, y-4, x+w+4, y+h+4, MAKE_COLOR(COLOR_GREY, COLOR_WHITE)); // main box
    draw_filled_rect(x-2, y-2, x+w+2, y+FONT_HEIGHT+2, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE)); //title
    draw_rect(x-2, y-2, x+w+2, y+h+2, COLOR_WHITE); //border
    draw_rect(x-3, y-3, x+w+3, y+h+3, COLOR_WHITE); //border

    for (i=0, ptr=top; i<NUM_LINES && ptr; ++i, ptr=ptr->next) {
        for (j=0; j<NAME_SIZE && ptr->name[j]; ++j) 
            buf[j]=ptr->name[j];
        if (j==NAME_SIZE && ptr->name[j]) buf[NAME_SIZE-1]='>';
        if (ptr->attr & DOS_ATTR_DIRECTORY) {
            if (j<NAME_SIZE) {
                buf[j++]='/';
            } else {
                buf[NAME_SIZE-2]='>';
                buf[NAME_SIZE-1]='/';
            }
        }
        for (; j<NAME_SIZE && (buf[j++]=' '););
        buf[NAME_SIZE]=0;
        draw_string(x+FONT_WIDTH, y+FONT_HEIGHT+4+i*FONT_HEIGHT, buf, MAKE_COLOR((ptr==selected)?COLOR_RED:COLOR_GREY, COLOR_WHITE));
        memset(buf, ' ', sizeof(buf));
        if (ptr->size < 10000000)
            sprintf(buf, "%7lu", ptr->size);
        else if (ptr->size < 1024000000)
            sprintf(buf, "%6luK", ptr->size>>10);
        else
            sprintf(buf, "%6luM", ptr->size>>20);
        buf[7]=0;
        draw_string(x+(1+NAME_SIZE+2)*FONT_WIDTH, y+FONT_HEIGHT+4+i*FONT_HEIGHT, buf, MAKE_COLOR((ptr==selected)?COLOR_RED:COLOR_GREY, COLOR_WHITE));
    }
}

//-------------------------------------------------------------------
void gui_fselect_kbd_process() {\
    int i;
    struct fitem  *ptr;
    
    switch (kbd_get_clicked_key()) {
        case KEY_UP:
            if (selected->prev==top && top->prev) 
                top=top->prev;
            if (selected->prev) 
                selected=selected->prev;
            break;
        case KEY_DOWN:
            for (i=0, ptr=top; i<NUM_LINES-1 && ptr; ++i, ptr=ptr->next);
            if (i==NUM_LINES-1 && ptr&& ptr->next)
                top=top->prev;
            if (selected->next) 
                selected=selected->next;
            break;
        case KEY_SET:
            gui_fselect_free_data();
            gui_set_mode(gui_fselect_mode_old);
            draw_restore();
            break;
    }
}

//-------------------------------------------------------------------
