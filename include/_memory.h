#ifndef __MLEI_H_
#define __MLEI_H_

extern unsigned long _MemoryFileStorageStart;

void* malloc(unsigned long);
void* memset(void*, int, int);
void* memcpy(void*, const void*, int);
void* memzero(void *, int);

void free(void *);
int  memcmp( const void * cs, const void * ,unsigned int , unsigned int );

#endif /* __MLEI_H_ */ 


