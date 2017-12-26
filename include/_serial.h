#ifndef __SERIAL_H_
#define __SERIAL_H_

#define COM1	0x3F8 

unsigned char _SerialRecvChar(int);
void _SerialSendChar(int, unsigned char);
void _SerialWriteHexOfDepth(int, unsigned long, unsigned long);
void _SerialWriteNumDecimal(int, unsigned long);
void _SerialPuts(int, unsigned char * );

#endif /* __SERIAL_H_ */ 
