#ifndef __INTR_H_
#define __INTR_H_

#define cli()	__asm__ __volatile__("cli": : :"memory")
#define sti()	__asm__ __volatile__("sti": : :"memory")

#define _ControllerConstant 18

extern volatile unsigned long _ControllerClicks; 
void _Controller8259A_Initialize(void);

#endif /* __INTR_H_ */ 
