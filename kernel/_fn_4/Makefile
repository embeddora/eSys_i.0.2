#CROSS = m68k-coff-

CROSS = 

CC	= $(CROSS)gcc
LD	= $(CROSS)ld
OD	= $(CROSS)objdump

LDFLAGS = -r  
CFLAGS	= 

# we want no space characters after last letter
THISDIRNAME	= _fn_4
FILENAME	= $(THISDIRNAME)
THISDIR		= ../$(THISDIRNAME)

LDFLAGS = -m elf_i386 -Ttext 100 -Tdata 500  --entry=100  

#_OFFS_BETWEEN_TEXT_AND_DATA_ = 0x400 = which is 1024 in decimal (see linkerflags)


CFLAGS += -D_OFFS_BETWEEN_TEXT_AND_DATA_=0x400 -nostartfiles -nostdlib -O0 -D_OFFS_BETWEEN_TEXT_AND_AUX_SEG_=0xE00 
##$(LD) -m elf_i386 -Ttext 0x90200  -Tdata 0x94800 -Tbss 0x94A00 --section-start 
#dtidt=95000 --entry=up_32  -o CORE.img $(OBJFILE) $(OBJFILES) 

OBJ = $(FILENAME).o

all:	$(FILENAME) 
	../../scripts/headmaker >$(FILENAME).fn
	dd if=$(FILENAME) of=$(FILENAME).bin bs=1 skip=256
	cat $(FILENAME).bin >>$(FILENAME).fn
	$(OD) -D -s $(THISDIRNAME) > $(THISDIRNAME).asm
	rm -f  $(FILENAME) $(FILENAME).o $(FILENAME).bin 





$(FILENAME): $(FILENAME).o
	ld $(LDFLAGS) $(OBJ) -o $@ 

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f  $(FILENAME).o  $(FILENAME).fn $(FILENAME).asm $(FILENAME)  .out   $(FILENAME).bin 

