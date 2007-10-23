VER=pre14

PLATFORM=ixus65
PLATFORMSUB=100a
OSTYPE = Windows

#PLATFORM=a610
#PLATFORMSUB=100e

#PLATFORM=a620
#PLATFORMSUB=100f

#PLATFORM=a630
#PLATFORMSUB=100c

#PLATFORM=a640
#PLATFORMSUB=100b

#PLATFORM=a700
#PLATFORMSUB=100b

#PLATFORM=a710
#PLATFORMSUB=100a

#PLATFORM=s2is
#PLATFORMSUB=100f

#PLATFORM=s3is
#PLATFORMSUB=100a

include $(topdir)version.inc
include $(topdir)platform/$(PLATFORM)/sub/$(PLATFORMSUB)/makefile.inc

SILENT=SILENT

NOZERO100K=TRUE

##########################################################################
##########################################################################
##########################################################################

ifndef OSTYPE
  HOSTPLATFORM:=$(shell uname -s | head -c 5)
  ifeq ($(HOSTPLATFORM),MINGW)
    OSTYPE = Windows
    EXE = .exe
    SH = sh
    DEVNULL = NUL
    SORT = $(dir $(shell which uniq.exe | sed s/\\\\/\\\//g))/sort.exe
    GCC_DIR=D:/projects/canon-hdk/gcc_env
  else
    ifeq ($(HOSTPLATFORM),Linux)
      OSTYPE = Linux
      EXE =
      SH =
      DEVNULL = /dev/null
      SORT = sort
      # TBD
      GCC_DIR=/usr
    else
      OSTYPE = Other
      EXE =
      SH =
      DEVNULL = /dev/null
      SORT = sort
      # TBD
      GCC_DIR=/usr
    endif
  endif
else
  EXE = .exe
  SH = 
  DEVNULL = /dev/null
  SORT = sort
  GCC_DIR=$(topdir)/../../gcc_env
endif

##########################################################################
##########################################################################
##########################################################################

HOSTCC=gcc
HOSTCFLAGS=-g -O2 -Wall

PAKWIF=$(topdir)tools/pakwif$(EXE)

GCC_INCLUDE=$(GCC_DIR)/include
GCC_ARM_INCLUDE=$(GCC_DIR)/lib/gcc/arm-elf/4.1.1/include

##########################################################################

#export PATH+=

CC=arm-elf-gcc
OBJCOPY=arm-elf-objcopy
OBJDUMP=arm-elf-objdump
STRIP=arm-elf-strip
NM=arm-elf-nm
AR=arm-elf-ar
RANLIB=arm-elf-ranlib
SIZE=arm-elf-size

# -msoft-float is used per default but object files are marked as hard-float
CFLAGS=-mfloat-abi=soft -fno-inline -Os -fno-strict-aliasing
# flags for gcc v4
#CFLAGS+=-mtune=arm946e-s
#-mthumb
CTHUMB=
CFLAGS+=-mthumb-interwork
CFLAGS+=-I$(topdir)include $(PLFLAGS) $(CPPFLAGS)
CFLAGS+=-DPLATFORM=\"$(PLATFORM)\" -DPLATFORMSUB=\"$(PLATFORMSUB)\" -DHDK_VERSION=\"$(VER)\" -DBUILD_NUMBER=\"$(BUILD_NUMBER)\" -DCAMERA_$(PLATFORM)
CFLAGS+=-Wall -Wno-unused -Wno-format
CFLAGS+=-I$(GCC_INCLUDE) -I$(GCC_ARM_INCLUDE)

LDFLAGS=-L$(topdir)lib/math -L$(topdir)lib/font
LDFLAGS+=-L$(topdir)lib/libc -L$(topdir)lib/ubasic
LDFLAGS+=-L$(topdir)platform/$(PLATFORM) -L$(topdir)platform/$(PLATFORM)/sub/$(PLATFORMSUB)


##########################################################################

default: all

ifndef SKIPBUILDRULES

%.o: %.c
	@echo $< \-\> $@
	$(CC) $(CFLAGS) -nostdinc -c -o $@ $<
%.opp: %.cpp
	@echo $< \-\> $@
	$(CC) $(CFLAGS) -nostdinc -c -o $@ $<
%.o: %.S
	@echo $< \-\> $@
	$(CC) $(CFLAGS) -nostdinc -c -o $@ $<
%.a:
	@echo $^ \-\> $@
	$(AR) rcs $@ $^

.dep/%.d: %.c
	echo Making $@
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -M $< | sed 's/[cdCD]:.*.h//g' | sed 's/$.+.o //g'> $@

.dep/%.d: %.S
	echo Making $@
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -M $< | sed 's/[cdCD]:.*.h//g' > $@

endif

all: all-recursive
clean: clean-recursive
distclean: distclean-recursive

.dep:
	mkdir .dep

clean-recursive:
	@for i in $(SUBDIRS); do \
	    echo \>\> Cleaning in $(FOLDER)$$i; \
	    $(MAKE) -C $$i FOLDER="$(FOLDER)$$i/" clean || exit 1; \
	done

distclean-recursive:
	@for i in $(SUBDIRS); do \
	    echo \>\> Distcleaning in $(FOLDER)$$i; \
	    $(MAKE) -C $$i FOLDER="$(FOLDER)$$i/" distclean || exit 1; \
	done

all-recursive:
	for i in $(SUBDIRS); do \
	    echo \>\> Entering to $(FOLDER)$$i; \
	    $(MAKE) -C $$i FOLDER="$(FOLDER)$$i/" || exit 1; \
	    echo \<\< Leaving $(FOLDER)$$i; \
	done

depend-recursive:
	@for i in $(SUBDIRS); do \
	    echo \>\> Entering to $(FOLDER)$$i; \
	    $(MAKE) -C $$i FOLDER="$(FOLDER)$$i/" depend || exit 1; \
	    echo \<\< Leaving $(FOLDER)$$i; \
	done

ifdef SILENT
.SILENT:
endif
