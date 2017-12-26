
SCRDIR		= ../scripts
LDSCRNAME	= _real.ld

include $(SCRDIR)/Rules

CFLAGS		+= 
ODFLAGS		+= --section-headers              -D 

# we want no space characters after last letter
TMPDIR		= ../temp
SCRDIR		= ../scripts
THISDIRNAME	= kernel
THISDIR		= ../$(THISDIRNAME)
TRGNAME		= wholething

include $(SCRDIR)/Rules

ifneq ($(ODD_MAKE),y)
all:
	$(CC) $(CFLAGS) -c _kernel.c -o $(TMPDIR)/$(TRGNAME).o 
	mv $(TMPDIR)/head.o $(TMPDIR)/head.o0
	echo ODD_MAKE=y >.allsrcs
	echo OBJFILES  = \\>>.allsrcs
	find $(TMPDIR)/*.o -type f -print | sort | xargs >> .allsrcs 	
	echo OBJFILE  = \\>>.allsrcs
	find $(TMPDIR)/*.o0 -type f -print | sort | xargs >> .allsrcs 	
	echo oBJFILE  = \\>>.allsrcs
	find $(TMPDIR)/*.O -type f -print | sort | xargs >> .allsrcs 	
	cat Makefile >> .allsrcs
	make -f .allsrcs kernel 
	mv $(TMPDIR)/head.o0 $(TMPDIR)/head.o
	rm -f .allsrcs 
endif

ifneq ($(TARGET),INTEL)
ifneq ($(TARGET),REAL)
kernel:
	######## it's no good if you see this one in commandline ########
else
kernel: $(OBJFILES) 
	$(LD) $(OBJFILES) -o 	$(TRGNAME).linked.image -T$(SCRDIR)/$(LDSCRNAME)  
	$(OC) -O srec 		$(TRGNAME).linked.image   $(TRGNAME).s19 
	$(SB) 						  $(TRGNAME).s19 > $(TRGNAME).b 
	$(NM) 			$(TRGNAME).linked.image > $(TRGNAME).map
	$(SZ) 			$(TRGNAME).linked.image > $(TRGNAME).siz
	$(OD) $(ODFLAGS)	$(TRGNAME).linked.image > $(TRGNAME).odf	
endif 	
else
kernel: $(OBJFILE) $(OBJFILES) $(oBJFILE) 
	$(LD) -m elf_i386 -Ttext 0x90200  -Tdata 0x94800 -Tbss 0x94A00 --section-start dtidt=95000 --entry=up_32  -o CORE.img $(OBJFILE) $(OBJFILES) 
	objdump -D --section-headers CORE.img > CORE.odf  
	objcopy -O binary -R .note -R .comment CORE.img CORE 
	rm -f CORE.img
	$(LD)  -Ttext 0x0 -o TRAMPOLINE $(oBJFILE) --entry=_rundschau_start -s --oformat binary 
	cat TRAMPOLINE CORE > wholething
	cat wholething > /dev/fd0     
endif

clean:
	rm -f *.[oa] *.coff *~ core _ker *.s19  *.map *.odf *.siz  *.b  .allsrcs .mk *.linked.image $(TRGNAME) TRAMPOLINE CORE 
