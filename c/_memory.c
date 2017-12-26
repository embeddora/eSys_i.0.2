
#include <_memory.h>
#include <_null.h>
#include <_true.h>
#include <_display.h>

/*

Draft memory map:

90000 - 90200  - RESET SECTION
90200 - 9FFFF  - First 63,5 kB of Kernel
A0000 - AFFFF  - Videobuffer ( or next 64 kB of Kernel)
. . . . . I believe that upper limit of kernel size is 639,5 kB
100000 - 200000 - first slice of free memory
200000 - 202000 - stack
202000 - 300000 - I don't know what (some free memory but I don't like bordering with stack)
300000 - 800000 - second slice of free memory

*/

/* first byte of heap starts here */
static unsigned long free_mem_ptr = 0x00300000;

/* eight megabytes - everyone is presumed to have them */
static unsigned long free_mem_end_ptr = 0x00800000;

/* this pointer to unused area we need unless we implement some reliadble memoryfilesystem and conjunct it with modem comport-download-routine (see 'protocols.c') */
unsigned long _MemoryFileStorageStart = 0x00203000;

/* of ANSI: allocate 'size' of bytes in memory and return a pointer to there */
void *malloc(unsigned long size)
{
/* temporary storage for free memory pointer */
void *p;

	/* if size requested is wrong ... */
	if ( 0 > size )
	{	
	    /* report an error */
	    error("Malloc error\n");
	    
	    /* return with nothing */
	    return NULL;

	}
	    
	/* if free memory pointer is wrong ... */	
	if ( 0 >= free_mem_ptr )
	{	
	    /* report error */
	    error("Memory error\n");
	    
	    /* return with nothing */
	    return NULL;
	}

	/* make free memory address unsigned-long-aligned */
	free_mem_ptr = (free_mem_ptr + 3) & ~3;

	/* store free memory address in temporary storage */
	p = (void *)free_mem_ptr;
	
	/* allocate th memory - decrease the heap - move the pointer up */
	free_mem_ptr += size;

	/* if pointer to memnory allocated exceeds the border ... */
	if (free_mem_ptr >= free_mem_end_ptr)
	{	
		/* report an error */
		error("\nOut of memory\n");

		/* return with nothing */
		return NULL;

	}
				
	/* otherwise return the pointer to memory allocated */
	return p;
}

/* of ANSI: free memory area pointerd by 'where' */
void free(void *where)
{

    /* not uimplemented, yet */;
	
}

/* of ANSI: fill memory with a constant byte */
void* memset(void* s, int c, int n)
{
int i;
char *ss;

	ss = (char*)s;

	for (i=0; i<n; i++)
	    ss[i] = c;
	    
	return s;
}

/* of ANSI: copy memory area */
void* memcpy(void* __dest, const void* __src, int __n)
{
int i;
char *d, *s;

	d = (char *)__dest;
	s = (char *)__src;
	
	for (i=0; i<__n; i++)
	    d[i] = s[i];
	    
	return __dest;
}

/* of ANSI: compare memory areas */
int memcmp( const void * cs, const void * ct, /*size_t*/ unsigned int count0, /*size_t*/ unsigned int count1)
{
const unsigned char *su1, *su2;
signed char res;

	res = 0;	

	if ( count0 != count1 )	  
	    return 1;
	    
	for( su1 = cs, su2 = ct; 0 < count1; ++su1, ++su2, count1-- )
	    if ((res = *su1 - *su2) != 0)
		break;

	return res;
}

/* fill memory with a constant byte '0' */
#define memzero(s, n)     memset ((s), 0, (n))

