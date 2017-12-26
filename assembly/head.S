



.text

	.globl up_32, idt , idt_descr  , ignore_int
	
up_32:

	cld	
	cli
	
	movl $0x10,%eax
	movl %eax,%ds
	movl %eax,%es
	movl %eax,%fs
	movl %eax,%gs

	lss stack_start,%esp	

	call setup_idt 

	
	xorl %eax,%eax
1:	incl %eax		# check that A20 really IS enabled
	movl %eax,0x000000	# loop forever if it isn't
	cmpl %eax,0x100000
 	je 1b       



/*
 * Initialize eflags.  Some BIOS's leave bits like NT set.  This would
 * confuse the debugger if this code is traced.
 * XXX - best to initialize before switching to protected mode.
 */
	pushl $0
	popfl
/*
 * Clear BSS
 */
/*
	xorl %eax,%eax
	movl $_bss_begin, %edi
	movl $_bss_aligned_end, %ecx
	subl %edi,%ecx
	cld
	rep
*/	
	stosb	


	xorl %ebx,%ebx	
	
	

	ljmp $8, $_rundschau_main
	

do_loop: 
	jmp do_loop 	
	


setup_idt:
	lea ignore_int,%edx
	movl $0x00080000,%eax
	movw %dx,%ax		/* selector = 0x0008 = cs */
	movw $0x8E00,%dx	/* interrupt gate - dpl=0, present */

	lea idt,%edi
	mov $256,%ecx
rp_sidt:
	movl %eax,(%edi)
	movl %edx,4(%edi)
	addl $8,%edi
	dec  %ecx
	jne  rp_sidt    	
	lidt idt_descr
	ret



## default interrupt handler from Him (I mean L. Torvalds)
ignore_int:
	incb 0xb8000+160		# put something on the screen
##	movb $0xC0,0xb8000+161		# so that we know something
	incb 0xb8000+161		# so that we know something
	movb $0x20,%al
	outb %al,$0x20			# EOI 

	iret				# happened





stack_start:	.long 0x200000  +8192
		.long 0x10 


.data


.align 32,0x90       
	.word 0			# 32-bit align idt_desc.address (Im not sure that aligned )
idt_descr:
	.word 256*8-1		# idt contains 256 entries
	.long idt

.align 32
idt:	.fill 256,8,0		# idt is uninitialized

	



