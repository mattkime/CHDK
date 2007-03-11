topdir=../

include $(topdir)makefile.inc

# warning: library order matters!
LDLIBS= -lfont -lplatform -lplatformsub -lubasic -lmath  -lc -lgcc
#LDOPTS=-nostdlib -Wl,--allow-shlib-undefined -Wl,--no-define-common,-EL,-T,$(topdir)tools/link.RAM
LDOPTS=-nostdlib -Wl,--allow-shlib-undefined -Wl,-T,$(topdir)tools/link.RAM
LDOPTS+=-Wl,-N,-Ttext,$(MEMISOSTART)

all: main.bin

OBJS=entry.o main.o gui_draw.o gui_menu.o gui_palette.o gui_mbox.o gui_reversi.o gui_debug.o gui.o kbd.o conf.o

main.bin: main.elf
	$(OBJDUMP) -z -d main.elf > main.dump
	$(OBJCOPY) -O binary main.elf main.bin

main.elf: $(OBJS) $(topdir)platform/$(PLATFORM)/libplatform.a \
          $(topdir)platform/$(PLATFORM)/sub/$(PLATFORMSUB)/libplatformsub.a \
          $(topdir)lib/font/libfont.a $(topdir)lib/libc/libc.a \
          $(topdir)lib/ubasic/libubasic.a $(topdir)lib/math/libmath.a
	$(CC) $(CFLAGS) -o $@ $^   $(LDLIBS) $(LDFLAGS) $(LDOPTS)
	( $(NM) $@ | grep ' U ' > $@.syms ) && exit 1 || exit 0

clean:
	rm -f $(OBJS) main.bin main.elf main.dump main.elf.syms
 
