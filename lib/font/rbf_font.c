#include "stdlib.h"
#include "gui.h"

//-------------------------------------------------------------------
#define RBF_HDR_SIZE       0x74
#define RBF_MAX_NAME       64

//-------------------------------------------------------------------
const char *RBF_HDR_MAGIC = "\xE0\x0E\xF0\x0D\x03\x00\x00\x00";

static struct {
     char name[RBF_MAX_NAME];
     int width, height;
     int points;
     int intline;
     int charFirst, charCount;
     char wTable[256];
     char *cTable[256];
     int maxWidth;
     int descent;
     int charLast;
     int charSize;
     int _wmapAddr;
     int _cmapAddr;
     int _unknown4;
} rbf_font;
static int need_free=0;;

//-------------------------------------------------------------------
static int win2dos(int ch) {
    if (ch>=192 && ch<=255) {
       if (ch<=239) ch-=64;
       else         ch-=16;
    }
    return ch;
}

//-------------------------------------------------------------------
int rbf_load(char *file) {
/*
    name         - name of font (max 64 characters)
    width        - font element width in pixels
    height       - font element height in pixels
    points       - font size in points
    charFirst    - ASCII code of first char, presents in font
    charCount    - count of chars containing in font
    cTable       - List of chars. Element of list is a bytecode string,
                   contains pixels representation  of char
    wTable       - List of character widths. Elements of list
                   is width of char 
    intline      - Interline spasing
    maxWidth     - width of widhest char in pixels
    descent      - font descent
    '''
*/        

    int fd;
    char buf[8];
    int i;

    fd = open(file, O_RDONLY, 0777);
    if (fd>=0 && read(fd, &buf, 8)==8 /* Magic number */ && memcmp(&buf, RBF_HDR_MAGIC, 8)==0) {

        read(fd, &rbf_font.name, RBF_MAX_NAME);
        read(fd, &rbf_font.charSize , 4);
        read(fd, &rbf_font.points   , 4);
        read(fd, &rbf_font.height   , 4);
        read(fd, &rbf_font.maxWidth , 4);
        read(fd, &rbf_font.charFirst, 4);
        read(fd, &rbf_font.charLast , 4);
        read(fd, &rbf_font._unknown4, 4);
        read(fd, &rbf_font._wmapAddr, 4);
        read(fd, &rbf_font._cmapAddr, 4);
        read(fd, &rbf_font.descent  , 4);
        read(fd, &rbf_font.intline  , 4);

        rbf_font.width = 8 * rbf_font.charSize / rbf_font.height;
        rbf_font.charCount = rbf_font.charLast - rbf_font.charFirst + 1;

        for (i=0; i<256; ++i) {
            rbf_font.wTable[i]=0; 
            if (need_free && rbf_font.cTable[i]) {
                free(rbf_font.cTable[i]);
            }
            rbf_font.cTable[i]=NULL;
        }
        need_free = 0;

        lseek(fd, rbf_font._wmapAddr, SEEK_SET);
        for (i=rbf_font.charFirst; i<=rbf_font.charLast; ++i) {
            read(fd, &rbf_font.wTable[win2dos(i)], 1);
        }

        lseek(fd, rbf_font._cmapAddr, SEEK_SET);
        for (i=rbf_font.charFirst; i<=rbf_font.charLast; ++i) {
            rbf_font.cTable[win2dos(i)]=malloc(rbf_font.charSize);
            read(fd, rbf_font.cTable[win2dos(i)], rbf_font.charSize);
        }
        need_free = 1;

        close(fd);
        return 1;
    }

    return 0;
}

//-------------------------------------------------------------------
void rbf_load_from_8x16(const char *font) {
    int i;

    rbf_font.charSize  = 16;
    rbf_font.height    = 16;
    rbf_font.maxWidth  = 8;
    rbf_font.charFirst = 0;
    rbf_font.charLast  = 255;

    rbf_font.width = 8 * rbf_font.charSize / rbf_font.height;
    rbf_font.charCount = rbf_font.charLast - rbf_font.charFirst + 1;

    for (i=0; i<256; ++i) {
        rbf_font.wTable[i]=8; 
        if (need_free && rbf_font.cTable[i]) {
            free(rbf_font.cTable[i]);
        }
        rbf_font.cTable[i]=NULL;
    }
    need_free = 0;

    for (i=rbf_font.charFirst; i<=rbf_font.charLast; ++i) {
        rbf_font.cTable[i]=malloc(rbf_font.charSize);
        memcpy(rbf_font.cTable[i], font+i*rbf_font.charSize, rbf_font.charSize);
    }
    need_free = 1;
}

//-------------------------------------------------------------------
int rbf_font_height() {
    return rbf_font.height;
}

//-------------------------------------------------------------------
int rbf_char_width(int ch) {
    return rbf_font.wTable[ch];
}

//-------------------------------------------------------------------
int rbf_draw_char(int x, int y, int ch, color cl) {
    int xx, yy;

    for (yy=0; yy<rbf_font.height; ++yy){
	for (xx=0; xx<rbf_font.wTable[ch]; ++xx){
            draw_pixel(x+xx ,y+yy, (rbf_font.cTable[ch][yy*rbf_font.width/8+xx/8] & (1<<(xx%8)))? cl&0xff : cl>>8);
	}
    }
    return rbf_char_width(ch);
}

//-------------------------------------------------------------------
