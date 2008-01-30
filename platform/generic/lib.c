#include "platform.h"
#include "lolevel.h"
#include "stdlib.h"

void shutdown()
{
    volatile long *p = (void*)0xc02200a0;
        
    asm(
         "MRS     R1, CPSR\n"
         "AND     R0, R1, #0x80\n"
         "ORR     R1, R1, #0x80\n"
         "MSR     CPSR_cf, R1\n"
         :::"r1","r0");
        
    *p = 0x44;

    while(1);
}

int get_flash_params_count(void)
{
 return 111;
}

void debug_led(int state)
{
    volatile long *p=(void*)LED_PR;
    if (state)
	p[0]=0x46;
    else
	p[0]=0x44;
}
#define LED_AF 0xc0220080

void ubasic_set_led(int led, int state, int bright)

{
  int leds[] = {12,16,4,8,4,0,4};
  if(led < 4 || led > 10 || led == 6) return;
  volatile long *p=(void*)LED_AF + leds[led-4];
    if (state)
	p[0]=0x46;
    else
	p[0]=0x44;
}



void led_on(int led)
{
    volatile long *p=(void*)led;
	p[0]=0x46;
}

void led_off(int led)
{
    volatile long *p=(void*)led;
	p[0]=0x44;
}

void debug_blink(int led) {

    volatile long *p=(void*)led;

    p[0]=0x46;
    
    _SleepTask(10);
    
    p[0]=0x44;

    return;
}



static int fd = 0;
static int counter = 0;

void debug_trace(char *a, int b)
{
    // FIX SIZE!!!!!!!!!!!!!!!!!!!
    char logg[512];
    int len;

    if (fd == 0) {
      fd = open("A/LOG.TXT", O_WRONLY|O_CREAT, 0777);
      lseek(fd, 0, SEEK_END);
    }

    len = sprintf(logg, "%04x: %05d: ", counter, time(NULL)%10000);
    len += sprintf(logg+len, a, b);
    logg[len++] = '\n';
    logg[len] = 0;

    write(fd, logg, len);
    counter++;

    if (counter%10 == 0)
    {
      close(fd);
      fd = 0;
    }

}

void logger_task()
{
    while(1) {
       msleep(500);
    }
}
