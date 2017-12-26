
typedef int (*functype1)(int);
typedef int (*functype2)(int);
typedef int (*functype3)(int, int);


int _fn_3 (void * par1, functype1 par2, functype2 par3, functype3 par4)
{

int i, j;

    /* set pixel's color to black */
    par3(0);


    /* for each vert. column */
    for (i = 0; i < 320; i++) 
    {
    
	/* for each hor. line */
	for (j = 0; j < 240; j++) 
		    
	    /* set pixel */
	    par4(i,j);	    

	    
    }
    	    
    /* done */
    return;
    
}

