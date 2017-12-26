
CFLAGS		+= 
ASFLAGS		+=  -Wa,--bitwise-or 

EMPT	 = $(SRCS:.S=) 
EMPTY	 = $(SRCSY:.s=)
DEPS	 = $(SRCS:.S=.d)
DEPSY	 = $(SRCSY:.s=.D)

# we want no space characters after last letter
TMPDIR		= ../temp
SCRDIR		= ../scripts
THISDIRNAME	= assembly
THISDIR		= ../$(THISDIRNAME)

include $(SCRDIR)/Rules

ifneq ($(DEPS_DONE),y)
ifeq ($(ODD_MAKE),y)
all:	$(DEPS) $(DEPSY)
	echo > $(TMPDIR)/$(THISDIRNAME).dep
	cat $(TMPDIR)/*.d $(TMPDIR)/*.D >> $(TMPDIR)/$(THISDIRNAME).dep
	rm $(TMPDIR)/*.d $(TMPDIR)/*.D 
	echo include $(SCRDIR)/Rules > .mk
	echo DEPS_DONE=y >.mk	
	echo SRCS  = \\>>.mk
	find *.S -type f -print | sort | xargs >> .mk	
	echo SRCSY = \\>>.mk
	find *.s -type f -print | sort | xargs >> .mk	
	echo -n all : >>.mk	
	for i in $(EMPT); do echo $(TMPDIR)/$$i.o \\>> .mk; done	
	for i in $(EMPTY);do echo $(TMPDIR)/$$i.O >> .mk; done	
	echo    >> .mk	
	cat Makefile >> .mk
	echo include $(TMPDIR)/$(THISDIRNAME).dep >>.mk
	make -f .mk all
	rm -f .mk
	
else
ifneq ($(ODD_MAKE),y)
all:
	echo ODD_MAKE=y >.allsrcs
	echo SRCS  = \\>>.allsrcs
	find *.S -type f -print | sort | xargs >> .allsrcs  
	echo SRCSY  = \\>>.allsrcs
	find *.s -type f -print | sort | xargs >> .allsrcs  
	cat Makefile >> .allsrcs
	make -f .allsrcs
	rm -f .allsrcs
endif
endif
endif

%.d: %.S 
	echo $(TMPDIR)/\\>$(TMPDIR)/$@
	$(CC) $(CFLAGS) -M $<  >>$(TMPDIR)/$@

%.D: %.s 
	echo $(TMPDIR)/\\>$(TMPDIR)/$@
	echo reset.O: reset.s >>$(TMPDIR)/$@
###$(CC) -M $<  >>$(TMPDIR)/$@    (Im still thinking how to do this place)

$(TMPDIR)/%.o: $(THISDIR)/%.S
	$(CC) -traditional -c -o $@ $<

$(TMPDIR)/%.O: $(THISDIR)/%.s
	$(AS) -o $@ $<

clean:
	rm -f .mk .allsrcs 

