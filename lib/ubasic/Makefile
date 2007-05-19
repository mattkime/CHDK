topdir=../../

include $(topdir)makefile.inc

CFLAGS+=$(CTHUMB)

OBJS = camera_functions.o tokenizer.o ubasic.o

all: libubasic.a

libubasic.a: $(OBJS)

check:
	gcc -g -Wall -DTEST -o ubasic_test$(EXE) *.c

clean:
	rm -f $(OBJS) libubasic.a ubasic_test$(EXE)
