topdir=../../

include $(topdir)makefile.inc

OBJS = font_8x16.o rbf_font.o

all: libfont.a

libfont.a: $(OBJS)

font_8x16.o: font_8x16.c font_8x16_def.h font_8x16_kbr.h font_8x16_uni.h font_8x16_rus.h

clean:
	rm -f $(OBJS) libfont.a
