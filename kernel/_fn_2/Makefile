#CROSS = m68k-coff-
CROSS = 

CC	= $(CROSS)gcc
LD	= $(CROSS)ld
OD	= $(CROSS)objdump

LDFLAGS = -r  
CFLAGS	= 

# we want no space characters after last letter
THISDIRNAME	= _fn_2
FILENAME	= $(THISDIRNAME)
THISDIR		= ../$(THISDIRNAME)

LDFLAGS += -Ttext 400300 -Tdata 400400 
CFLAGS += -nostartfiles -nostdlib -O0 

OBJ = $(FILENAME).o

all:	$(FILENAME) 
	../../scripts/headmaker >$(FILENAME).fn
	dd if=$(FILENAME) of=$(FILENAME).bin bs=1 skip=52
	cat $(FILENAME).bin >>$(FILENAME).fn
	$(OD) -D -s $(THISDIRNAME) > $(THISDIRNAME).asm
	rm -f  $(FILENAME) $(FILENAME).o $(FILENAME).bin 

$(FILENAME): $(FILENAME).o
	ld $(LDFLAGS) $(OBJ) -o $@ 

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f  $(FILENAME).o  $(FILENAME).fn $(FILENAME).asm $(FILENAME)  .out   $(FILENAME).bin 

