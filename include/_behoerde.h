#ifndef	__BEHOERDE_H_
#define	__BEHOERDE_H_

#include <_handler.h> 

/* Behoerde is a record composed of: */
typedef struct BehoerdeType {
	/* pointer to item's name */
	unsigned char *		uchName;
	/* an absolute address item is placed at */
        unsigned long		uloAddress;
	/* pointer to next record */
	struct BehoerdeType *	next;
/* record and pointer to record list types */	
} Behoerde, *pBehoerde;

void _AppendBehoerde(pBehoerde, unsigned char * , unsigned long);
void _PostBehoerdeContentsThroughSerial(pHandle, pBehoerde);
void _DisplayBehoerde(pHandle, pBehoerde);
void _DeleteBehoerde(pBehoerde);
pBehoerde _CrBehoerde(unsigned long, pBehoerde);
#define _CreateBehoerde(x) _CrBehoerde((unsigned long)&x, x)


#endif /* __BEHOERDE_H_ */
