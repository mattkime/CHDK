#include "stdlib.h"
#include "keyboard.h"
#include "platform.h"
#include "core.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_debug.h"
#include <coproc.h>

//-------------------------------------------------------------------
static void *addr;
static char debug_to_draw;
static char buf[32];
static long dummy=0;
static unsigned int step;

//-------------------------------------------------------------------
#define SCREEN_COLOR            0xF7

//-------------------------------------------------------------------
void gui_debug_init(void *st_addr) {
    addr = st_addr;
    debug_to_draw = 1;
    step = 4;
    gui_set_mode(GUI_MODE_DEBUG);
}

//#include "../lib/fceu/src/driver.h"

void debug_dump_information() {
    int fd;
    int len, cnt = 0;
    static char buf[64];
    const char *name = NULL;
    int idList[100];

//    FCEUI_LoadGame("path");

    started();

    fd = open("A/tasks-dump.txt", O_WRONLY|O_CREAT, 0777);

    if (!fd) return;
        
    int tnum = taskIdListGet(idList, 100);
    
    while(tnum){
        
        name = taskName(idList[tnum]);

        len = sprintf(buf, "task %x: %s\n", idList[tnum], name);
        write(fd, buf, len);
        tnum--;

    }
    
    close(fd);

    finished();
}


void debug_dump_arm()
{
    int creg, creg_dis = 0;
    int banks[8] = {0};
    int accperm_data = 0;
    int accperm_code = 0;
    int cpsr = 0;
    int i;


    FILE *fd = fopen("A/arm-info.txt", "w");

    if (!fd) return;

    // Reread it
    MRC(creg, p15, c1, c0, 0, 0);

    MRC(banks[0], p15, c6, c0, 0, 0);
    MRC(banks[1], p15, c6, c1, 0, 0);
    MRC(banks[2], p15, c6, c2, 0, 0);
    MRC(banks[3], p15, c6, c3, 0, 0);
    MRC(banks[4], p15, c6, c4, 0, 0);
    MRC(banks[5], p15, c6, c5, 0, 0);
    MRC(banks[6], p15, c6, c6, 0, 0);
    MRC(banks[7], p15, c6, c7, 0, 0);

    MRC(accperm_data, p15, c5, c0, 0, 2);
    MRC(accperm_code, p15, c5, c0, 0, 3);

    fprintf(fd, "Control register: %x\n", creg);

    asm volatile
    (
        "MRS     r0, CPSR\n"
        "STR     r0, [%0]\n"
        :: "r"(&cpsr) : "r0"
    );
    fprintf(fd, "CPSR: %x\n", cpsr);


    fprintf(fd, "Bank registers: \n");

    for (i = 0; i < 8; i++) {
       int size = (banks[i]>>1) & 0x1F;
       fprintf(fd, " bank%d: base=0x% 8x size=%d kb, enabled(%d) accode(%x) acdata(%x)\n", i,
                banks[i]&~4095, 4 * (1 << size - 0xB ), banks[i]&1,  (accperm_code>>i*4)&7, (accperm_data>>i*4)&7 );
    }

    fprintf(fd, "Interrupt vectors: \n");

    for (i = 0; i < 8; i++) {
       fprintf(fd, " vec(%x) = %x\n", i*4,  *(int*)(i*4) );
    }

    fclose(fd);

    msleep(500);

    // trigger it
    *((int*)0x700000) = 0x100;

    *((int*)0x700100) = 0x200;

    *((int*)0x700200) = 0x300;

    msleep(1000);

    //if ( *((int*)0x700000) == 0x100 ) data_count += 0x100;
    //if ( *((int*)0x700100) == 0x200 ) data_count += 0x100;
    //if ( *((int*)0x700200) == 0x300 ) data_count += 0x100;

    // data_count should be 0x303 here!!!

}

void dump_memory()
{
    int fd;
    static int cnt=0;
    static char fn[32];
    int i;

    int * addr = (int*)hook_raw_image_addr();

    started();

/*
    for(i = 0; i < 1000000; i++){
        *addr = 0xFFFFFFFF;
        addr++;
    }
*/
    
	sprintf(fn, "A/32mem-%d.dump", cnt++);
	fd = open(fn, O_WRONLY|O_CREAT, 0777);
	if (fd) {
//            fwrite((void*)vid_get_viewport_fb(), 360*240*3, 1, fd);
//            fwrite((void*)vid_get_bitmap_fb(), 360*240, 1, fd);

	    // Zero is not readable!
	    write(fd, (int*)0xFFFF0000, 4);
            
	    write(fd, (int*)4, 0x1900-4);

	    // write(fd, (void*)0x1900, 0x9C6B0); // all RAM+BSS

	    write(fd, (void*)0x1900, 32*1024*1024 - 0x1900);

	    close(fd);
	}
    vid_bitmap_refresh();
    finished();
    msleep(1000);
}

#define CONS_W (45)
#define CONS_H (128)
extern char console_buf[CONS_H][CONS_W];
extern long console_buf_line;
long cons_topline = 0;

extern int cons_cmd_ptr;
static char osd_buf[64];

void gui_debug_draw_console() {
  long i;
  for (i=0;i<15;i++){
      long l = cons_topline+i;
      if (l>CONS_H) l-=CONS_H;
      sprintf(osd_buf, "%02d:%-45s", i, console_buf[l]);
      draw_txt_string(1, 1+i, osd_buf, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));
  }
}

//-------------------------------------------------------------------
static void gui_debug_draw_values(const coord y, void* addr) {
    int i;

    if (!(addr<(void*)0x2000000 || addr>(void*)0xFFC00000)) { addr = &dummy; };

    sprintf(buf, "0x%08X (%10u)", *((unsigned int*)addr), *((unsigned int*)addr));
    draw_txt_string(10, y, buf, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));

    sprintf(buf, "0x%04X (%5hu)", *((unsigned short*)addr), *((unsigned short*)addr));
    draw_txt_string(10, y+1, buf, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));

    sprintf(buf, "0x%02X (%3hu)", *((unsigned char*)addr), *((unsigned char*)addr));
    draw_txt_string(10, y+2, buf, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));

//    sprintf(buf, "0x%lf", *((double*)addr));
//    draw_txt_string(10, y+3, buf, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));

    for (i=0; i<30; ++i) {
        if (*((char*)(addr+i))) buf[i]=*((char*)(addr+i));
        else break;
    }
    while (i<30) {
        buf[i++]=' ';
    }
    buf[i]=0;
    draw_txt_string(10, y+4, buf, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));
}

//-------------------------------------------------------------------
void gui_debug_draw() {
    switch (debug_to_draw) {
        case 1:
            draw_filled_rect(0, 0, screen_width-1, screen_height-1, MAKE_COLOR(SCREEN_COLOR, SCREEN_COLOR));
            draw_txt_string(1, 0, "Address:", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(25, 0, "Incr:", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(1, 1, "Values:",  MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(2, 2, "DWORD  :", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(2, 3, "WORD   :", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(2, 4, "BYTE   :", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(2, 5, "DOUBLE :", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(2, 6, "STRING :", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(1, 7, "Dereferencing:",  MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(2, 8, "DWORD  :", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(2, 9, "WORD   :", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(2, 10, "BYTE   :", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(2, 11, "DOUBLE :", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(2, 12, "STRING :", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));

            debug_to_draw = 2;
            break;
        case 2:
            sprintf(buf, "0x%08X", addr);
            draw_txt_string(10, 0, buf, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));
            sprintf(buf, "0x%08X", step);
            draw_txt_string(31, 0, buf, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));
            gui_debug_draw_values(2, addr);
            gui_debug_draw_values(8, *((void**)addr));

            debug_to_draw = 0;
            break;
        default:
            debug_to_draw = 0;
            break;
    }
}

//-------------------------------------------------------------------
void gui_debug_kbd_process() {
    switch (kbd_get_autoclicked_key()) {
    case KEY_DOWN:
        switch (step) {
            case 0x00000010: step = 0x00000004; break;
            case 0x00000004: step = 0x10000000; break;
            default: step>>=4; break;
        }
        debug_to_draw = 2;
        break;
    case KEY_UP:
        switch (step) {
            case 0x00000004: step = 0x00000010; break;
            case 0x10000000: step = 0x00000004; break;
            default: step<<=4; break;
        }
        debug_to_draw = 2;
        break;
    case KEY_LEFT:
        addr-=step;
        debug_to_draw = 2;
        break;
    case KEY_RIGHT:
        addr+=step;
        debug_to_draw = 2;
        break;
    default:
        if (debug_to_draw == 0) {
            debug_to_draw = 2;
        }
        break;
    }
}

//-------------------------------------------------------------------
