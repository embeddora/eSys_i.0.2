
include scripts/Rules

INTEL_DIRS = assembly c  kernel

EVERNEW_DIRS = assembly c kernel 
TARGET = nothing_yet 

all:	
	for j in $(INTEL_DIRS) ; do make -C $$j clean; done	
	for j in $(INTEL_DIRS) ; do make -C $$j TARGET=INTEL; done 

clean:
	for j in $(EVERNEW_DIRS) ; do make -C $$j clean; done	

totalclean:
	for j in $(EVERNEW_DIRS) temp; do make -C $$j clean; done	


