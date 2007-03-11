#include "stdlib.h"
#include "keyboard.h"
#include "platform.h"
#include "core.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_fselect.h"


//-------------------------------------------------------------------
#define NUM_LINES		5
#define NAME_SIZE		16

//-------------------------------------------------------------------
static char current_dir[100];
static enum Gui_Mode 	gui_fselect_mode_old;
struct fitem {
    char 	    *name;
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
    DIR 	   *d;
    struct dirent *de;
    struct stat   st;
    struct fitem  **ptr = &head, *prev = NULL;
    char   buf[100];

    gui_fselect_free_data();

    d = opendir(dir);
    if (d) {
        de = readdir(d);
        while (de) {
            if (de->name[0] != 0xE5 /* deleted entry */) {
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
    top=selected=head;
}

//-------------------------------------------------------------------
void gui_fselect_init(const char* dir) {
    int i;

    strcpy(current_dir, dir);
    gui_fselect_read_dir(current_dir);
    gui_fselect_mode_old = gui_get_mode();
    gui_set_mode(GUI_MODE_FSELECT);
}

//-------------------------------------------------------------------
void gui_fselect_draw() {
    int i=0, t;
    struct fitem  *ptr = head;
    char buf[48];
/*
        if (h<MAX_LINES)
            c[h++][l] = 0;
        if (bw+BUTTON_SEP>w*FONT_WIDTH) 
            w=(bw+BUTTON_SEP)/FONT_WIDTH+1;
    
        x = ((44-w)>>1)*FONT_WIDTH; y = ((12-h)>>1)*FONT_HEIGHT;
        draw_rect(x-3, y-3, x+w*FONT_WIDTH+5, y+(h+2)*FONT_HEIGHT+SPACING_BTN+2+SPACING_TITLE+8, COLOR_BLACK); //shadow
        draw_rect(x-2, y-2, x+w*FONT_WIDTH+6, y+(h+2)*FONT_HEIGHT+SPACING_BTN+2+SPACING_TITLE+9, COLOR_BLACK); //shadow
        draw_rect(x-1, y-1, x+w*FONT_WIDTH+7, y+(h+2)*FONT_HEIGHT+SPACING_BTN+2+SPACING_TITLE+10, COLOR_BLACK); //shadow
        draw_filled_rect(x-4, y-4, x+w*FONT_WIDTH+4, y+(h+2)*FONT_HEIGHT+SPACING_BTN+2+SPACING_TITLE+7, MAKE_COLOR(COLOR_GREY, COLOR_WHITE)); // main box
        draw_filled_rect(x-2, y-2, x+w*FONT_WIDTH+2, y+FONT_HEIGHT+2, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE)); //title
        draw_rect(x-2, y-2, x+w*FONT_WIDTH+2, y+(h+2)*FONT_HEIGHT+SPACING_BTN+2+SPACING_TITLE+5, COLOR_WHITE); //border
        draw_rect(x-3, y-3, x+w*FONT_WIDTH+3, y+(h+2)*FONT_HEIGHT+SPACING_BTN+2+SPACING_TITLE+6, COLOR_WHITE); //border
    while (i<14 && ptr) {
       draw_txt_string(4, i , ptr->name, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));
       sprintf(buf, "[%02X] %7lu %lu ", ptr->attr, ptr->size, ptr->mtime);
       draw_txt_string(20, i , buf, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));
       ptr = ptr->next;
       ++i;
    }
// */
//    t = get_tick_count();
//    while (get_tick_count() - t <10000) ;
    /*
    if (mbox_to_draw) {
        char c[MAX_LINES][MAX_WIDTH+1];
        const char *p=mbox_msg;
        coord x=0, y=0, d;
        unsigned int w, h=0, l=0, bw=(mbox_buttons_num*BUTTON_SIZE*FONT_WIDTH+(mbox_buttons_num-1)*BUTTON_SEP);
        color cl_t =((mode_get()&MODE_MASK) == MODE_PLAY)?MAKE_COLOR(0xAA, COLOR_WHITE):MAKE_COLOR(0xDF, COLOR_WHITE);

        w =strlen(mbox_title);
        if (w > MAX_WIDTH) w = MAX_WIDTH;
        while (*p) {
            if (*p == '\n') {
                c[h++][l] = 0;
                l=0;
                if (h == MAX_LINES) break;
            } else {
                if (l < MAX_WIDTH) {
                    c[h][l++]=*p;
                    if (l > w) w = l;
                }
            }
            ++p;
        }
        if (h<MAX_LINES)
            c[h++][l] = 0;
        if (bw+BUTTON_SEP>w*FONT_WIDTH) 
            w=(bw+BUTTON_SEP)/FONT_WIDTH+1;
    
        x = ((44-w)>>1)*FONT_WIDTH; y = ((12-h)>>1)*FONT_HEIGHT;
        draw_rect(x-3, y-3, x+w*FONT_WIDTH+5, y+(h+2)*FONT_HEIGHT+SPACING_BTN+2+SPACING_TITLE+8, COLOR_BLACK); //shadow
        draw_rect(x-2, y-2, x+w*FONT_WIDTH+6, y+(h+2)*FONT_HEIGHT+SPACING_BTN+2+SPACING_TITLE+9, COLOR_BLACK); //shadow
        draw_rect(x-1, y-1, x+w*FONT_WIDTH+7, y+(h+2)*FONT_HEIGHT+SPACING_BTN+2+SPACING_TITLE+10, COLOR_BLACK); //shadow
        draw_filled_rect(x-4, y-4, x+w*FONT_WIDTH+4, y+(h+2)*FONT_HEIGHT+SPACING_BTN+2+SPACING_TITLE+7, MAKE_COLOR(COLOR_GREY, COLOR_WHITE)); // main box
        draw_filled_rect(x-2, y-2, x+w*FONT_WIDTH+2, y+FONT_HEIGHT+2, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE)); //title
        draw_rect(x-2, y-2, x+w*FONT_WIDTH+2, y+(h+2)*FONT_HEIGHT+SPACING_BTN+2+SPACING_TITLE+5, COLOR_WHITE); //border
        draw_rect(x-3, y-3, x+w*FONT_WIDTH+3, y+(h+2)*FONT_HEIGHT+SPACING_BTN+2+SPACING_TITLE+6, COLOR_WHITE); //border
//        draw_line(x-2, y+FONT_HEIGHT+2, x+w*FONT_WIDTH+2, y+FONT_HEIGHT+2, COLOR_WHITE);
    
        l = strlen(mbox_title);
        draw_string(x+((w-l)>>1)*FONT_WIDTH, y, mbox_title, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE)); //title text
        y+=FONT_HEIGHT+2+SPACING_TITLE;
    
        mbox_buttons_x = x+((w*FONT_WIDTH-bw)>>1);
        mbox_buttons_y = y+h*FONT_HEIGHT+SPACING_BTN;

        while (h) {
            l = strlen(c[--h]);
            switch (mbox_flags & MBOX_TEXT_MASK) {
                case MBOX_TEXT_LEFT:    d = 0; break;
                case MBOX_TEXT_CENTER:  d = ((w-l)>>1)*FONT_WIDTH; break;
                case MBOX_TEXT_RIGHT:   d = (w-l)*FONT_WIDTH; break;
                default:                d = 0; break;
            }
            draw_string(x+d, y+h*FONT_HEIGHT, c[h], MAKE_COLOR(COLOR_GREY, COLOR_WHITE)); // text
        }

        gui_mbox_draw_buttons();

        mbox_to_draw = 0;
    }
    */
}

//-------------------------------------------------------------------
void gui_fselect_kbd_process() {
    switch (kbd_get_clicked_key()) {
    case KEY_UP:
        break;
    case KEY_DOWN:
        break;
    case KEY_SET:
    	gui_fselect_free_data();
        gui_set_mode(gui_fselect_mode_old);
        draw_restore();
        break;
    }
}

//-------------------------------------------------------------------
