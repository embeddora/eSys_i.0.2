
#include <_behoerde.h> 
#include <_handler.h>
#include <_null.h>
#include <_memory.h> 
#include <_serial.h>
#include <_odds+adds.h> 

/* creates Behoerde and initializes its initial element */
pBehoerde _CrBehoerde(unsigned long uloNewBehoerdeAddress, pBehoerde pbNewBehoerde)
{
	/* only one chain, for breginning */
	pbNewBehoerde = (pBehoerde) malloc ( sizeof (Behoerde) );

	/* check if successful */
	if (!pbNewBehoerde)
		/* NULL identifies "failure on creation" error */
		return  NULL;

	/* allocate a memory for name string */
	pbNewBehoerde->uchName = (unsigned char *) malloc (strlen("(start)"));
	
	/* assing this string a value */
	strcpy(pbNewBehoerde->uchName, "(start)");

	/* a lock-up  */
	pbNewBehoerde->next = NULL;
	
        /* write an address of newly created structure on right place */
	*(unsigned long*)(uloNewBehoerdeAddress) = (unsigned long)pbNewBehoerde;

	/* NULL identifies "failure on creation" error */
	return pbNewBehoerde;
}

/* registers an ditem '_NameOfItem' underf address '_AddressOfItem' */
void _AppendBehoerde(pBehoerde pbThisBehoerde, unsigned char * _NameOfItem, unsigned long _AddressOfItem)
{
/* introduce two temporary variables of type 'pBehoerde' */
pBehoerde pbChild, pbTempBehoerde;

	/* point with first temporary element to head of Behoerde */
	pbChild = pbThisBehoerde;

	/* allocate a space for new record in Behorde */
	pbTempBehoerde = (pBehoerde) malloc ( sizeof (Behoerde));

	/* Skip everything */
	while (NULL != pbChild->next )

		/* til the tail */
		pbChild = pbChild->next;
		
	/* if previous memory allocation was successful */
	if(pbTempBehoerde != NULL)
	{
		/* allocate a space needed for item's name */
		pbTempBehoerde->uchName = (unsigned char *) malloc (strlen(_NameOfItem));
		
		/* do copy item's name */
		strcpy(pbTempBehoerde->uchName, _NameOfItem);
		
		/* do register item's address  */
		pbTempBehoerde->uloAddress = _AddressOfItem;
		
		/* set a look-up */
		pbTempBehoerde->next = NULL;		

		/* append a new Behoerde entry to the end of existing Behoerde */
		pbChild->next = pbTempBehoerde;
	}
	else
		/* memory for new recored wasn't allocated */
		return; 
	
}

/* send information about all current Behoerdes entries through serial line */
void _PostBehoerdeContentsThroughSerial(pHandle phThisHandle, pBehoerde pbThisBehoerde)
{
/* a storage for number under which the item is registerd in Behoerde */
unsigned char _the_number;
    
    /* issue an explanatory line */
    _SerialPuts(0, "\nBehoerde's actual contents ['u' - unchained item, item's number otherwise]:");

	
    /* process each Behoerde's entry */
    while (pbThisBehoerde != NULL )
    {
	/* first, issue NLC */
	_SerialPuts(0, "\n");
    
	/* if an intem has a number then the item is 'chaind' ... */
	if (0 != (_the_number = _IsInHandle(phThisHandle, (unsigned long)pbThisBehoerde->uloAddress)  ))
	
	    /* so item's position in Behoerde is of interest */
	    _SerialWriteNumDecimal(0, _the_number-1);	    
	    
	/* otherwise item is 'unchained' */
	else	
	
	    /* and we merely report this fact (i.e. that item is unchained) */
	    _SerialSendChar(0, 'u' );
	    
	/* issue a wrapping TC */
	_SerialSendChar(0, '\t');

	/* issue an item's address */	
	_SerialWriteHexOfDepth(0, pbThisBehoerde->uloAddress, 8);

	/* issue a wrapping TC */
	_SerialSendChar(0, '\t');

	/* issue item's name */	
	_SerialPuts(0, (unsigned char *)(pbThisBehoerde->uchName));	
	
	/* Go to next record of Behoerde */
	pbThisBehoerde =  pbThisBehoerde->next;
    };	
    
    /* issue NLC to keep stuff issued smarter */
    _SerialPuts(0, "\n");
	
}


/* erase an entire Behoerde, useless but kept for symmetrisity with '_CrBehoerde()' */
void _DeleteBehoerde(pBehoerde pbThisBehoerde)
{
/* a tomparary variable of type 'pBehoerde' */
pBehoerde pbChild;

	/* Walk through entire list and delete each chain */
	while (NULL != pbThisBehoerde)
	{
		/* if space to keep item's name is allocated */
		if (pbThisBehoerde->uchName)
		
		    /* then release this space */
		    free(pbThisBehoerde->uchName);
		    
		/* preserve a pointer to next record */		    
		pbChild = pbThisBehoerde->next;
		
		/* free space occupied by current record */
		free (pbThisBehoerde);
		
		/* Go to next record */
		pbThisBehoerde = pbChild;
	}
	
	/* done */
	return; 
}
