#include "stdlib.h"
#include "keyboard.h"
#include "platform.h"
#include "core.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_mbox.h"
#include "gui_fselect.h"


//-------------------------------------------------------------------
#define NUM_LINES               7
#define NAME_SIZE               15
#define SIZE_SIZE               7
#define TIME_SIZE               14
#define SPACING                 1


//-------------------------------------------------------------------
static char current_dir[100], selected_file[100];
static enum Gui_Mode    gui_fselect_mode_old;
struct fitem {
    unsigned int    n;
    char            *name;
    unsigned char   attr;
    unsigned long   size;
    unsigned long   mtime;
    struct fitem    *prev, *next;
};
static struct fitem *head=NULL, *top, *selected;
static unsigned int count;
static coord x, y, w, h;
static int gui_fselect_redraw;
static const char *fselect_title = "Select file";
static void (*fselect_on_select)(const char *fn);

//-------------------------------------------------------------------
static void gui_fselect_free_data() {
    struct fitem  *ptr = head, *prev;

    while (ptr) {
        if (ptr->name)
            free(ptr->name);
        prev=ptr;
        ptr=ptr->next;
        free(prev);
    }
    head=top=selected=NULL;
    count=0;
}

//-------------------------------------------------------------------
extern int fselect_sort_nothumb(const void* v1, const void* v2);
int fselect_sort(const void* v1, const void* v2) {
    struct fitem *i1=*((struct fitem **)v1), *i2=*((struct fitem **)v2);

    if (i1->attr & DOS_ATTR_DIRECTORY) {
        if (i2->attr & DOS_ATTR_DIRECTORY) {
            if (i1->name[0]=='.' && i1->name[1]=='.' && i1->name[2]==0) {
                return -1;
            } else if (i2->name[0]=='.' && i2->name[1]=='.' && i2->name[2]==0) {
                return 1;
            } else {
                return strcmp(i1->name, i2->name);
            }
        } else {
            return -1;
        }
    } else {
        if (i2->attr & DOS_ATTR_DIRECTORY) {
            return 1;
        } else {
            return strcmp(i1->name, i2->name);
        }
    }
}

//-------------------------------------------------------------------
static void gui_fselect_read_dir(const char* dir) {
    DIR           *d;
    struct dirent *de;
    static struct stat   st;
    struct fitem  **ptr = &head, *prev = NULL;
    static char   buf[100];
    int    i;

    gui_fselect_free_data();

    d = opendir(dir);
    if (d) {
        de = readdir(d);
        while (de) {
            if (de->name[0] != 0xE5 /* deleted entry */ && (de->name[0]!='.' || de->name[1]!=0)) {
                *ptr = malloc(sizeof(struct fitem));
                if (*ptr) {
                    (*ptr)->n = count;
                    (*ptr)->name = malloc(strlen(de->name)+1);
                    if ((*ptr)->name)
                        strcpy((*ptr)->name, de->name);
                    sprintf(buf, "%s/%s", dir, de->name);
                    if (stat(buf, &st)==0) {
                        (*ptr)->attr=st.st_attrib;
                        (*ptr)->size=st.st_size;
                        (*ptr)->mtime=st.st_mtime;
                    } else {
                        (*ptr)->attr=(de->name[0]=='.' && de->name[1]=='.' && de->name[2]==0)?DOS_ATTR_DIRECTORY:0xFF;
                        (*ptr)->size=(*ptr)->mtime=0;
                    }
                    (*ptr)->prev=prev;
                    prev=*ptr;
                    ptr = &((*ptr)->next);
                    ++count;
                }   
            }
            de = readdir(d);
        }
        closedir(d);
    }
    *ptr=NULL;
    
    if (count) {
        // sort
        ptr=malloc(count*sizeof(struct fitem*));
        if (ptr) {
            prev=head;
            count=0;
            while (prev) {
                ptr[count++]=prev;
                prev=prev->next;
            }
            
            qsort(ptr, count, sizeof(struct fitem*), fselect_sort_nothumb);
            
            for (i=0; i<count-1; ++i) {
                ptr[i]->n=i;
                ptr[i]->next=ptr[i+1];
                ptr[i+1]->prev=ptr[i];
            }
            ptr[0]->prev=ptr[count-1]->next=NULL;
            ptr[count-1]->n=count-1;
            head=ptr[0];

            free(ptr);
        }
    }

    top = selected = head;
}

//-------------------------------------------------------------------
void gui_fselect_init(const char* dir, void (*on_select)(const char *fn)) {
    int i;
    
    w = (1+NAME_SIZE+SPACING+SIZE_SIZE+SPACING+TIME_SIZE+1+1)*FONT_WIDTH;
    h = FONT_HEIGHT+4+NUM_LINES*FONT_HEIGHT+4+FONT_HEIGHT;
    x = (screen_width-w)>>1;
    y = (screen_height-h)>>1;

    strcpy(current_dir, dir);
    gui_fselect_read_dir(current_dir);
    top = selected = head;
    selected_file[0]=0;
    fselect_on_select = on_select;
    gui_fselect_mode_old = gui_get_mode();
    gui_fselect_redraw = 2;
    gui_set_mode(GUI_MODE_FSELECT);

}

//-------------------------------------------------------------------
char* gui_fselect_result() {
    if (selected_file[0])
        return selected_file;
    else
        return NULL;
}

//-------------------------------------------------------------------
void gui_fselect_draw_initilal() {
    int i;

    draw_rect(x-3, y-3, x+w+5, y+h+5, COLOR_BLACK); //shadow
    draw_rect(x-2, y-2, x+w+6, y+h+6, COLOR_BLACK); //shadow
    draw_rect(x-1, y-1, x+w+7, y+h+7, COLOR_BLACK); //shadow
    draw_filled_rect(x-4, y-4, x+w+4, y+h+4, MAKE_COLOR(COLOR_GREY, COLOR_WHITE)); // main box
    draw_filled_rect(x-2, y-2, x+w+2, y+FONT_HEIGHT+2, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE)); //title
    draw_filled_rect(x-2, y+h-FONT_HEIGHT-2, x+w+2, y+h+2, MAKE_COLOR(COLOR_GREY, COLOR_WHITE)); //footer
    draw_rect(x-2, y-2, x+w+2, y+h+2, COLOR_WHITE); //border
    draw_rect(x-3, y-3, x+w+3, y+h+3, COLOR_WHITE); //border
    i = strlen(fselect_title);
    draw_string(x+((w-i*FONT_WIDTH)>>1), y, fselect_title, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE)); //title text
}

//-------------------------------------------------------------------
void gui_fselect_draw() {
    int i, j;
    struct fitem  *ptr;
    char buf[48];
    struct tm *time;

    if (gui_fselect_redraw) {
        if (gui_fselect_redraw==2)
            gui_fselect_draw_initilal();

        for (i=0, ptr=top; i<NUM_LINES && ptr; ++i, ptr=ptr->next) {
            // print name
            for (j=0; j<NAME_SIZE && ptr->name[j]; ++j) 
                buf[j]=ptr->name[j];
            if (j==NAME_SIZE && ptr->name[j]) buf[NAME_SIZE-1]='>';
            if (ptr->attr & DOS_ATTR_DIRECTORY && ptr->attr != 0xFF) {
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

            draw_string(x+(1+NAME_SIZE)*FONT_WIDTH, y+FONT_HEIGHT+4+i*FONT_HEIGHT, "³", MAKE_COLOR((ptr==selected)?COLOR_RED:COLOR_GREY, COLOR_WHITE));

            // print size or <Dir>
            if (ptr->attr & DOS_ATTR_DIRECTORY) {
                if (ptr->attr == 0xFF) {
                    sprintf(buf, "  ???  ");
                } else if (ptr->name[0]=='.' && ptr->name[1]=='.' && ptr->name[2]==0) {
                    sprintf(buf, "<UpDir>");
                } else {
                    sprintf(buf, "< Dir >");
                }
            } else {
                if (ptr->size < 10000000)
                    sprintf(buf, "%7lu", ptr->size);
                else if (ptr->size < 1024000000)
                    sprintf(buf, "%6luK", ptr->size>>10);
                else
                    sprintf(buf, "%6luM", ptr->size>>20);
            }
            draw_string(x+(1+NAME_SIZE+SPACING)*FONT_WIDTH, y+FONT_HEIGHT+4+i*FONT_HEIGHT, buf, MAKE_COLOR((ptr==selected)?COLOR_RED:COLOR_GREY, COLOR_WHITE));

            draw_string(x+(1+NAME_SIZE+SPACING+SIZE_SIZE)*FONT_WIDTH, y+FONT_HEIGHT+4+i*FONT_HEIGHT, "³", MAKE_COLOR((ptr==selected)?COLOR_RED:COLOR_GREY, COLOR_WHITE));

            // print modification time
            if (ptr->mtime) {
                time = localtime(&(ptr->mtime));
                sprintf(buf, "%2u/%02u/%02u %02u:%02u", time->tm_mday, time->tm_mon+1, (time->tm_year<100)?time->tm_year:time->tm_year-100, time->tm_hour, time->tm_min);
            } else {
                sprintf(buf, "%14s", "");
            }
            draw_string(x+(1+NAME_SIZE+SPACING+SIZE_SIZE+SPACING)*FONT_WIDTH, y+FONT_HEIGHT+4+i*FONT_HEIGHT, buf, MAKE_COLOR((ptr==selected)?COLOR_RED:COLOR_GREY, COLOR_WHITE));
        }

        if (i<NUM_LINES) {
            draw_filled_rect(x+FONT_WIDTH, y+FONT_HEIGHT+4+i*FONT_HEIGHT, x+(1+NAME_SIZE+SPACING+SIZE_SIZE+SPACING+TIME_SIZE)*FONT_WIDTH, 
                             y+FONT_HEIGHT+4+NUM_LINES*FONT_HEIGHT-1, MAKE_COLOR(COLOR_GREY, COLOR_GREY));
        }

        i=strlen(current_dir);
        if (i>NAME_SIZE+SPACING+SIZE_SIZE+SPACING+TIME_SIZE) {
            i-=NAME_SIZE+SPACING+SIZE_SIZE+SPACING+TIME_SIZE -1;
            draw_char(x+FONT_WIDTH, y+FONT_HEIGHT+4+NUM_LINES*FONT_HEIGHT+4, '<', MAKE_COLOR(COLOR_GREY, COLOR_WHITE));
            draw_string(x+FONT_WIDTH*2, y+FONT_HEIGHT+4+NUM_LINES*FONT_HEIGHT+4, current_dir+i, MAKE_COLOR(COLOR_GREY, COLOR_WHITE)); //current dir
        } else {
            draw_string(x+FONT_WIDTH, y+FONT_HEIGHT+4+NUM_LINES*FONT_HEIGHT+4, current_dir, MAKE_COLOR(COLOR_GREY, COLOR_WHITE)); //current dir
            draw_filled_rect(x+(1+i)*FONT_WIDTH, y+FONT_HEIGHT+4+NUM_LINES*FONT_HEIGHT+4, 
                             x+(1+NAME_SIZE+SPACING+SIZE_SIZE+SPACING+TIME_SIZE)*FONT_WIDTH, y+FONT_HEIGHT+4+NUM_LINES*FONT_HEIGHT+4+FONT_HEIGHT, MAKE_COLOR(COLOR_GREY, COLOR_GREY)); // fill
        }

        // scrollbar
        if (count>NUM_LINES) {
            i=NUM_LINES*FONT_HEIGHT-1 -1;
            j=i*NUM_LINES/count;
            if (j<20) j=20;
            i=(i-j)*selected->n/(count-1);
            draw_filled_rect(x+(1+NAME_SIZE+SPACING+SIZE_SIZE+SPACING+TIME_SIZE+1)*FONT_WIDTH+2, y+FONT_HEIGHT+4+1, 
                             x+(1+NAME_SIZE+SPACING+SIZE_SIZE+SPACING+TIME_SIZE+1)*FONT_WIDTH+6, y+FONT_HEIGHT+4+1+i, MAKE_COLOR(COLOR_BLACK, COLOR_BLACK));
            draw_filled_rect(x+(1+NAME_SIZE+SPACING+SIZE_SIZE+SPACING+TIME_SIZE+1)*FONT_WIDTH+2, y+FONT_HEIGHT+4+i+j, 
                             x+(1+NAME_SIZE+SPACING+SIZE_SIZE+SPACING+TIME_SIZE+1)*FONT_WIDTH+6, y+FONT_HEIGHT+4+NUM_LINES*FONT_HEIGHT-1-1, MAKE_COLOR(COLOR_BLACK, COLOR_BLACK));
            draw_filled_rect(x+(1+NAME_SIZE+SPACING+SIZE_SIZE+SPACING+TIME_SIZE+1)*FONT_WIDTH+2, y+FONT_HEIGHT+4+1+i, 
                             x+(1+NAME_SIZE+SPACING+SIZE_SIZE+SPACING+TIME_SIZE+1)*FONT_WIDTH+6, y+FONT_HEIGHT+4+i+j, MAKE_COLOR(COLOR_WHITE, COLOR_WHITE));
        } else {
            draw_filled_rect(x+(1+NAME_SIZE+SPACING+SIZE_SIZE+SPACING+TIME_SIZE+1)*FONT_WIDTH+2, y+FONT_HEIGHT+4+1, 
                             x+(1+NAME_SIZE+SPACING+SIZE_SIZE+SPACING+TIME_SIZE+1)*FONT_WIDTH+6, y+FONT_HEIGHT+4+NUM_LINES*FONT_HEIGHT-1-1, MAKE_COLOR(COLOR_BLACK, COLOR_BLACK));
        }

        gui_fselect_redraw = 0;
    }
}

//-------------------------------------------------------------------
static void fselect_delete_cb(unsigned int btn) {
    if (btn==MBOX_BTN_YES) {
        sprintf(selected_file, "%s/%s", current_dir, selected->name);
        remove(selected_file);
        selected_file[0]=0;
        gui_fselect_read_dir(current_dir);
    }
    gui_fselect_redraw = 1;
}

//-------------------------------------------------------------------
static void fselect_goto_prev(int step) {
    register int j;

    for (j=0; j<step; ++j) {
        if (selected->prev==top && top->prev) 
            top=top->prev;
        if (selected->prev) 
            selected=selected->prev;
    }
}

//-------------------------------------------------------------------
static void fselect_goto_next(int step) {
    register int j, i;
    struct fitem  *ptr;

    for (j=0; j<step; ++j) {
        for (i=0, ptr=top; i<NUM_LINES-1 && ptr; ++i, ptr=ptr->next);
        if (i==NUM_LINES-1 && ptr && ptr->prev==selected && ptr->next)
            top=top->next;
        if (selected->next) 
            selected=selected->next;
    }
}

//-------------------------------------------------------------------
void gui_fselect_kbd_process() {
    int i;
    
    switch (kbd_get_clicked_key()) {
        case KEY_UP:
            if (selected) {
                fselect_goto_prev(1);
                gui_fselect_redraw = 1;
            }
            break;
        case KEY_DOWN:
            if (selected) {
                fselect_goto_next(1);
                gui_fselect_redraw = 1;
            }
            break;
        case KEY_ZOOM_OUT:
            if (selected) {
                fselect_goto_prev(NUM_LINES-1);
                gui_fselect_redraw = 1;
            }
            break;
        case KEY_ZOOM_IN:
            if (selected) {
                fselect_goto_next(NUM_LINES-1);
                gui_fselect_redraw = 1;
            }
            break;
        case KEY_SET:
            if (selected && selected->attr != 0xFF) {
                if (selected->attr & DOS_ATTR_DIRECTORY) {
                    i=strlen(current_dir);
                    if (selected->name[0]=='.' && selected->name[1]=='.' && selected->name[2]==0) {
                        while (current_dir[--i] != '/');
                        current_dir[i]=0;
                    } else {
                        sprintf(current_dir+i, "/%s", selected->name);
                    }
                    gui_fselect_read_dir(current_dir);
                    gui_fselect_redraw = 1;
                } else  {
                    sprintf(selected_file, "%s/%s", current_dir, selected->name);
                    gui_fselect_free_data();
                    gui_set_mode(gui_fselect_mode_old);
                    draw_restore();
                    if (fselect_on_select) 
                        fselect_on_select(selected_file);
                }
            }
            break;
        case KEY_ERASE:
            if (selected && selected->attr != 0xFF && !(selected->attr & DOS_ATTR_DIRECTORY)) {
                gui_mbox_init("*** Delete file ***", "Are you SURE to delete\nselected file?",
                               MBOX_TEXT_CENTER|MBOX_BTN_YES_NO|MBOX_DEF_BTN2, fselect_delete_cb);
            }
            break;
        case KEY_MENU:
            gui_fselect_free_data();
            gui_set_mode(gui_fselect_mode_old);
            draw_restore();
            if (fselect_on_select) 
                fselect_on_select(NULL);
            break;
    }
}

//-------------------------------------------------------------------
