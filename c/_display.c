
/* a local visriable to point to videobuffer */
static char *vidmem;

/* a local visriable to keep address of videoport */
static int vidport;

/* local variables to keep displays height and width */
static unsigned char lines, cols;

/* local variables to keep cursor's vertical and horizontal positions */
static unsigned char pos_x, pos_y;


/* local function to scroll up visible stuff in case we run out of free space on screen */
static void scroll(void)
{
/* local counter */
int i;

	/* first, replace visible information in the videomemory */
	memcpy ( vidmem, vidmem + cols * 2, ( lines - 1 ) * cols * 2 );
	
	/* then fill released space ... */
	for ( i = ( lines - 1 ) * cols * 2; i < lines * cols * 2; i += 2 )
		/* with corresponding characters */
		vidmem[i] = ' ';
}

/* local function to put character into current position of cursor; performs scrolling if needed */
static void putc(unsigned char c)
{
/* local variables to process cursor position */
int x,y,pos;

	/* store x-position of cursor */
	x = pos_x;
	
	/* store y-position of cursor */
	y = pos_y;	


	/* if char to be displayed is NLC */
	if ( c == '\n' )
	{
	    /* move cursor to left border */
	    x = 0;

	    /* if y-position of cursor in pre-last line */
	    if ( ++y >= lines )
	    {
		/* do scroolling */		
		scroll();
		
		/* climb one line up */
		y--;
	    
	    }
	    
	}
	/* otherwise */
	else
	{
	    /* assign a character ont its right address in videomemory */
	    vidmem [ ( x + cols * y ) * 2 ] = c; 
	    
	    /* if x-position of cursor in last column */
	    if ( ++x >= cols )
	    {
		/* move cursor to left border */
		x = 0;
		
		/* if y-position of cursor in pre-last line */
		if ( ++y >= lines )
		{
		    /* do scroolling */		
		    scroll();
		    
		    /* go one line up */
		    y--;
		}
	    }
	}

	/* restore x-position of cursor */
	pos_x = x;
	
	/* restore y-position of cursor */	
	pos_y = y;

	/* update cursor position */
	pos = (x + cols * y) * 2;
	
	/* execute 'update cursor position' command sequence */
	*((volatile unsigned char*) vidport) = 14;
	
	/* execute its next command */
	*((volatile unsigned char*) (vidport+1)) = (0xff & (pos >> 9));
	
	/* execute its next command */
	*((volatile unsigned char*) vidport) = 15;
	
	/* execute its next command */
	*((volatile unsigned char*) (vidport+1)) = (0xff & (pos >> 1));
	

}


/* function to put string on display starting from current position of cursor; performs scrolling if needed */
void _DisplayPuts(const char *s)
{
/* local variables to process cursor position */
int x,y,pos;
/* temporary character variable to store string contents */
char c;

	/* store x-position of cursor */
	x = pos_x;
	
	/* store y-position of cursor */
	y = pos_y;


	/* for each character if string which is not EOL character */
	while ( ( c = *s++ ) != '\0' ) {

	    /* if char to be displayed is NLC */
	    if ( c == '\n' )
	    {
		/* move cursor to left border */
		x = 0;

		/* if y-position of cursor in pre-last line */
		if ( ++y >= lines )
		{
		    /* do scroolling */		
		    scroll();
		
		    /* climb one line up */
		    y--;
	    
		}	    
	    }
	    /* otherwise */
	    else
	    {
		/* assign a character ont its right address in videomemory */
		vidmem [ ( x + cols * y ) * 2 ] = c; 
	    
		/* if x-position of cursor in last column */
		if ( ++x >= cols )
		{
		    /* move cursor to left border */
		    x = 0;
		
		    /* if y-position of cursor in pre-last line */
		    if ( ++y >= lines )
		    {
			/* do scroolling */		
			scroll();
		    
			/* go one line up */
			y--;
		    }
		}
	    }
	}

	/* restore x-position of cursor */	
	pos_x = x;
	
	/* restore y-position of cursor */
	pos_y = y;

	/* update cursor position */
	pos = (x + cols * y) * 2;
	
	/* execute 'update cursor position' command sequence */	
	*((volatile unsigned char*) vidport) = 14;

	/* execute its next command */
	*((volatile unsigned char*) (vidport+1)) = (0xff & (pos >> 9));

	/* execute its next command */
	*((volatile unsigned char*) vidport) = 15;

	/* execute its next command */
	*((volatile unsigned char*) (vidport+1)) = (0xff & (pos >> 1));
	

}

/* function to put a string representing a hexadecimal number 'n' on a display */
void _DisplayWriteHexOfDepth(unsigned long n, unsigned long depth)
{
    /* if hexadecimal to be shown stil has 4-bit tetrade */
    if (depth)
    {
	/* recursively show everything but this 4-bit tetrade */
        _DisplayWriteHexOfDepth(n >> 4, depth-1);
	
	/* now take only this 4-bit tetrade and store its value in 'n' */
        n &= 0x0000000F;
	
	/* if the value needs to be represented as hexadecimal digit 0xA, .., 0xF */
	if (n > 9)
	
	    /* make corresponding char - 'A', ..., 'F' */
            n += 'A' - '0' - 10;
	    
	/* make corresponding char '0' - '9', otherwise */
        n += '0';

	/* and make this character visible in current cursor position on disblay */
	putc((unsigned char)  n );
    }
    
    /* done */
    return;
}

/* initialize VGA display to 80x25 mode */
void _Display80x25_Initialize(void)
{
	
	/* a textmode we initialize provides this amount of lines */
	lines = 25;
	
	/* a textmode we initialize provides this amount of columns */
	cols = 80;

	/* current x-position of cursor */
	pos_x = 0;
	
	/* current y-position of cursor */
	pos_y = 0;

/* a definition to toggle between different cases of videohardware */
#define ALTERNATE_TEXT_VMODE 0

	/* though sometimes we might need this, ... */
	if (ALTERNATE_TEXT_VMODE) {
		
		/* address of videomemory */
		vidmem = (char *) 0xb0000;
		
		/* address of videoport */
		vidport = 0x3b4;
	}
	/* most PC's fall into this cathegory */
	else {
		/* address of videomemory */
		vidmem = (char *) 0xb8000;
		
		/* address of videoport */
		vidport = 0x3d4;
	}

    /* done */
    return;
}

