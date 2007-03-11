topdir=../

include $(topdir)makefile.inc

all: pakwif$(EXE) finsig$(EXE) hexdmplt$(EXE)

pakwif$(EXE): pakwif.c
	$(HOSTCC) $(HOSTCFLAGS) -o pakwif$(EXE) pakwif.c

gensig$(EXE): gensig.c
	$(HOSTCC) $(HOSTCFLAGS) -o gensig$(EXE) gensig.c

hexdmplt$(EXE): hexdmplt.c
	$(HOSTCC) $(HOSTCFLAGS) -o hexdmplt$(EXE) hexdmplt.c

finsig$(EXE): finsig.c signatures.h
	$(HOSTCC) $(HOSTCFLAGS) -o finsig$(EXE) finsig.c

clean:
	rm -f pakwif$(EXE) gensig$(EXE) finsig$(EXE) hexdmplt$(EXE)
	if [ -s sig_ref.bin ] ; then \
	  rm -f signatures.h ; \
	fi

signatures.h: gensig$(EXE) gensigs.sh sig_ref.txt sig_ref.bin
	if [ -s sig_ref.bin ] ; then \
	  $(SH) ./gensigs.sh sig_ref.txt sig_ref.bin $(ROMBASEADDR) > signatures.h ; \
	else \
	  echo CAUTION! \'signatures.h\' is not uptated due to \'sig_ref.bin\` is empty! ; \
	  touch signatures.h ; \
	fi

sig_ref.bin:
	touch sig_ref.bin
