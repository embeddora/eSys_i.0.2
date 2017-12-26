#ifndef __HANDLER_H_
#define __HANDLER_H_

/* Easiest we only can */
typedef volatile void UPLT;

/* callback takes 6 parameters (pointers to anything) and returns nothing */
typedef void (*CallbackType)(UPLT*, UPLT*, UPLT*, UPLT*, UPLT*, UPLT*);

/* Handle is a record composed of: */
typedef struct HandleType {
	/* pointer to function, i.e. callback */
	CallbackType 		clbInstance;
	/* set of pointers to its parameters */
	UPLT*			uplParameters[6];
	/* pointer to next record */
	struct HandleType *	next;
/* record and pointer to record list types */	
} Handle, *pHandle;

void _ExecuteHandle(pHandle);
void _DeleteHandle(pHandle);
void _ExcludeChainFromHandle(pHandle, CallbackType);
int  _IsInHandle(pHandle, unsigned long);
pHandle _CrHandle(unsigned long, pHandle);
pHandle _AppendHandle (pHandle, CallbackType,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long);
#define _UnchainCallbackFromCallbacklist	_ExcludeChainFromHandle 
#define _CreateHandle(x) 			_CrHandle((unsigned long)&x, x)

/* offset of code section in file received */ 
#define CLB_OFFSET  	0x48

/* offset of name section in file received */ 
#define	CLBNAME_OFFSET  0

/* length of parameter cell in file received */
#define	PARNUMB_MAX_LEN 0x8 

/* length of name section in file received */
#define CLBNAME_MAX_LEN 0x0F

/* offset of first parameter cell in file received */ 
#define PAR0_OFFSET	0x10

/* offset of second parameter cell in file received */ 
#define PAR1_OFFSET	PAR0_OFFSET + PARNUMB_MAX_LEN + 1

/* offset of third parameter cell in file received */ 
#define PAR2_OFFSET	PAR1_OFFSET + PARNUMB_MAX_LEN + 1

/* offset of fourth parameter cell in file received */ 
#define PAR3_OFFSET	PAR2_OFFSET + PARNUMB_MAX_LEN + 1

/* offset of fifth parameter cell in file received */ 
#define PAR4_OFFSET	PAR3_OFFSET + PARNUMB_MAX_LEN + 1

/* offset of sixth parameter cell in file received */ 
#define PAR5_OFFSET	PAR4_OFFSET + PARNUMB_MAX_LEN + 1

#endif /* __HANDLER_H_ */

