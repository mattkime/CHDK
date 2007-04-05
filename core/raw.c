#include "platform.h"
#include "conf.h"
#include "stdlib.h"
#include "raw.h"

//-------------------------------------------------------------------
#define RAW_TARGET_DIRECTORY    "A/DCIM/100CANON"
#define RAW_TMP_FILENAME        "HDK_RAW.TMP"
#define RAW_TARGET_FILENAME     "CRW_%04d.CRW"

//-------------------------------------------------------------------
static char fn[64];
//int xxxx, eeee;

//-------------------------------------------------------------------
int raw_savefile() {
    int fd;

    // got here second time in a row. Skip second RAW saving.
    if (state_shooting_progress == SHOOTING_PROGRESS_PROCESSING){
        return 0;
    }

    state_shooting_progress = SHOOTING_PROGRESS_PROCESSING;

    if (conf.save_raw) {
        started();

        mkdir(RAW_TARGET_DIRECTORY);

        sprintf(fn, "%s/%s", RAW_TARGET_DIRECTORY, RAW_TMP_FILENAME);
        fd = fopen(fn, "w+");
        if (fd >= 0) {
            fwrite(hook_raw_image_addr(), hook_raw_size(), 1, fd);
            fclose(fd);
        }

        finished();

        return (fd >= 0);
    }

    return 0;
}

//-------------------------------------------------------------------
void raw_postprocess() {
//    int fd;
    long v=get_file_counter();
    static struct utimbuf t;

    started();

//    sprintf(fn, RAW_TARGET_FILENAME, (v>>18)&0x3FF, (v>>4)&0x3FFF);
    sprintf(fn, RAW_TARGET_FILENAME, (v>>4)&0x3FFF);
    chdir(RAW_TARGET_DIRECTORY);
    rename(RAW_TMP_FILENAME, fn);

    t.actime = t.modtime = time(NULL);
    utime(fn, &t);

//        chdir("A/DCIM");
//    fd = open( "A/1", O_RDONLY, 0 );
//    eeee = fd;
//    xxxx = ((int (*)(int fd, int function, int arg))(0xFFEBBF9C))(fd, 47, (int)"A/DCIM/1"); //move
//    close(fd);
//    xxxx=rename("1", "DCIM/1");
//    eeee=*((int*)0xA021C); //errno

    finished();
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------
