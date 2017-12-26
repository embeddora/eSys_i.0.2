

SETUPSECTS	= 48  			
BOOTSEG		= 0x07C0		
INITSEG		= 0x9000
SETUPSEG	= 0x9020
SYSSEG		= 0x1000		
SYSSIZE		= 0x6F00 /* allows kersize about 28 KB */

					
ROOT_DEV	= 0 			
SWAP_DEV	= 0			

.code16
.text

.global _rundschau_start
_rundschau_start:

# First things first. Move ourself from 0x7C00 -> 0x90000 and jump there.

	movw	$BOOTSEG, %ax
	movw	%ax, %ds		# %ds = BOOTSEG
	movw	$INITSEG, %ax
	movw	%ax, %es		# %ax = %es = INITSEG
	movw	$256, %cx
	subw	%si, %si
	subw	%di, %di
	cld
	rep
	movsw
	ljmp	$INITSEG, $go	
	
go:	movw	$0x9000-12, %di		# 0x4000 is an arbitrary value >=
					# length of bootsect + length of
					# setup + room for stack;
					# 12 is disk parm size.
	movw	%ax, %ds		# %ax and %es already contain INITSEG
	movw	%ax, %ss
	movw	%di, %sp		# put stack at INITSEG:0x4000-12.

# Many BIOS's ...

	movw	%cx, %fs		# %fs = 0
	movw	$0x78, %bx		# %fs:%bx is parameter table dress
	pushw	%ds
	ldsw	%fs:(%bx), %si		# %ds:%si is source
	movb	$6, %cl			# copy 12 bytes
	pushw	%di			# %di = 0x4000-12.
	rep				# don't worry about cld
	movsw				# already done above
	popw	%di
	popw	%ds
	movb	$36, 0x4(%di)		# patch sector count
	movw	%di, %fs:(%bx)
	movw	%es, %fs:2(%bx)

# Get disk ...

##---------BIOS-port-addr-check-----(store-in-DX)-----------------------------
    sti	    
      
    pushw	%fs			# fs to save on the stack
    movw	$0x0040, %ax		# 
    movw	%ax, %fs		# fs to assign 0040
    movw	$0x0000, %bx		# fs to assign 0000
    pushw	%ds			# ds to save on the stack
    ldsw	%fs:(%bx), %dx		# 40:0000 is source == addr of COMPORT 1
    popw	%ds
    popw	%fs   
    
    movw	%dx, %bx            
    
##---------interrupt-output-(BIOS-routines)----------------------------------    
    
    movw	$0x0000, %dx		# COM1
    movb	$0x00, %ah		# function 0 (init)
#   movb	$0xA3, %al		# 8N1, no parity , 2400
    movb	$0xE3, %al		# 8N1, no parity , 9600
    int		$0x14


    movb	%bh, %al        
    addb	$0x4C, %al
    movw	$0x0000, %dx		# COM1
    movb	$0x01, %ah		# function 1 (transmchar)
    int		$0x14
    
    movb	%bl, %al
    subb	$0xAD, %al
    movw	$0x0000, %dx		# COM1
    movb	$0x01, %ah		# function 1 (transmchar)
    int		$0x14	
    
    cli	
##---------------------------------------------------------------------------

	movw	$disksizes, %si		# table of sizes to try
probe_loop:
	lodsb
	cbtw				# extend to word
	movw	%ax, sectors
	cmpw	$disksizes+4, %si
	jae	got_sectors		# If all else fails, try 9

	xchgw	%cx, %ax		# %cx = track and sector
	xorw	%dx, %dx		# drive 0, head 0
	movw	$0x0200, %bx		# address = 512, in INITSEG (%es = %cs)
	movw	$0x0201, %ax		# service 2, 1 sector
	int	$0x13
	jc	probe_loop		# try next value

got_sectors:

	movb	$0x01, %ah		# hide cursor 
	xorb	$0x20, %ch
	int	$0x10


# Load the setup-sectors directly after the moved bootblock (at 0x90200).
# We should know the drive geometry to do it, as setup may exceed first
# cylinder (for 9-sector 360K and 720K floppies).

	movw	$0x0001, %ax		# set sread (sector-to-read) to 1 as
	movw	$sread, %si		# the boot sector has already been read
	movw	%ax, (%si)

	xorw	%ax, %ax		# reset FDC
	xorb	%dl, %dl
	int	$0x13
	movw	$0x0200, %bx		# address = 512, in INITSEG
next_step:
	movb	setup_sects, %al
	movw	sectors, %cx
	subw	(%si), %cx		# (%si) = sread
	cmpb	%cl, %al
	jbe	no_cyl_crossing
	movw	sectors, %ax
	subw	(%si), %ax		# (%si) = sread
no_cyl_crossing:
	call	read_track
	pushw	%ax			# save it
	call	set_next		# set %bx properly; it uses %ax,%cx,%dx
	popw	%ax			# restore
	subb	%al, setup_sects	# rest - for next step
	jnz	next_step

	pushw	$SYSSEG
	popw	%es			# %es = SYSSEG
	
    	
	call	read_it
	call	print_nl		
	call	kill_motor
	

	# SECOND ATTEMPT 
	movb	$0xD1, %al			# command write
	outb	%al, $0x64
	movb	$0xDF, %al			# A20 on
	outb	%al, $0x60
    
	call	print_nl		

	# TRHIRD ATTEMPT 	
	inb	$0x92, %al			# Configuration Port A
	orb	$0x02, %al			# "fast A20" version
	andb	$0xFE, %al			# don't accidentally reset
	outb	%al, $0x92	
	
	xorl	%eax, %eax		# Compute gdt_base
	movw	$INITSEG, %ax		# (Convert %ds:gdt to a linear ptr)
	shll	$4, %eax
	addl	$gdt, %eax
	movl	%eax, (gdt_48+2)		
	
	lgdt	gdt_48			# load gdt with whatever is	
	movw	$1, %ax			# protected mode (PE) bit
	
	lmsw	%ax			# This is it!	
	

# the following is a sad evidence that Red Hat people do read wrong books :-) (I mean their idea to patch code current with following datastuff)
	.byte 0x66, 0xea	# prefix + jmpi-opcode
	.long 0x90200		# 
	.word 8			#.word	__KERNEL_CS
	
jk:	jmp	jk

# These variables are addressed via %si register as it gives shorter code.

sread:	.word 0			# sectors read of current track
head:	.word 0			# current head
track:	.word 0			# current track

# This routine loads the system at address SYSSEG, making sure
# no 64kB boundaries are crossed. We try to load it as fast as
# possible, loading whole tracks whenever we can.

read_it:
	movw	%es, %ax	# %es = SYSSEG when called
	testw	$0x0fff, %ax
	
die:	jne	die		# %es must be at 64kB boundary
	xorw	%bx, %bx	# %bx is starting address within segment
rp_read:

	cmpw	syssize, %ax	# have we loaded everything yet?
	jbe	ok1_read


################ output newline + car. Ret.

zack:
	pusha

	movb	$13, %al        
	movw	$0x0000, %dx		# COM1
	movb	$0x01, %ah		# function 1 (transmchar)
	int	$0x14
	
	movb	$10, %al        
	movw	$0x0000, %dx		# COM1
	movb	$0x01, %ah		# function 1 (transmchar)
	int	$0x14
	
	popa
	
################


	ret

ok1_read:
	movw	sectors, %ax
	subw	(%si), %ax	# (%si) = sread
	movw	%ax, %cx
	shlw	$9, %cx
	addw	%bx, %cx
	jnc	ok2_read

	je	ok2_read

	xorw	%ax, %ax
	subw	%bx, %ax
	shrw	$9, %ax
ok2_read:
	call	read_track
	call	set_next
	jmp	rp_read

read_track:
	pusha
	pusha	
	
	movb	$0x2e, %al        
	movw	$0x0000, %dx		# COM1
	movb	$0x01, %ah		# function 1 (transmchar)
	int	$0x14
		
	popa	
	

# Accessing head, track, sread via %si gives shorter code.

	movw	4(%si), %dx	# 4(%si) = track
	movw	(%si), %cx	# (%si)  = sread
	incw	%cx
	movb	%dl, %ch
	movw	2(%si), %dx	# 2(%si) = head
	movb	%dl, %dh
	andw	$0x0100, %dx
	movb	$2, %ah
	pushw	%dx		# save for error dump
	pushw	%cx
	pushw	%bx
	pushw	%ax
	int	$0x13
	jc	bad_rt

	addw	$8, %sp
	popa
	ret

set_next:
	movw	%ax, %cx
	addw	(%si), %ax	# (%si) = sread
	cmp	sectors, %ax
	jne	ok3_set
	movw	$0x0001, %ax
	xorw	%ax, 2(%si)	# change head
	jne	ok4_set
	incw	4(%si)		# next track
ok4_set:
	xorw	%ax, %ax
ok3_set:
	movw	%ax, (%si)	# set sread
	shlw	$9, %cx
	addw	%cx, %bx
	jnc	set_next_fin
	movw	%es, %ax
	addb	$0x10, %ah
	movw	%ax, %es
	xorw	%bx, %bx
set_next_fin:
	ret

bad_rt:
	pushw	%ax		# save error code
#	call	print_all	# %ah = error, %al = read
	xorb	%ah, %ah
	xorb	%dl, %dl
	int	$0x13
	addw	$10, %sp
	popa
	jmp read_track

# print_all is for debugging purposes.  



print_nl:
	movw	$0xe0d, %ax	# CR
	int	$0x10
	movb	$0xa, %al	# LF
	int 	$0x10
	ret
	



# This procedure turns off the floppy drive motor, ...

kill_motor:
    
##	sti
##	xorw	%ax, %ax	# reset FDC
##	xorb	%dl, %dl
##	int	$0x13	
##	cli

## the following stuff is better

	push	%dx
	push	%ax
	
	movw	$0x3F2, %dx
	xorb	%al, %al
	outb	%al, %dx
	
	pop	%ax
	pop	%dx	
	
	ret
	
	
gdt_48:
	.word	3*8		# gdt limit=24, 3 GDT entries
	.word	0,0		# lgdt base ?
	
gdt:
	.long	0,0		# zero entry (empty)
	.word	0xFFFF		# 4Gb - (0x100000*0x1000 = 4Gb)
	.word	0		# base address = 0
	.word	0x9A00		# code read/exec
	.word	0x00CF		# granularity = 4096, 386 (+5th nibble of limit)
	.word	0xFFFF		# 4Gb - (0x100000*0x1000 = 4Gb)
	.word	0		# base address = 0
	.word	0x9200		# data read/write
	.word	0x00CF		# granularity = 4096, 386 (+5th nibble of limit)


sectors:	.word 0
disksizes:	.byte 36, 18, 15, 9

		
# XXX: This is a fairly snug fit.

.org 507  
setup_sects:	.byte SETUPSECTS
syssize:	.word SYSSIZE
root_dev:	.word ROOT_DEV





