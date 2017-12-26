#ifndef __TEXTMODE_H_
#define __TEXTMODE_H_

void _DisplayPuts(const char *);
void _DisplayWriteHexOfDepth(unsigned long, unsigned long );
int  _Display80x25_Initialize(void);

#define  error(x) _DisplayPuts(x)

#endif /* __TEXTMODE_H_ */
