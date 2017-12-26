
CFLAGS		+=  

EMPT = $(SRCS:.c=)
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

# we want no space characters after last letter
TMPDIR		= ../temp
SCRDIR		= ../scripts
THISDIRNAME	= c
THISDIR		= ../$(THISDIRNAME)

include $(SCRDIR)/Rules

ifneq ($(DEPS_DONE),y)
ifeq ($(ODD_MAKE),y)
all:	$(DEPS)
	echo > $(TMPDIR)/$(THISDIRNAME).dep
	cat $(TMPDIR)/*.d >> $(TMPDIR)/$(THISDIRNAME).dep
	rm $(TMPDIR)/*.d
	echo include ../$(SCRDIR)/Rules > .mk
	echo DEPS_DONE=y >.mk	
	echo SRCS  = \\>>.mk
	find *.c -type f -print | sort | xargs >> .mk	
	echo -n all : >>.mk	
	for i in $(EMPT); do echo $(TMPDIR)/$$i.o \\>> .mk; done	
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
	find *.c -type f -print | sort | xargs >> .allsrcs 	
	cat Makefile >> .allsrcs
	make -f .allsrcs
	rm -f .allsrcs 
endif
endif
endif

%.d: %.c
	echo $(TMPDIR)/\\>$(TMPDIR)/$@
	$(CC) $(CFLAGS) -M $<  >>$(TMPDIR)/$@

$(TMPDIR)/%.o: $(THISDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f .mk .allsrcs 

