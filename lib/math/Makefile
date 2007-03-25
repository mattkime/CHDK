topdir=../../

include $(topdir)makefile.inc

OBJS = ef_log.o ef_sqrt.o ef_pow.o sf_fabs.o s_scalbnf.o s_copysignf.o

all: libmath.a

libmath.a: $(OBJS)

ef_log.o: ef_log.c fdlibm.h

ef_pow.o: ef_pow.c fdlibm.h

sf_fabs.o: sf_fabs.c fdlibm.h

s_scalbnf.o: s_scalbnf.c fdlibm.h

s_copysignf.o: s_copysignf.c fdlibm.h

clean:
	rm -f $(OBJS) libmath.a
