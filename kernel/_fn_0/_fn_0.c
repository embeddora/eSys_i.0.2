
typedef int (*functype1)(int);
typedef int (*functype2)(int);
typedef int (*functype3)(int, int);


int _fn_0 (void * par1, functype1 par2, functype2 par3, functype3 par4)

{

unsigned long uloVidBufPtr = 0, i;


    /* here we're about to spoil those kernels larger than 63,5 Kb */
    while (uloVidBufPtr < 0x10000)
    {       
	/* blacken the screen */    
	*(volatile unsigned long*)(0xA0000 + uloVidBufPtr) = 0;
	/* next ulo */
	uloVidBufPtr += 4;	
    }

    /* Assign right value to library's internal variable __svgalib_graph_mem this value is vidfeo-buffer-start-address */
    *((volatile unsigned long*)par1) =  0xA0000;

    
    /* initialize 320x240x256, for details - to 'vga.h' */
    par2(6); 

    
    /* Emit diagonal rainbow to show we're allright */
    for (i = 0; i < 256; i++) 
    {	
	    /* set pixel's color */
	    par3((int)i);
	    
	    /* set pixel on diag. line */
	    par4((int)i,(int)i);
    }

    return;
    
}

