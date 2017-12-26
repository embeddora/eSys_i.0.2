

#include <_controller.h>
#include <_io.h>

/* controller will work with freq. 100 Hz */
#define HZ 100

/* a controller constant, underlying HZ */
#define CLOCK_TICK_RATE 1193180

/* a controller constant to define number if ticks per second */
#define LATCH  ((CLOCK_TICK_RATE + HZ/2) / HZ)	

/* a 16-bit array for masking purposes */
unsigned int cached_irq_mask = 0xffff;

/* macro to access preferred byte within word-wide array */
#define __byte(x,y) 	(((unsigned char *)&(y))[x])

/* maceto to first byte */
#define cached_21	(__byte(0,cached_irq_mask))

/* maceto to second byte */
#define cached_A1	(__byte(1,cached_irq_mask))

/* 32-bit wide variable to accumulate timer ticks */
volatile unsigned long _ControllerClicks;

/* interrupt descriptor table, she is in allocated and initalized in head.S */
extern struct desc_struct  * idt;


/* timer interrupt handler */
void timer_interrupt(void)
{

	/* block interupts */
	cli();

	/* confirm interrupt was processed */
	__asm__("movb	$0x20, %al\n\toutb	%al, $0x20\n\t");
	
	/* set interrupts */
	sti();

}

/* 4th (of those casceded) interrupt handler, should be COM1 normally */
void i4_interrupt(void)
{
	/* block interupts */
	cli();

	/* confirm interrupt was processed */
	__asm__("movb	$0x20, %al\n\toutb	%al, $0x20\n\t");
	
	/* set interrupts */
	sti();
}

/* 3rd (of those casceded) interrupt handler, should be COM2 normally  */
void i3_interrupt(void)
{
	/* block interupts */
	cli();

	/* confirm interrupt was processed */
	__asm__("movb	$0x20, %al\n\toutb	%al, $0x20\n\t");
	
	/* set interrupts */
	sti();
}

/* handler for timer, serials, and all cascaded interrupts; raw */
void bad_interrupt(void)
{

    /* block interupts */
    cli();
	
    /* incerease timer clicks counter */
    _ControllerClicks++;

    /* _DisplayPuts("."); - ATTENTION: if i unkomment it I receive recursively inserted interrupts, and 'raibow' in 81st char, consequently  */

    /* confirm interrupt was processed */
    __asm__("movb	$0x20, %al\n\t	outb	%al, $0x20\n\t");

    /* set interrupt */	
    sti();
}

/* do interrupt unmasking */
void unmask_in_cascaded_8259A(unsigned int irq)
{
	/* preparing a required mask */
	unsigned int mask = ~(1 << irq);

	/* preparing a right mask */
	cached_irq_mask &= mask;
	
	/* if the task about lower interrupt sources */
	if (irq & 8)
		/* do the work to lower sorces */
		outb(cached_A1,0xA1);
	/* otherwise */		
	else
		/* do the unmasking to upper interrupt sorces */
		outb(cached_21,0x21);

}


/* do interrupts masking */
void mask_all_of_8259A(int auto_eoi)
{

	/* mask upper cascade's souces */
	outb(0xff, 0x21);
	
	/* mask lower cascade's souces */
	outb(0xff, 0xA1);

	/* a command i.-controller's first controller: select first controller init */
	outb_p(0x11, 0x20);
	
	/* map IRQs 0-7 of first controller to IRQs 32-39 */
	outb_p(0x20 + 0, 0x21);
	
	/* first cascaded - master, second - slave */
	outb_p(0x04, 0x21);	

	/* master controller expects software to send EOI, no automatic issuing it */
	outb_p(0x01, 0x21);

	/* a command i.-controller's second controller: select second controller init */	
    	outb_p(0x11, 0xA0);
	
	/* map IRQs 0-7 of second controller to IRQs 40-47 */
	outb_p(0x20 + 8, 0xA1);
	
	/* second is a slave on master's interrupt line IRQ2 */
	outb_p(0x02, 0xA1);
	
	/* something about auto EOI and flat mode - they say this is to be investigated */
	outb_p(0x01, 0xA1);
				    
	/* restore interrupt mask for master controler */
	outb(cached_21, 0x21);
	
	/* restore interrupt mask for slave controler */
	outb(cached_A1, 0xA1);


}


/* initialize system cascededble interrupt controller 8259A */
void _Controller8259A_Initialize(void)
{

	/* dafaulting click Akku */
	_ControllerClicks = 0;
	
	/* make the both cascedes of controller totally humble */
	mask_all_of_8259A(0);

	/* Set the clock to HZ Hz, hopefully, we already have a valid now (0x34 i.e. binary, mode 2, LSB/MSB, ch 0) */
	outb(0x34,0x43);		
	
	/* settind LSB */
	outb(LATCH & 0xff , 0x40);
	
	/* setting MSB */
	outb(LATCH >> 8 , 0x40);
	
	/* unmask all sources plugges to second cascade by unmaskins second i.-line in first casce */
	unmask_in_cascaded_8259A(2);
	
	/* a handler of umasked above i.-source is 'bad_interrupt()' */
	*((volatile unsigned long*)(&idt + 8*0x02)) = (0x00080000 + (0x0000FFFF & (unsigned long)(&bad_interrupt)));

}


/* waiting for 'seconds_to_wait' seconds to pass */
void _ControllerWait(int seconds_to_wait)
{
/* storage for start time*/
unsigned long starttime;
	
    /* storing the start time */
    starttime = _ControllerClicks;    
    
    /* doing ... */
    do
    {	
	/* idle loop ... */
	;
	
    /* until timequote expires */	
    } while ( ((_ControllerClicks - starttime) / _ControllerConstant ) <= seconds_to_wait);

}
