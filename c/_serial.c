
#include "_controller.h"
#include "_protocols.h"


/* send singel character 'tschar' to serial port 'port' */
void _SerialSendChar(int port, unsigned char tschar)
{
/* temporary (useless, yet) variable to store address of port */
int srport = port;

    /* the following stuff does: static __inline__ void port_outw(int value, int port) {    __asm__ volatile ("outw %0,%1"	     ::"a" ((unsigned short) value), "d"((unsigned short) port)); } */
    __asm__(
    "mov	$0x3F8, %%dx\n\t"
    "addw	$5, %%dx\n"
"0:\n\t"
    "inb	%%dx, %%al\n\t"
    "test 	$0x40, %%al\n\t"
    "jz		0b\n\t"
    "sub	$5, %%dx\n\t"
    "mov	%0, %%al\n\t"
    "out	%%al, %%dx\n\t"
    ::"rm" (tschar));
    
    /* done */
    return;
    
}

/* wait for character on serial port 'port' to appear, get this character, and return this character */
unsigned char _SerialRecvChar(int port)
{
/* temporary (useless, yet) variable to store address of port */
int srport = port;
/* local variable to store and return character received */
unsigned char tschar;

    /* the following stuff does: static __inline__ int port_inw(int port){  unsigned short value; __asm__ volatile ("inw %1,%0" :"=a" (value) :"d"((unsigned short) port));   return value; } */
    __asm__ (
    "mov	$0x3F8, %%dx\n\t"
    "addw	$5, %%dx\n"
"2:\n\t"
    "inb	%%dx, %%al\n\t"
    "test 	$0x01, %%al\n\t"
    "jz		2b\n\t"
    "sub	$5, %%dx\n\t"
    "in		%%dx, %%al\t\n"
    "movb	%%al, %0\t\n":"=rm" (tschar):);

    /* return received character */
    return tschar;       
}


/* wait not more than 'seconds_quote' seconds for character to appear on serial port 'port'; once characted appeared then return it in low byte of integer; return integer value of TIMEOUT otherwise */
int _SerialRecvCharInTime(int port, int seconds_quote)
{
/**/
unsigned long starttime;
unsigned char chur, ready;
	
    /* fix the start time */
    starttime = _ControllerClicks;
    
    do
    {	
	ready = 0;	

__asm__ (
    "mov	$0x3F8, %%dx\n\t"
    "addw	$5, %%dx\n\t"
    "inb	%%dx, %%al\n\t"
    "test 	$0x01, %%al\n\t"
    "jz		3f\n\t"
    "movb	$55, %%ah\t\n"
    "movb	%%ah, %0\t\n"
    "sub	$5, %%dx\n\t"
    "in		%%dx, %%al\t\n"
    "movb	%%al, %1\t\n"
"3:\n\t"    :"=rm" (ready):"rm" (chur));

	/* once character has came ... */
	if (ready)	
	{    
	    /* break the loop, and return the character in lower byte of integer */
	    return (0xFF & chur);
	}
    
    /* otherwise do the loop until time expires */
    } while ( ((_ControllerClicks - starttime) / _ControllerConstant ) <= seconds_quote);


    /* if during given time no characted has came then return a TIMEOUT */
    return (TIMEOUT);

}


/* write string representing a hexadecimal number 'n' into serial port 'port' */ 
void _SerialWriteHexOfDepth(int port, unsigned long n, unsigned long depth)
{
    /* if hexadecimal to be emitted stil has 4-bit tetrade */
    if (depth)
    {
	/* recursively emit everything but this 4-bit tetrade */
        _SerialWriteHexOfDepth(0, n >> 4, depth-1);

	/* now take only this 4-bit tetrade and store its value in 'n' */
        n &= 0x0000000F;
	
	/* if the value needs to be represented as hexadecimal digit 0xA, .., 0xF */
        if (n > 9)
	    /* make corresponding char - 'A', ..., 'F' */
            n += 'A' - '0' - 10;
	/* make corresponding char '0' - '9', otherwise */
        n += '0';
	
	/* and put this char into serial port 'port' */
	_SerialSendChar(port, (unsigned char)n );
    }
}


/* write string representing an adecimal number 'n' into serial port 'port' */
void _SerialWriteNumDecimal(int port, unsigned long n)
{
    /* if decimal to be emitted stil not representable by single lowest digit */ 
    if (n > 9)
    {
	/* then recursively emit everything but its lowest digit */	
        _SerialWriteNumDecimal(port, n / 10);
	
	/* now take only this lowest digit */
        n %= 10;
    }
    
    /* make char of this digit, and put this char into serial port 'port' */
    _SerialSendChar(port, (unsigned char)(n + '0') );   

}

/* write string pointed by str2put into serial port 'port' */
void _SerialPuts(int port, unsigned char * str2put)
{
/* temporary variable to store strings's contents */
char c;

	while ( ( c = *str2put++ ) != '\0' )
	
	    /* if NLC character is to be emitted */
	    if ( c == '\n' )
	    {
	    	/* emit newline character into serial port 'port' */
		_SerialSendChar(port, 13 );
		
		/* emit cariagereturn character into serial port 'port' */
		_SerialSendChar(port, 10 );	    
		
	    }
	    /* otherwise */
	    else	
		/* simply emit current character */
		_SerialSendChar(port, c );

}
