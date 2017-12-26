
typedef int (*functype1)(int);
typedef int (*functype2)(int);
typedef int (*functype3)(int, int);


int _fn_1 (void * par1, functype1 par2, functype2 par3, functype3 par4)

{

unsigned long uloVidBufPtr = 0, i;


    
    /* set pixel's coloe */
    par3( 3 *16);

    /* Emit diagonal rainbow to show we're allright */
    for (i = 10; i < 256; i++) 
    {	    
	    /* set pixel on diag. line */
	    par4((int)i,(int)0);
    }
    
    /* set pixel's coloe */
    par3( 3 *16 + 1);

    /* Emit hor. line  */
    for (i = 10; i < 256; i++) 
    {	    
	    /* set pixels of line */
	    par4((int)i,(int)10);
    }

    /* set pixel's coloe */
    par3( 3 *16 + 2);

    /* Emit hor. line  */
    for (i = 10; i < 256; i++) 
    {	    
	    /* set pixel on diag. line */
	    par4((int)i,(int)20);
    }
    
    /* set pixel's coloe */
    par3( 3 *16 + 3);

    /* Emit hor. line  */
    for (i = 10; i < 256; i++) 
    {	    
	    /* set pixel on diag. line */
	    par4((int)i,(int)30);
    }
    
    /* set pixel's coloe */
    par3( 3 *16 + 4);

    /* Emit hor. line  */
    for (i = 10; i < 256; i++) 
    {	    
	    /* set pixel on diag. line */
	    par4((int)i,(int)40);
    }
    
    /* set pixel's coloe */
    par3( 3 *16 + 5);

    /* Emit hor. line  */
    for (i = 10; i < 256; i++) 
    {	    
	    /* set pixel on diag. line */
	    par4((int)i,(int)50);
    }
    
    /* set pixel's coloe */
    par3( 3 *16 + 6);

    /* Emit hor. line  */    
    for (i = 10; i < 256; i++) 
    {	    
	    /* set pixel on diag. line */
	    par4((int)i,(int)60);
    }
    
    /* set pixel's coloe */
    par3( 3 *16 + 7);

    /* Emit hor. line  */
    for (i = 10; i < 256; i++) 
    {	    
	    /* set pixel on diag. line */
	    par4((int)i,(int)70);
    }


    return;
    
}

