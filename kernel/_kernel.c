
#include <_vga.h>
#include <_null.h>
#include <_true.h>
#include <_serial.h>
#include <_memory.h>
#include <_handler.h>
#include <_display.h>
#include <_behoerde.h>
#include <_protocols.h>
#include <_controller.h>

/* pointer to callbacklist */
pHandle			phTasks;

/* pointer to list where system items (i.e. functions and globally-accessible variables) get registered */
pBehoerde		pbBehoerde;

/* place to where a new task gets stored after XMODEM download */
CallbackType		clbNewTask;

/* and a length of this task  */
unsigned long 		uloNewTaskLen;


/* local function to provide a simple interpreter across a serial line */
static void KernelBasicLoop(void)
{
/* temporary variable to store character received */
unsigned char uchChar;    
    
    /* do the loop endlessly */
    for ( ; ; )
    {
	/* get a character */
	uchChar = _SerialRecvChar(0);

	/* process a character either as regular, either as ESC-command */
	switch( uchChar )
	{
	    /* Escape char */
    	    case 0x1B:
	    
		/* Process escape sequence */
		{
		    do
		    {
		    	/* Get the rest of them ESCapes*/
			uchChar = _SerialRecvChar(0);			

		    } while (0x1B == uchChar);
		    
		    /* The following chars are our friends */
		    switch(uchChar)
		    {
			case 'R':
			    /* Perform file-receiving procedure */
			    {				
				_ProtocolsReceivefile(NULL);				    

				/* first receive a file*/
				if ( clbNewTask && ( strlen (  (  (unsigned char*)( (unsigned long)clbNewTask + CLBNAME_OFFSET )  )  )  <= CLBNAME_MAX_LEN  )  )
				{
				    /* file received - applzing it */
				    pHandle phNewlyAppended;				    
				    				    
				    /* install this task */
				    phNewlyAppended = _AppendHandle(phTasks, (CallbackType ) ((unsigned long)clbNewTask+ CLB_OFFSET),(unsigned long)(uloNewTaskLen - CLB_OFFSET),*(unsigned long*)((unsigned long)clbNewTask + PAR0_OFFSET),*(unsigned long*)((unsigned long)clbNewTask + PAR1_OFFSET),*(unsigned long*)((unsigned long)clbNewTask + PAR2_OFFSET),*(unsigned long*)((unsigned long)clbNewTask + PAR3_OFFSET),*(unsigned long*)((unsigned long)clbNewTask + PAR4_OFFSET),*(unsigned long*)((unsigned long)clbNewTask + PAR5_OFFSET)  );

				    if (NULL != phNewlyAppended)
				    {
					/* Register newly installed callback in Behoerde */	    
					_AppendBehoerde(pbBehoerde, (unsigned char*)clbNewTask, (unsigned long)(phNewlyAppended->clbInstance));
				    }
				    else
				    {					
					/* report an error */				
					_SerialPuts(0, "ERROR: attempt to append handler failed\n");
				    }
				}
				else 
				{
				    /* report an error */				
				    _SerialPuts(0, "ERROR: either wrong exec file, either transmittion error\n");
				}

			    }
			    break;
			
			case 'B':			
			    /* Output actual Behorede contents */			    
	        	    _PostBehoerdeContentsThroughSerial(phTasks, pbBehoerde);
			    break;
			    
			case 'E':			
			    /* execute task chain */
			    _ExecuteHandle(phTasks);
			    break;
			    
			default:
			
			    /* the command is unknown, can't perform it */
			    break;					    
		    }
		    		
		}
		break;	    
    
    	    default:
		/* Post it back */
	        _SerialSendChar(0, uchChar );
	}
    }
    
    /* normally, unreachable */
    return;
}


/* main(); launched from bootup stuff of 'head.S' */
int _rundschau_main (void)
{    
    /* Initialize PC's display to ouput messaqges by means: puts, WriteHexOfDepth, and others */
    _Display80x25_Initialize();

    /* Intialize */
    _Controller8259A_Initialize();

    /* Execute known assembly instruction */
    sti();    
    
    /* Create empty callback list */
    _CreateHandle(phTasks);    
    
    /* Create empty Behoerde */
    _CreateBehoerde(pbBehoerde);   
    
    /* Insert in Behoerde another member */
    _AppendBehoerde(pbBehoerde, "addr of __svgalib_graph_mem", (unsigned long)&__svgalib_graph_mem);    
    
    /* Insert in Behoerde another member */
    _AppendBehoerde(pbBehoerde, "addr of vga_setmode()", (unsigned long)&vga_setmode);
    
    /* Insert in Behoerde another member */
    _AppendBehoerde(pbBehoerde, "addr of vga_setcolor()", (unsigned long)&vga_setcolor);

    /* Insert in Behoerde another member */
    _AppendBehoerde(pbBehoerde, "addr of vga_drawpixel()", (unsigned long)&vga_drawpixel);    
    
    /* Insert in Behoerde another member */
    _AppendBehoerde(pbBehoerde, "addr of _UnchainCallbackFromCallbacklist()", (unsigned long)&_UnchainCallbackFromCallbacklist );
    
    /* Insert in Behoerde another member */
    _AppendBehoerde(pbBehoerde, "phTasks", (unsigned long)phTasks/* the thing is an address, already */);     

    /* Eternally do these few instructions */
    KernelBasicLoop();

    /* Give a useless error message */
    _SerialPuts(0, "ERROR: it's no good to see this line in terminal\n");

    /* Perform a useles exit to nowhere */
    return 0;
}

