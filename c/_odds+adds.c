
#include <_null.h>

/* of ANSI: calculate a length of a string */
int strlen(const char *str)
{
const char *p;
int res;

    p = str;
    res = 0;
    
    while(*p)
    {
        ++p;
	++res;
    }

    return res;
}

/* of ANSI: copy a string */
char *strcpy(char *dest, const char *source)
{
char *p;
char c;

    p = dest;

    do
    {
        c = *source++;
        *p++ = c;
	
    } while (c);

    return dest;
}

/* of ANSI: copy first '__n' bytes of array, ignoring terminating null byte */
char * strncpy(char * __dest, const char * __src, int __n)
{
int i;
char *d, *s;

	d = (char *)__dest;
	s = (char *)__src;

	for (i=0; i<__n; i++)
	    d[i] = s[i];
	
	return __dest;
}



/* of ANSI: converts 'depth'-long portion of a string 'numbstr' to unsigned long and return this unsigend long */
unsigned long atol(volatile unsigned char * numbstr, unsigned char depth)
{
unsigned long result;
unsigned char i; 

    result=0;
    i=0;

    while ( (++i) && ((i-1) < depth) )
    {
	if (( '9' >= numbstr[i-1] ) && ( '0' <= numbstr[i-1] ))
	    result = result*16 + numbstr[i-1] - '0';
	    
	if (( 'F' >= numbstr[i-1] ) && ( 'A' <= numbstr[i-1] ))
	    result = result*16 + numbstr[i-1] - 'A'+ 10;
	    
	if (( 'f' >= numbstr[i-1] ) && ( 'a' <= numbstr[i-1] ))
	    result = result*16 + numbstr[i-1] - 'a'+ 10;
    }
    
    return result;
    
}
