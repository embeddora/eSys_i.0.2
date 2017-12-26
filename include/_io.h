#ifndef __IO_H_
#define __IO_H_

#undef inb
#undef outb
#undef inb_p
#undef outb_p

#define outb_p(b, addr) *((volatile unsigned char*)addr) = (unsigned char)(b)
#define inb(addr) 	*((volatile unsigned char*)addr)
#define outb(b, addr)	*((volatile unsigned char*)addr) = (unsigned char)(b)
#define inb(addr) 	*((volatile unsigned char*)addr)


#endif /* __IO_H_ */ 
