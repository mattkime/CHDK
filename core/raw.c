#include "platform.h"
#include "conf.h"
#include "stdlib.h"
#include "raw.h"

//-------------------------------------------------------------------
#define RAW_TARGET_DIRECTORY    "A/DCIM/%03dCANON"
//#define RAW_TMP_FILENAME        "HDK_RAW.TMP"
#define RAW_TARGET_FILENAME     "%s_%04d.%s"

//-------------------------------------------------------------------
static char fn[64];
static char dir[32];
static char prefixes[][4] = { "IMG", "CRW", "SND" };
static char exts[][4] = { "JPG", "CRW", "CR2", "THM", "WAV" };
//int xxxx, eeee;

//-------------------------------------------------------------------
int raw_savefile() {
    int fd;
    static struct utimbuf t;

    // got here second time in a row. Skip second RAW saving.
    if (state_shooting_progress == SHOOTING_PROGRESS_PROCESSING){
        return 0;
    }

    state_shooting_progress = SHOOTING_PROGRESS_PROCESSING;

    if (conf.save_raw) {
        long v;
        started();

        t.actime = t.modtime = time(NULL);
        v=get_file_next_counter();

        sprintf(dir, RAW_TARGET_DIRECTORY, (conf.raw_in_dir)?((v>>18)&0x3FF):100);
        mkdir(dir);

        sprintf(fn, "%s/", dir);
        sprintf(fn+strlen(fn), RAW_TARGET_FILENAME, prefixes[conf.raw_prefix], (v>>4)&0x3FFF, exts[conf.raw_ext]);

        fd = fopen(fn, "wb");
        if (fd) {
            fwrite(hook_raw_image_addr(), hook_raw_size(), 1, fd);
            fclose(fd);
            utime(fn, &t);
        }

        finished();

        return (fd != 0);
    }

    return 0;
}

//-------------------------------------------------------------------
void raw_postprocess() {
/*
//    int fd;
    long v=get_file_counter();
    static struct utimbuf t;

    started();

//    sprintf(fn, RAW_TARGET_FILENAME, (v>>18)&0x3FF, (v>>4)&0x3FFF);
    sprintf(fn, RAW_TARGET_FILENAME, prefixes[conf.raw_prefix], (v>>4)&0x3FFF, exts[conf.raw_ext]);
    chdir(dir);
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
 */
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------
