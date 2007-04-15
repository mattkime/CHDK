#include "stdlib.h"
#include "gui.h"
#include "font.h"

//-------------------------------------------------------------------
#define RBF_HDR_SIZE       0x74
#define RBF_MAX_NAME       64

//-------------------------------------------------------------------
const char *RBF_HDR_MAGIC = "\xE0\x0E\xF0\x0D\x03\x00\x00\x00";
/*
const char tbl_dos2win[] = {
    192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,
    208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,
    224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,
    136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,
    152,153,154,129,156,157,158,159,160,161,162,163,164,165,166,167,
    168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,
    240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,
    130,132,135,134,128,133,131,155,184,185,186,187,188,189,190,191
};
*/
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
static int need_free    = 0;
static int rbf_codepage = FONT_CP_WIN; 

//-------------------------------------------------------------------
static int win2dos(int ch) {
    switch (ch) {
        case 0xAA: return 0xF2;  // ò
        case 0xBA: return 0xF3;  // ó
        case 0xAF: return 0xF4;  // ô
        case 0xBF: return 0xF5;  // õ
        default:
            if (ch>=192 && ch<=255) {
               if (ch<=239) ch-=64;
               else         ch-=16;
            }
            return ch;
    }
}

//-------------------------------------------------------------------
static int dos2win(int ch) {
    switch (ch) {
        case 0xF2: return 0xAA;  // ò
        case 0xF3: return 0xBA;  // ó
        case 0xF4: return 0xAF;  // ô
        case 0xF5: return 0xBF;  // õ
        default:
            if (ch>=128 && ch<=175) {
               ch+=64;
            } else if (ch>=224 && ch<=239) {
               ch+=16;
            }
            return ch;
    }
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
            read(fd, &rbf_font.wTable[i], 1);
        }

        lseek(fd, rbf_font._cmapAddr, SEEK_SET);
        for (i=rbf_font.charFirst; i<=rbf_font.charLast; ++i) {
            rbf_font.cTable[i]=malloc(rbf_font.charSize);
            read(fd, rbf_font.cTable[i], rbf_font.charSize);
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
        rbf_font.cTable[dos2win(i)]=malloc(rbf_font.charSize);
        memcpy(rbf_font.cTable[dos2win(i)], font+i*rbf_font.charSize, rbf_font.charSize);
    }
    need_free = 1;
}

//-------------------------------------------------------------------
void rbf_set_codepage(int codepage) {
    rbf_codepage = codepage;
}

//-------------------------------------------------------------------
int rbf_font_height() {
    return rbf_font.height;
}

//-------------------------------------------------------------------
int rbf_char_width(int ch) {
    switch (rbf_codepage) {
        case FONT_CP_WIN: 
            break;
        case FONT_CP_DOS: 
            ch = dos2win(ch); 
            break;
    }
    return rbf_font.wTable[ch];
}

//-------------------------------------------------------------------
int rbf_draw_char(int x, int y, int ch, color cl) {
    int xx, yy;

    switch (rbf_codepage) {
        case FONT_CP_WIN: 
            break;
        case FONT_CP_DOS: 
            ch = dos2win(ch); 
            break;
    }

    for (yy=0; yy<rbf_font.height; ++yy) {
	for (xx=0; xx<rbf_font.wTable[ch]; ++xx) {
            draw_pixel(x+xx ,y+yy, (rbf_font.cTable[ch][yy*rbf_font.width/8+xx/8] & (1<<(xx%8)))? cl&0xff : cl>>8);
	}
    }
    return rbf_font.wTable[ch];
}

//-------------------------------------------------------------------
