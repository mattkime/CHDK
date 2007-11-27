topdir=../../

include $(topdir)makefile.inc

DUMPER_LOCATION=0x1400000

LDOPTS=-nostdlib -Wl,--allow-shlib-undefined -Wl,--no-define-common,-EL,-T,$(topdir)tools/link-boot.ld
LDOPTS+=-Wl,-N,-Ttext,$(DUMPER_LOCATION)

all: main.bin

OBJS=entry.o main.o

main.bin: main.elf
	@echo $< \-\> $@
	$(OBJDUMP) -z -D main.elf > main.dump
	arm-elf-readelf -a main.elf > main.relf.txt
	$(OBJCOPY) -O binary main.elf main.bin

main.elf: $(OBJS)
	@echo \-\> $@
	$(CC) $(CFLAGS) -o $@ $^   $(LDLIBS) $(LDFLAGS) $(LDOPTS)
	( $(NM) $@ | grep ' U ' > $@.syms ) && exit 1 || exit 0

clean:
	rm -f $(OBJS) main.bin main.elf main.dump main.elf.syms

distclean: distclean-recursive
	rm -f $(OBJS) main.bin main.elf main.dump main.elf.syms

include $(topdir)bottom.inc
