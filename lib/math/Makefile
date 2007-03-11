topdir=../../

include $(topdir)makefile.inc

OBJS = ef_log.o rnd.o

all: libmath.a

libmath.a: $(OBJS)

ef_log.o: ef_log.c fdlibm.h

clean:
	rm -f $(OBJS) libmath.a
