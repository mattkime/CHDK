#include "stdlib.h"
#include "keyboard.h"
#include "platform.h"
#include "core.h"
#include "conf.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_read.h"


//-------------------------------------------------------------------
static int read_file;
static int read_file_size;
static int read_on_screen;
static int read_to_draw;
static coord x, y, h, w, s;
#define READ_BUFFER_SIZE        (45*15)
static char buffer[READ_BUFFER_SIZE+45];

//-------------------------------------------------------------------
int gui_read_init(const char* file) {
    static struct stat   st;
    read_file = open(file, O_RDONLY, 0777);
    if (strcmp(file, conf.reader_file)!=0) {
        conf.reader_pos = 0;
        strcpy(conf.reader_file, file);
    }
    read_on_screen = 0;
    read_file_size = (read_file>=0 && stat((char*)file, &st)==0)?st.st_size:0;
    if (read_file_size<=conf.reader_pos) {
        conf.reader_pos = 0;
    }
    read_to_draw = 1;
    x=0; 
    y=1;
    w=(screen_width-(x+1)*FONT_WIDTH)/FONT_WIDTH;
    h=(screen_height-y*FONT_HEIGHT)/FONT_HEIGHT;
    s=w*h;
    
    return (read_file >= 0);
}

//-------------------------------------------------------------------
void gui_read_draw() {
    if (read_to_draw) {
        int i, j;
        
        if (read_to_draw) {
            lseek(read_file, conf.reader_pos, SEEK_SET);
            i=read(read_file, buffer, s);
            buffer[i]=0;

            j=0; i=1;
            for (read_on_screen=0; read_on_screen<s && j<h; ++read_on_screen) {
                if (buffer[read_on_screen]) {
                    switch (buffer[read_on_screen]) {
                        case '\r':
                            break;
                        case '\n':
                            for (; i<w-1; ++i) {
                                draw_txt_char(x+i, y+j, ' ', conf.reader_color); //fill the rest
                            }
                            break;
                        case '\t':
                            draw_txt_string(x+i, y+j, "    ", conf.reader_color); //text
                            i+=4;
                            break;
                        default:
                            draw_txt_char(x+i, y+j, buffer[read_on_screen], conf.reader_color); //text
                            ++i;
                            break;

                    }
                    if (i>=w-1) {
                        ++j;
                        i=1;
                    }
                } else {
                    for (; j<h; ++j) {
                        for (; i<w-1; ++i) {
                            draw_txt_char(x+i, y+j, ' ', conf.reader_color); //fill the rest
                        }
                        i=1;
                    }
                }
            }
        
            sprintf(buffer, "(%3d%%) %d/%d%45s", (read_file_size)?(conf.reader_pos*100/read_file_size):0, conf.reader_pos, read_file_size, "");
            buffer[screen_width/FONT_WIDTH]=0;
            draw_txt_string(0, 0, buffer, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE)); //title infoline

            draw_filled_rect(0, y*FONT_HEIGHT, 
                             FONT_WIDTH-1, (y+h)*FONT_HEIGHT, MAKE_COLOR((conf.reader_color>>8)&0xFF, (conf.reader_color>>8)&0xFF));
            // scrollbar
            draw_filled_rect((x+w-1)*FONT_WIDTH, y*FONT_HEIGHT, 
                             (x+w)*FONT_WIDTH+8, (y+h)*FONT_HEIGHT, MAKE_COLOR((conf.reader_color>>8)&0xFF, (conf.reader_color>>8)&0xFF));
            if (read_file_size) {
                i=h*FONT_HEIGHT-1 -1;           // full height
                j=i*s/read_file_size;           // bar height
                if (j<20) j=20;
                i=(i-j)*conf.reader_pos/read_file_size;   // top pos
                draw_filled_rect((x+w)*FONT_WIDTH+2, y*FONT_HEIGHT+1, 
                                 (x+w)*FONT_WIDTH+6, y*FONT_HEIGHT+1+i, MAKE_COLOR(COLOR_BLACK, COLOR_BLACK));
                draw_filled_rect((x+w)*FONT_WIDTH+2, y*FONT_HEIGHT+i+j, 
                                 (x+w)*FONT_WIDTH+6, (y+h)*FONT_HEIGHT-1-1, MAKE_COLOR(COLOR_BLACK, COLOR_BLACK));
                draw_filled_rect((x+w)*FONT_WIDTH+2, y*FONT_HEIGHT+1+i, 
                                 (x+w)*FONT_WIDTH+6, y*FONT_HEIGHT+i+j, MAKE_COLOR(COLOR_WHITE, COLOR_WHITE));
            } else {
                draw_filled_rect((x+w)*FONT_WIDTH+2, y*FONT_HEIGHT+1, 
                                 (x+w)*FONT_WIDTH+6, (y+h)*FONT_HEIGHT-1-1, MAKE_COLOR(COLOR_BLACK, COLOR_BLACK));
            }

            read_to_draw = 0;
        }
    }
}

//-------------------------------------------------------------------
void gui_read_kbd_process() {
    switch (kbd_get_clicked_key()) {
        case KEY_ZOOM_OUT:
        case KEY_UP:
            if (conf.reader_pos>0) {
                conf.reader_pos -= s-w;
                if (conf.reader_pos<0) conf.reader_pos=0;
                read_to_draw = 1;
            }
            break;
        case KEY_ZOOM_IN:
        case KEY_DOWN:
            if ((conf.reader_pos+read_on_screen)<read_file_size) {
                conf.reader_pos += read_on_screen;
                read_to_draw = 1;
            }
            break;
        case KEY_SET:
            break;
        case KEY_MENU:
            if (read_file >= 0) {
                close(read_file);
                read_file=-1;
            }
            break;
    }
}

//-------------------------------------------------------------------
