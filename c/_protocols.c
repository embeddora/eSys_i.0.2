
#include <_null.h>
#include <_true.h>
#include <_serial.h>
#include <_memory.h>
#include <_handler.h>
#include <_behoerde.h>
#include <_display.h>
#include <_protocols.h>
#include <_odds+adds.h>  
#include <_controller.h>

/* needed as long as patch (see end of file) is present here */
#include <_kernel.h>

/* long for time */
unsigned long start_time;

/* buffer for data */
unsigned char buff[BBUFSIZ];

/* crctab as calculated by initcrctab() */
unsigned short crctab[1<<B] = { 

    0x0000,  0x1021,  0x2042,  0x3063,  0x4084,  0x50a5,  0x60c6,  0x70e7,
    0x8108,  0x9129,  0xa14a,  0xb16b,  0xc18c,  0xd1ad,  0xe1ce,  0xf1ef,
    0x1231,  0x0210,  0x3273,  0x2252,  0x52b5,  0x4294,  0x72f7,  0x62d6,
    0x9339,  0x8318,  0xb37b,  0xa35a,  0xd3bd,  0xc39c,  0xf3ff,  0xe3de,
    0x2462,  0x3443,  0x0420,  0x1401,  0x64e6,  0x74c7,  0x44a4,  0x5485,
    0xa56a,  0xb54b,  0x8528,  0x9509,  0xe5ee,  0xf5cf,  0xc5ac,  0xd58d,
    0x3653,  0x2672,  0x1611,  0x0630,  0x76d7,  0x66f6,  0x5695,  0x46b4,
    0xb75b,  0xa77a,  0x9719,  0x8738,  0xf7df,  0xe7fe,  0xd79d,  0xc7bc,
    0x48c4,  0x58e5,  0x6886,  0x78a7,  0x0840,  0x1861,  0x2802,  0x3823,
    0xc9cc,  0xd9ed,  0xe98e,  0xf9af,  0x8948,  0x9969,  0xa90a,  0xb92b,
    0x5af5,  0x4ad4,  0x7ab7,  0x6a96,  0x1a71,  0x0a50,  0x3a33,  0x2a12,
    0xdbfd,  0xcbdc,  0xfbbf,  0xeb9e,  0x9b79,  0x8b58,  0xbb3b,  0xab1a,
    0x6ca6,  0x7c87,  0x4ce4,  0x5cc5,  0x2c22,  0x3c03,  0x0c60,  0x1c41,
    0xedae,  0xfd8f,  0xcdec,  0xddcd,  0xad2a,  0xbd0b,  0x8d68,  0x9d49,
    0x7e97,  0x6eb6,  0x5ed5,  0x4ef4,  0x3e13,  0x2e32,  0x1e51,  0x0e70,
    0xff9f,  0xefbe,  0xdfdd,  0xcffc,  0xbf1b,  0xaf3a,  0x9f59,  0x8f78,
    0x9188,  0x81a9,  0xb1ca,  0xa1eb,  0xd10c,  0xc12d,  0xf14e,  0xe16f,
    0x1080,  0x00a1,  0x30c2,  0x20e3,  0x5004,  0x4025,  0x7046,  0x6067,
    0x83b9,  0x9398,  0xa3fb,  0xb3da,  0xc33d,  0xd31c,  0xe37f,  0xf35e,
    0x02b1,  0x1290,  0x22f3,  0x32d2,  0x4235,  0x5214,  0x6277,  0x7256,
    0xb5ea,  0xa5cb,  0x95a8,  0x8589,  0xf56e,  0xe54f,  0xd52c,  0xc50d,
    0x34e2,  0x24c3,  0x14a0,  0x0481,  0x7466,  0x6447,  0x5424,  0x4405,
    0xa7db,  0xb7fa,  0x8799,  0x97b8,  0xe75f,  0xf77e,  0xc71d,  0xd73c,
    0x26d3,  0x36f2,  0x0691,  0x16b0,  0x6657,  0x7676,  0x4615,  0x5634,
    0xd94c,  0xc96d,  0xf90e,  0xe92f,  0x99c8,  0x89e9,  0xb98a,  0xa9ab,
    0x5844,  0x4865,  0x7806,  0x6827,  0x18c0,  0x08e1,  0x3882,  0x28a3,
    0xcb7d,  0xdb5c,  0xeb3f,  0xfb1e,  0x8bf9,  0x9bd8,  0xabbb,  0xbb9a,
    0x4a75,  0x5a54,  0x6a37,  0x7a16,  0x0af1,  0x1ad0,  0x2ab3,  0x3a92,
    0xfd2e,  0xed0f,  0xdd6c,  0xcd4d,  0xbdaa,  0xad8b,  0x9de8,  0x8dc9,
    0x7c26,  0x6c07,  0x5c64,  0x4c45,  0x3ca2,  0x2c83,  0x1ce0,  0x0cc1,
    0xef1f,  0xff3e,  0xcf5d,  0xdf7c,  0xaf9b,  0xbfba,  0x8fd9,  0x9ff8,
    0x6e17,  0x7e36,  0x4e55,  0x5e74,  0x2e93,  0x3eb2,  0x0ed1,  0x1ef0
    };



/* Left for future */ 
void prtime (unsigned long numsect, unsigned long seconds)
{ 
    return;
}


/* This is mixture of ANSI's 'read()' and Linux's 'select()'. And it seems to be raw. */
int draft_read(int port, char * storage, int maxamount, unsigned long timequote)
{
    int actual_amount;
    unsigned char ready;
    char chur;
    char * storagebuf = storage;
    
    /* initially we havent read anything */
    actual_amount = 0;
    
    /* */    
    do
    {
    	ready = 0;

__asm__ (
    "mov	$0x3F8, %%dx\n\t"
    "addw	$5, %%dx\n\t"
    "inb	%%dx, %%al\n\t"
    "test 	$0x01, %%al\n\t"
    "jz		4f\n\t"
    "movb	$55, %%ah\n\t"
    "movb	%%ah, %0\n\t"
    "sub	$5, %%dx\n\t"
    "in		%%dx, %%al\n\t"
    "movb	%%al, %1\n\t"
"4:\n\t":"=rm" (ready):"rm" (chur));

	
	if (ready)	
	{
	    *storagebuf++ = chur;		
	    actual_amount++;    
	    
	}
     } while (( ((_ControllerClicks - start_time) / _ControllerConstant ) < timequote) && (actual_amount < maxamount) );
    
    /* amount of chars read, or return-thing */
    return actual_amount;
}



int readbuf(int bufsize, int seconds, int tmode, int * checksum, int * bufctr)
{
	int readfd;		/* mask for select call */
	int numread;		/* number of chars read */
	int left;		/* number of chars left to read */
	int recfin = 0;		/* flag that EOF read */
	char inbuf[BBUFSIZ];	/* buffer for incoming packet */
	unsigned char c;	/* character being processed */
	unsigned short chksm;	/* working copy of checksum */
	int bfctr;		/* working copy of bufctr */
	int j;			/* loop index */

	start_time = _ControllerClicks;			    


	readfd = 1<<0;
	chksm = 0;
	bfctr = 0;

	for (left = bufsize; left > 0;) {

#if (0)
		/* read however many chars are waiting */
		if ((select(1, &readfd, (int *)0, (int *)0, &tmout)) == 0)
			return(TIMEOUT);

		numread = read(0, inbuf, left);
#else
		numread = draft_read(0, (char *)(&inbuf), left, seconds);

		if (!numread)
		    return (TIMEOUT);
		else
		    ;

#endif /* (0) */		

		left -= numread;		
		
		/* now process part of packet we just read */
		for (j =  0; j < numread; j++) 
			{  
				buff[bfctr] = c = inbuf[j] & 0xff;				

				if (CRCMODE)  /* CRC */
					chksm = (chksm<<B) ^ crctab[(chksm>>(W-B)) ^ c];

				else        /* checksum */
		       			chksm = ((chksm+c) & 0xff);

				/* binary mode */
				if (!tmode)
					{  
					bfctr++;
		       			continue;
		       			}

				/* text mode */
				buff[bfctr] &= 0x7f; /* nuke bit 8 */
				
				if (c == CR)       /* skip CR's */
				continue;
				if (c == CTRLZ)  /* CP/M EOF char */
					{  
					recfin = TRUE;
		       			continue;
		       			}
		       		if (!recfin)
					bfctr++;
		     	}	

#if (0)
		/* go to sleep to save uneeded system calls while kernel
		   is reading data from serial line; forget this when we
		   running at 9600 bps; also fudge constant from 10000 to
		   9000 to avoid sleeping too long
		*/
		if (ttyspeed < 9600)
			napms ( (left<SLEEPNUM ? left:SLEEPNUM) * 9000/ttyspeed);
#else
		/* hopefully, in future we going only to speed system up */
#endif /* (0) */
	}
	

	*checksum = chksm;
	*bufctr = bfctr;
	return(0);
}





/* returns:: <true, false> */
void _ProtocolsReceivefile(unsigned char * name)
{

    int fd,     /* file descriptor for created file */
    checksum,   /* packet checksum */
    firstchar,  /* first character of a packet */
    sectnum,    /* number of last received packet (modulo 128) */
    sectcurr,   /* second byte of packet--should be packet number (mod 128) */
    sectcomp,   /* third byte of packet--should be complement of sectcurr */
    tmode,      /* text mode if true, binary mode if false */
    errors,     /* running count of errors (reset when 1st packet starts */
    errorflag,  /* set true when packet (or first char of putative packet) is invalid */
    fatalerror, /* set within main "read-packet" Do-While when bad error found */
    inchecksum, /* incoming checksum or CRC */
    expsect,    /* expected number of sectors (YMODEM batch) */
    bufsize;    /* packet size (128 or 1024) */
    long recvsectcnt;   /* running sector count (128 byte sectors) */
    int bufctr; /* number of real chars in read packet */
    unsigned char *nameptr; /* ptr in filename for MODEM7 protocol */
    unsigned long start;   /* starting time of transfer */
    int openflag = FALSE;   /* is file open for writing? */

    unsigned long storage_size;
    unsigned char * storage_pointer;
    
    

    storage_pointer = (unsigned char *)_MemoryFileStorageStart;
    
    storage_size = 0;   
    
    clbNewTask = NULL;
    
    CRCMODE = TRUE;
    
    BATCH = FALSE;          /* don't know if really are in batch mode ! */
    fatalerror = FALSE;
    sectnum = errors = recvsectcnt = 0;
    bufsize = 128;

    tmode = (XMITTYPE == 't') ? TRUE : FALSE;

#if (0)
    sleep(1);       /* wait a second for other side to get ready */
#else
//    _DisplayPuts("we just have skipped sleep(1);\n");
#endif /* () */    


    if (CRCMODE)        /* start up transfer */
        _SerialSendChar(0, CRCCHR);
    else
        _SerialSendChar(0, NAK);


    do                  /* start of MAIN Do-While loop to read packets */
        {   
        errorflag = FALSE;
        do              /* start by reading first byte in packet */
            {
            firstchar = _SerialRecvCharInTime(0, 6);
            } 
            while ((firstchar != SOH) 
                && (firstchar != STX) 
                && (firstchar != EOT) 
                && (firstchar != ACK || recvsectcnt > 0) 
                && (firstchar != TIMEOUT) 
                && (firstchar != CAN));

        if (firstchar == EOT)           /* check for REAL EOT */
            {
            if (_SerialRecvCharInTime(0, 1) != TIMEOUT)
                {
                firstchar = TIMEOUT;
                errorflag = TRUE;
                _DisplayPuts ("EOT followed by characters; ignored\n");
                }
            }

        if (firstchar == TIMEOUT)       /* timeout? */
            {  
//            _DisplayPuts("Timeout on Sector _s\n"/*, sectdisp(recvsectcnt,bufsize,1)*/);
                errorflag = TRUE;
            }

        if (firstchar == CAN)           /* bailing out? */
            {
            if ((_SerialRecvCharInTime(0, 3) & 0x7f) == CAN)
                _DisplayPuts("Reception canceled at user's request\n");
            else
                {
                errorflag = TRUE;
                _DisplayPuts("Received single CAN character\n");
                }
            }

        if (firstchar == ACK)           /* MODEM7 batch? */
            {
            int i,c; 

            _DisplayPuts("MODEM7 Batch Protocol\n");
            nameptr = buff;
            checksum = 0;

            for (i=0; i<NAMSIZ; i++)
                {
                c = _SerialRecvCharInTime(0, 3);

                if (c == CAN)
                    {
                    if (_SerialRecvCharInTime(0, 3) == CAN)
                        _DisplayPuts("Program Canceled by User\n");
                    else
                        {
                        _DisplayPuts("Received single CAN character\n");
                        errorflag = TRUE;
                        break;
                        }
                    }

                if (c == EOT && i == 0)
                    {
                    _DisplayPuts("MODEM7 Batch Receive Complete\n");
#if (0)		    
                    return (FALSE);
#else
		    return;
#endif /* (0) */		    
                    }

                if (c == TIMEOUT)
                    {
                    _DisplayPuts("Timeout waiting for MODEM7 filename character\n");
                    errorflag = TRUE;
                    break;
                    }

                if (c == BAD_NAME)
                    {
                    _DisplayPuts("Error during MODEM7 filename transfer\n");
                    errorflag = TRUE;
                    break;
                    }

                *nameptr++ = c;
                checksum += c;
                _SerialSendChar(0, ACK);
                }

            if (!errorflag)
                {
                c = _SerialRecvCharInTime(0, 3);
                if (c == CTRLZ)     /* OK; end of string found */
                    {
                    _SerialSendChar(0, checksum + CTRLZ);
                    if (_SerialRecvCharInTime(0, 3) == ACK)     /* file name found! */
                        {
                        _DisplayPuts("MODEM7 file name OK\n");
                        *nameptr = '\000';
#if (0)			
                        name = cpm_unix(buff);
#else
			_DisplayPuts("we just skipped: name = cpm_uni..\n");
#endif /* (0) */			
                        BATCH = TRUE;
                        }
                    else
                        {
                        _DisplayPuts("Checksum _DisplayPuts in MODEM7 filename\n");
                        errorflag = TRUE;
                        }
                    }
                else
                    {
                    _DisplayPuts("Length _DisplayPuts in MODEM7 fielname\n");
                    errorflag = TRUE;
                    }
                }
            }
            

        if (firstchar == SOH || firstchar == STX)  /* start reading packet */
            {	    
            bufsize = (firstchar == SOH) ? 128 : 1024;

            if (recvsectcnt == 0)           /* 1st data packet, initialize */
                {
                if (bufsize == 1024)
                    _DisplayPuts("1K packet mode chosen\n");
#if (0)
                start = time((time_t *) 0);
#else
		start = _ControllerClicks / _ControllerConstant; 
#endif /* (0) */		
                errors = 0;
                }

	    sectcurr = _SerialRecvCharInTime(0, 3);
	    sectcomp = _SerialRecvCharInTime(0, 3);
		if ((sectcurr + sectcomp) == 0xff)  /* is packet number checksum correct? */
		    {  
			if (sectcurr == ((sectnum+1) & 0xff))   /* is packet number correct? */
			    {  

        		    /* Read, process and calculate checksum for a buffer of data */
			    if (readbuf(bufsize, 3, tmode, &checksum, &bufctr) != TIMEOUT) 
                                {

				/* verify checksum or CRC */
				if (CRCMODE) 
                                    {
				    checksum &= 0xffff;
				    inchecksum = _SerialRecvCharInTime(0, 3);  /* get 16-bit CRC */
				    inchecksum = (inchecksum<<8) | _SerialRecvCharInTime(0, 3);
				    }
                        
				else
				    inchecksum = _SerialRecvCharInTime(0, 3);  /* get simple 8-bit checksum */

 
				if ( checksum == checksum ) /* good checksum, hence good packet */

				    {  

				    errors = 0;
				    recvsectcnt += (bufsize == 128) ? 1 : 8;
				    sectnum = sectcurr; 

				    if (!openflag)      /* open output file if necessary */
					{
					openflag = TRUE;
#if (0)					
					if ((fd = creat(name, CREATMODE)) < 0)
#else
//_DisplayPuts("we just skipped: fd = creat(name,.\n");
					if (FALSE)
#endif /* (0) */					
					    {
					    _SerialSendChar(0, CAN);
					    _SerialSendChar(0, CAN);
					    _SerialSendChar(0, CAN);
					    _DisplayPuts("Can't create file for receive\n");
					    }
					}

#if (0)					
				    if (write(fd, (char *) buff, bufctr) < 0)
#else

//_DisplayPuts("we just skipped: write(fd, (c..., but we did better\n");

				    memcpy(storage_pointer, (char *)buff, bufctr);
				    storage_pointer = (void *)((unsigned long)storage_pointer + bufctr);
				    storage_size += bufctr;

    				    if (FALSE)	  
#endif /* (0) */									    
					_DisplayPuts("File Write Error\n");
				    else
				    
					_SerialSendChar(0, ACK);      /* ACK the received packet */
				    }

        			/* Start handling various errors and special conditions */
				else        /* bad checksum */
				    {  				    
_DisplayPuts("Checksum Error on Sector _s\n"/*, sectdisp(recvsectcnt,bufsize,1)*/);
//_DisplayWriteHexOfDepth(inchecksum, 8);
//_DisplayPuts(" ");
//_DisplayWriteHexOfDepth(checksum, 8);
//_DisplayPuts("\n");
				    errorflag = TRUE;
				    }
                                }

			    else    /* read timeout */
				{
//_DisplayPuts("Timeout while reading sector _s\n"/*,sectdisp(recvsectcnt,bufsize,1)*/);
				errorflag = TRUE;
				}
			    }

                        else        /* sector number is wrong OR Ymodem filename */
                            { 
			    if (sectcurr == 0 && recvsectcnt == 0)  /* Ymodem file-name packet */
				{
				_DisplayPuts("YMODEM Batch Protocol\n");

				/* Read and process a file-name packet */
				if (readbuf(bufsize, 3, FALSE, &checksum, &bufctr) != TIMEOUT) 
                                    {

				    /* verify checksum or CRC */

				    if (CRCMODE) 
                                        {
					checksum &= 0xffff;
					inchecksum = _SerialRecvCharInTime(0, 3);  /* get 16-bit CRC */
					inchecksum = (inchecksum<<8) | _SerialRecvCharInTime(0, 3);
				        }
                        
				    else
					inchecksum = _SerialRecvCharInTime(0, 3);  /* get simple 8-bit checksum */

				    if (inchecksum == checksum) /* good checksum, hence good filename */
					{
					strcpy(name, (char *)buff);
                                        expsect = ((buff[bufsize-1]<<8) | buff[bufsize-2]);
					_SerialSendChar(0, ACK);      /* ACK the packet */
					BATCH = TRUE;
					if (strlen(name) == 0)  /* check for no more files */
					    {
					    _DisplayPuts("YMODEM Batch Receive Complete\n");
#if (0)					    
					    return (FALSE);
#else
					    return;
#endif /* */					    
					    }
#if (0)					    
                                        unixify(name);       /* make filename canonical */
#else
//_DisplayPuts("we just skipped: unixify(nam...\n");
#endif /* (0) */					
					_DisplayPuts("YMODEM file name: _s\n"/*, name*/);
					_DisplayPuts("YMODEM estimated file length _d sectors\n"/*, expsect*/);
					_DisplayPuts("YMODEM header info: _s\n"/*, (char *)buff + strlen(name) + 1*/);
					}					

				    else                /* bad filename checksum */
					{
					_DisplayPuts("bad checksum _DisplayPuts on filename sector\n");
					errorflag = TRUE;
					}
				    }
				else
				    {
				    _DisplayPuts("Timeout while reading filename packet\n");
				    errorflag = TRUE;
                                    }
				}

			    else if (sectcurr == sectnum)   /* duplicate sector? */
				{  
				_DisplayPuts("Duplicate sector _s flushed\n"/*, sectdisp(recvsectcnt,bufsize,0)*/);
				while(_SerialRecvCharInTime(0, 3) != TIMEOUT)
				    ;
				_SerialSendChar(0, ACK);
				}
			    else                /* no, real phase _DisplayPuts */
				{
				_DisplayPuts("Phase Error - Expected packet is _s\n"/*, sectdisp(recvsectcnt,bufsize,1)*/);
				errorflag = TRUE;
				fatalerror = TRUE;
				_SerialSendChar(0, CAN);
				_SerialSendChar(0, CAN);
				_SerialSendChar(0, CAN);
				}
			    }
		    }

		else        /* bad packet number checksum */
		    {  
		    _DisplayPuts("Header Sector Number Error on Sector _s\n"/*, sectdisp(recvsectcnt, bufsize,1)*/);
		    errorflag = TRUE;
		    }

	    }           /* END reading packet loop */
    
	if ((errorflag && !fatalerror) || recvsectcnt == 0) /* check on errors or batch transfers */
	    {  
	    if (errorflag)
	        errors++;
	    if (recvsectcnt != 0)
		while (_SerialRecvCharInTime(0, 3) != TIMEOUT)  /* wait for line to settle if not beginning */
		    ;

	    if (CRCMODE && recvsectcnt == 0 && errors == CRCSWMAX)
		{
		CRCMODE = FALSE;
//_DisplayPuts("Sender not accepting CRC request, changing to checksum\n");
		_SerialSendChar(0, NAK);
		}
	    else if (!CRCMODE && recvsectcnt == 0 && errors == CRCSWMAX)
		{
		CRCMODE = TRUE;
//_DisplayPuts("Sender not accepting checksum request, changing to CRC\n");
		_SerialSendChar(0, CRCCHR);
		}
	    else if (CRCMODE && recvsectcnt == 0)
		_SerialSendChar(0, CRCCHR);
	    else
		_SerialSendChar(0, NAK);
	    }
	}
        while ((firstchar != EOT) && (errors < ERRORMAX) && !fatalerror);   /* end of MAIN Do-While */

	if ((firstchar == EOT) && (errors < ERRORMAX))  /* normal exit? */
	    {
#if (0)	    
	    close(fd);
#else
//	    _DisplayPuts("we just skipped: close(fd) \n");
#endif /* */	    
	    _SerialSendChar(0, ACK);
	    
_SerialPuts(0, "\nDone\n");
	    
	    uloNewTaskLen = storage_size;
	    
	    clbNewTask = (void *)_MemoryFileStorageStart;
	    
////////////////////////////////////////////// [patch!]

*(volatile unsigned long*)(clbNewTask + PAR0_OFFSET) =
    atol((volatile unsigned char*)(clbNewTask + PAR0_OFFSET), 8);

*(volatile unsigned long*)(clbNewTask + PAR1_OFFSET) =
    atol((volatile unsigned char*)(clbNewTask + PAR1_OFFSET), 8);

*(volatile unsigned long*)(clbNewTask + PAR2_OFFSET) =
    atol((volatile unsigned char*)(clbNewTask + PAR2_OFFSET), 8);
    
*(volatile unsigned long*)(clbNewTask + PAR3_OFFSET) =
    atol((volatile unsigned char*)(clbNewTask + PAR3_OFFSET), 8);

*(volatile unsigned long*)(clbNewTask + PAR4_OFFSET) =
    atol((volatile unsigned char*)(clbNewTask + PAR4_OFFSET), 8);

*(volatile unsigned long*)(clbNewTask + PAR5_OFFSET) =
    atol((volatile unsigned char*)(clbNewTask + PAR5_OFFSET), 8);

////////////////////////////////////////////// [/patch!]

#if (0)	    
	    prtime (recvsectcnt, time((time_t *) 0) - start);
#else	    
	    prtime (recvsectcnt, (_ControllerClicks - start) / _ControllerConstant );	    
#endif /* (0) */	    



#if (0)
	    if (BATCH)          /* send appropriate return code */
		return(TRUE);
	    else
		return(FALSE);	    
#endif /* (0) */	    
        
	    
	    }
	else                /* no, _DisplayPuts exit */
	    { 
	    if (recvsectcnt != 0)
		_SerialSendChar(0, CAN);
		_SerialSendChar(0, CAN);
		_SerialSendChar(0, CAN);
_SerialPuts(0, "\nABORTED -- Too Many Errors\n");
#if (0)		
		return (FALSE);				
#else

#endif /* (0) */		
	    }  

}




