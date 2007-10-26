#include "stdlib.h"
#include "keyboard.h"
#include "platform.h"
#include "core.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_debug.h"

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

#define MRC(reg, p, c1, c2, op1, op2)  \
    do{  \
    asm volatile   \
    (  \
        "MRC     " #p ", " #op1 ", r0, " #c1 "," #c2 "," #op2 "\n"        \
        "STR     r0, [%0]"  \
        :: "r"(&(reg)) : "r0"  \
    );   \
    }while(0)


#define MCR(reg, p, c1, c2, op1, op2)  \
    do{  \
    int data = (reg); \
    asm volatile   \
    (  \
        "LDR     r0, [%0]\n"  \
        "MCR     " #p ", " #op1 ", r0, " #c1 "," #c2 "," #op2 "\n"        \
        :: "r"(&data) : "r0"  \
    );   \
    }while(0)


int prefetch_count = 0;

void prefetch_abort_action()
{
    prefetch_count++;
}

void __attribute((naked)) prefetch_abort_handler()
{
    asm volatile
    (
        "STMDB	 sp!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, lr}\n"
        "BL      prefetch_abort_action\n"
        "LDMIA	 sp!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, lr}\n"
        "SUBS    PC, R14, #4\n" // Retries the instruction!

//        "LDR     pc, vxworks_prefetch_abort_handler\n"

        // vxWorks original handler stored here
        ".GLOBL  vxworks_prefetch_abort_handler;\n"
        "vxworks_prefetch_abort_handler:;\n"
        "MOV     R0, R0\n"
    
    );
}




void task_spywriter()
{
    int i;

    msleep(1000);

    started();
    
    FILE *fd = fopen("A/rom.dat", "w");
    for(i = 0; i < 0x400000; i += 0x1000){
      fwrite((void*)(0xFF800000+i), 0x1000, 1, fd);
    }
    fclose(fd);

    fd = fopen("A/boot.dat", "w");
    for(i = 0; i < 0x10000; i += 0x1000){
      fwrite((void*)(0xFFFF0000+i), 0x1000, 1, fd);
    }
    fclose(fd);

    finished();

    while(1){
       msleep(100);
    };
}

int data_count = 0;

/**
 * Action to be executed in super mode
 */
int data_abort_action(int sp)
{
    if (data_count == 0) {
      int creg = 0;
//      MRC(creg, p15, c1, c0, 0, 0);
//      MCR(creg & ~1, p15, c1, c0, 0, 0);
      data_count++;
      // abort_retval == 1 - perform user-mode action
      return 1;
    }

    data_count++;

    // abort_retval == 0 - perform no post action
    return 0;

}

/**
 * Action to be executed in user mode
 */
void data_abort_action_usermode(int abort_retval)
{
    // Execute it only if data_abort_action returns TRUE
    if (abort_retval) {
//        CreateTask("SpyWriter", 0x19, 0x4000, task_spywriter, 0);
    }
}

void __attribute((naked)) data_abort_handler()
{
    asm volatile
    (

        "STMDB	 sp!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}\n"
        
        // Store the instruction to reexecute
        "LDR     R0, [R14, #-8]\n"
        "STR     R0, reexecute\n"

        // Trying to reset the cache
        // WARNING: ARM946ES specific!!!
        "MOV     R0, #0\n"
        "MCR     p15, 0, r0, c7, c5, 0\n"

        // execute our supervisor-side action
        "MOV     R0, SP\n"
        "BL      data_abort_action\n"
        "STR     R0, abort_retval\n"

        "LDMIA	 sp!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}\n"

        // save real return address - after the data access instruction
        "SUB     R14, R14, #4\n"
        "STR     R14, retlabel\n"
        "ADD     R14, R14, #4\n"

        // return from abort mode
        "SUBS    PC, PC, #-4\n"
        "MOV     R0, R0\n"
        "MOV     R0, R0\n"
        "MOV     R0, R0\n"
        "MOV     R0, R0\n"

        // execute our user-side action
        "STMDB	 sp!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}\n"
        "LDR     R0, abort_retval\n"
        "BL      data_abort_action_usermode\n"
        "LDMIA	 sp!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}\n"


        // Disable PU
        "STMDB	 sp!, {r0}\n"
        "MRC     p15, 0, r0, c1, c0, 0\n"
        "BIC     r0, #1\n"
        "MCR     p15, 0, r0, c1, c0, 0\n"
        "LDMIA	 sp!, {r0}\n"

        // Instruction to be re-executed, but with disabled Protection Unit!
        ".GLOBL  reexecute;\n"
        "reexecute:;\n"
        "MOV     R0, R0\n"

        // Enable PU back
        "STMDB	 sp!, {r0}\n"
        "MRC     p15, 0, r0, c1, c0, 0\n"
        "ORR     r0, #1\n"
        "MCR     p15, 0, r0, c1, c0, 0\n"
        "LDMIA	 sp!, {r0}\n"


        // jump back to saved return address
        "LDR     PC, retlabel\n"

        ///////////////// Variables //////////////////

        // location to store return addrress
        "retlabel:;\n"
        "MOV     R0, R0\n"

        // stored return value of the abort action handler
        "abort_retval:;\n"
        "MOV     R0, R0\n"

        // vxWorks original handler stored here
        ".GLOBL  vxworks_data_abort_handler;\n"
        "vxworks_data_abort_handler:;\n"
        "MOV     R0, R0\n"

//        "LDR     PC, vxworks_data_abort_handler\n" // Jump to VxWorks handler
//        "SUBS    PC, R14, #8\n"    // Retries the instruction!
//        "SUBS    PC, R14, #4\n"    // Moves to the next instruction!    
    );

}

#define PREFETCH_HANDLER ((int*)0x108)
#define DATA_HANDLER     ((int*)0x10C)

extern int vxworks_prefetch_abort_handler;
extern int vxworks_data_abort_handler;

extern int reexecute;

void debug_dump_arm()
{
    int creg = 0, creg_dis = 0;
    int banks[8] = {0};
    int accperm_data = 0;
    int accperm_code = 0;
    int cpsr = 0;
    int i;


    FILE *fd = fopen("A/arm-info.txt", "w");

    if (!fd) return;

    // Changing abort handlers: 0x0C and 0x10 (prefetch and data aborts)
//    vxworks_prefetch_abort_handler = *PREFETCH_HANDLER;
//    *PREFETCH_HANDLER = (int)prefetch_abort_handler;
    vxworks_data_abort_handler = *DATA_HANDLER;
    *DATA_HANDLER = (int)data_abort_handler;

    
    // Disable Memory Protection Unit
    MRC(creg, p15, c1, c0, 0, 0);
    MCR(creg & ~1, p15, c1, c0, 0, 0);
    
    // Add new memory bank to control //0x700000  0xb
    MCR( (0x2000) + (0xb<<1) + 1, p15, c6, c6, 0, 0);
    MRC(accperm_data, p15, c5, c0, 0, 2);
    MCR((accperm_data & 0x00FFFFFF) + 0x06000000, p15, c5, c0, 0, 2);
    MRC(accperm_data, p15, c5, c0, 0, 3);
    MCR((accperm_data & 0x00FFFFFF) + 0x06000000, p15, c5, c0, 0, 3);

    // ReEnable Memory Protection Unit
    MRC(creg_dis, p15, c1, c0, 0, 0);
    MCR(creg_dis | 1, p15, c1, c0, 0, 0);
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

    fprintf(fd, "Control register dis: %x\n", creg_dis);
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

    fprintf(fd, "Abort Prefetch handler: %x\n", *(int*)prefetch_abort_handler);
    fprintf(fd, "Abort Data handler: %x\n", *(int*)data_abort_handler);
    
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

    if ( *((int*)0x700000) == 0x100 ) data_count += 0x100;
    if ( *((int*)0x700100) == 0x200 ) data_count += 0x100;
    if ( *((int*)0x700200) == 0x300 ) data_count += 0x100;

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
