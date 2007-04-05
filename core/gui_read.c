#include "stdlib.h"
#include "keyboard.h"
#include "platform.h"
#include "core.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_read.h"


//-------------------------------------------------------------------
static int read_file;
static int read_offset, read_file_size;
static int read_to_draw;
static coord x, y, h, w;
#define READ_BUFFER_SIZE        (45*15)
static char buffer[READ_BUFFER_SIZE+45];

//-------------------------------------------------------------------
int gui_read_init(const char* file) {
    read_file = open(file, O_RDONLY, 0777);
    read_offset = 0;
    read_file_size = (read_file >= 0)?lseek(read_file, 0, SEEK_END):0;
    read_to_draw = 1;
    x=0; 
    y=1;
    w=(screen_width-(x+1)*FONT_WIDTH)/FONT_WIDTH;
    h=(screen_height-y*FONT_HEIGHT)/FONT_HEIGHT;
    
    return (read_file >= 0);
}

//-------------------------------------------------------------------
void gui_read_draw() {
    if (read_to_draw) {
        int r;
        int i, j;
        register int f=1;
        
        lseek(read_file, read_offset, SEEK_SET);
        r=read(read_file, buffer, READ_BUFFER_SIZE);
        buffer[r]=0;
        
        for (j=0; j<h; ++j) {
            for (i=0; i<w; ++i) {
                draw_txt_char(x+i, y+j, (f)?buffer[j*w+i]:' ', MAKE_COLOR(COLOR_GREY, COLOR_WHITE)); //text
                if (f && !buffer[j*w+i]) f=0;
            }
        }
    
        sprintf(buffer, "%d%45s", read_offset, "");
        buffer[screen_width/FONT_WIDTH]=0;
        draw_txt_string(0, 0, buffer, MAKE_COLOR(COLOR_BG, COLOR_WHITE)); //title infoline

        read_to_draw = 0;
    }
}

//-------------------------------------------------------------------
void gui_read_kbd_process() {
    switch (kbd_get_clicked_key()) {
        case KEY_UP:
            read_offset-=READ_BUFFER_SIZE;
            if (read_offset<0) read_offset=0;
            break;
        case KEY_DOWN:
            if ((read_offset+READ_BUFFER_SIZE)<read_file_size) 
                read_offset+=READ_BUFFER_SIZE;
            break;
        case KEY_SET:
            break;
        case KEY_MENU:
            if (read_file >= 0) {
                close(read_file);
            }
            break;
    }
}

//-------------------------------------------------------------------
