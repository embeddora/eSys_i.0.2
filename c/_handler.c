

#include <_handler.h> 
#include <_null.h> 
#include <_true.h> 
#include <_memory.h>


/* normally this should incorporate steps to keep taskchain tide and healthy */ 
static void _AuditHandle(const unsigned char * _format, ... )
{
    /* these steps */;
    
    /* are not uimplemented, yet */;
}

/* creates a new Handle list - so called callbacklist - and intializes its first entry */
pHandle _CrHandle(unsigned long uloNewHandlerAddress, pHandle phNewHandle)
{
	/* allocate anough space for new handler */
	phNewHandle = (pHandle)malloc ( sizeof (Handle) );

	/* if not allocated */
	if (!phNewHandle)
	
		/* return NULL - "failure on creation" error */
		return phNewHandle;

	/* insert '_AuditHandle()' function into first chain of Callbacklist */
	phNewHandle->clbInstance = (CallbackType)_AuditHandle;

	/* first parameter to '_AuditHandle()' is NULL */
	phNewHandle->uplParameters[0] = (UPLT*)NULL;
	
	/* second parameter to '_AuditHandle()' is NULL */	
	phNewHandle->uplParameters[1] = (UPLT*)NULL;
	
	/* third parameter to '_AuditHandle()' is NULL */
	phNewHandle->uplParameters[2] = (UPLT*)NULL;
	
	/* fourth parameter to '_AuditHandle()' is NULL */
	phNewHandle->uplParameters[3] = (UPLT*)NULL;
	
	/* fifth parameter to '_AuditHandle()' is NULL */
	phNewHandle->uplParameters[4] = (UPLT*)NULL;
	
	/* sixth parameter to '_AuditHandle()' is NULL */
	phNewHandle->uplParameters[5] = (UPLT*)NULL;
                                      
	/* assign a lock-up  */
	phNewHandle->next = NULL;
	
        /* write an address of newly created record onto right place */
	*(unsigned long*)(uloNewHandlerAddress) = (unsigned long)phNewHandle;

	/* ~NULL identifies an absense of "failure on creation" error */
	return phNewHandle;
}


/* insets 'clbThisCallback' element into callbacklist ponted as 'phThisHandle'. Insert newcallback's parameters, too */
pHandle _AppendHandle (pHandle phThisHandle, CallbackType clbThisCallback, unsigned long uloCallbackLength, unsigned long uplTheseParameters0, unsigned long uplTheseParameters1, unsigned long uplTheseParameters2, unsigned long uplTheseParameters3, unsigned long uplTheseParameters4, unsigned long uplTheseParameters5)
{
/* introduce two temporary variables of type 'pHandle' */
pHandle phChild, phTempHandle;

	/* point with first temporary variable to head of callbackchain */
	phChild = phThisHandle;
	
	/* allocate a space for new callback-record */
	phTempHandle = (pHandle)malloc ( sizeof (Handle));	

	/* Skip everything */
	while (NULL != phChild->next )
	
		/* till the tail */
		phChild = phChild->next;
		
	/* if previous memory allocation was successful */
	if(phTempHandle != NULL)
	{
		/* allocate a space to store a callback being inserted into callbacklist */ 
		phTempHandle->clbInstance = (CallbackType) malloc (uloCallbackLength);
		
		/* if previous memory allocation was successful */		
		if (phTempHandle->clbInstance)
		{		
		    /* copy a callback being inserted into the spaceallocated step before */
		    memcpy((void *) phTempHandle->clbInstance, (void *) clbThisCallback, uloCallbackLength);
		
		    /* copy a first parameter to callback being inserted */
		    phTempHandle->uplParameters[0] =  (UPLT*)uplTheseParameters0;
		
		    /* copy a second parameter to callback being inserted */
		    phTempHandle->uplParameters[1] =  (UPLT*)uplTheseParameters1;
		
		    /* copy a third parameter to callback being inserted */
		    phTempHandle->uplParameters[2] =  (UPLT*)uplTheseParameters2;
		
		    /* copy a fourth parameter to callback being inserted */
		    phTempHandle->uplParameters[3] =  (UPLT*)uplTheseParameters3;
		
		    /* copy a fifth parameter to callback being inserted */
		    phTempHandle->uplParameters[4] =  (UPLT*)uplTheseParameters4;
		
		    /* copy a sixth parameter to callback being inserted */
		    phTempHandle->uplParameters[5] =  (UPLT*)uplTheseParameters5;
		
		    /* a look-up */
		    phTempHandle->next = NULL;

		    phChild->next = phTempHandle;
		
		    /* ~NULL identifies an absense of any error */
		    return phTempHandle;
		}		
	}
		
	/* either first, eeither seond time memory wasn't allocated */
	return NULL ; 
	
}


/* delete entire callbacklist, for nothing but symmetry with '_CrHandle()' */
void _DeleteHandle(pHandle phThis)
{
/* a temporary variable of type pHandle */
pHandle phChild;

	/* Walk through the entire list and delete each chain */
	while (NULL != phThis)
	{
		/* store a pointer to next chain into phChild */
		phChild = phThis->next;
		
		/* normally, memory resourse should be released */
		free (phThis);		
		
		/* make phChild an actual pointer */
		phThis = phChild;
	}
	
	/* done */
	return; 
}


/* execute all callbacks of entire callbacklist */
void _ExecuteHandle(pHandle _pHandleInstance)
{
	/* Skip first callback, which is '_AuditHandle()' */
	_pHandleInstance =  _pHandleInstance->next;

	/* Walk through the rest of list and ... */
	while (_pHandleInstance != NULL )
	{
		/* execute each callback with its parameters */
		_pHandleInstance->clbInstance(_pHandleInstance->uplParameters[0],_pHandleInstance->uplParameters[1],_pHandleInstance->uplParameters[2],_pHandleInstance->uplParameters[3],_pHandleInstance->uplParameters[4],_pHandleInstance->uplParameters[5]);

		/* Go to next callbackchain */
		_pHandleInstance =  _pHandleInstance->next;
	};
	
	/* done */
	return;
}

/* exclude from callbacklist a callbackrecord whose callbackaddress is equal to 'clbCallbackInstance' */
void _ExcludeChainFromHandle(pHandle phThisHandle, CallbackType clbCallbackInstance)
{
/* a temporary variable */
pHandle phChild;

	/* store and address of 'phThisHandle' in temporary variable */
	phChild = phThisHandle;

	/* is actual recors and next record are existing ... */
	while ( (phChild) && (phChild->next) )
	{
	    /* check if callback of next record is not exactly the thing to be deleted ... */
	    if ( clbCallbackInstance != (phChild->next)->clbInstance )

		/* if so then go to next record */	    
		phChild = phChild->next;
		
	    /* but in case callback of next record is exactly the thing to be deleted ... */
	    else
	    {
		/* release the space occupied by target to be deleted */
		free ( phChild->next );
	    
		/* throw the pointer over deleted target */
		phChild->next = (phChild->next)->next;
	    }
	}
	
	/* done */
	return;
}

/* check is callbackchain incorporates a callback addresed by 'uloAddress' if so then returns its position number, if not so then returns zero */
int _IsInHandle(pHandle phThisHandle, unsigned long uloAddress)
{
/* temporary variabl eto store return result */
int	counter = 0;

    	/* Walk through the entire list and explore */
	while (NULL != phThisHandle)
	{
		/* pre-increase tempvar */
		counter++;
	
		/* check if actual callback starts at 'uloAddress' */
		if ( uloAddress == (unsigned long)phThisHandle->clbInstance )
		
		    /* is so then return actual callback's position number */
		    return counter;
	
		/* otherwise go to next chain */
		phThisHandle = phThisHandle->next;
	};
	
	/* if we've came here then we haven't found any address coincedence, therewhy we return a zero which identifies an error */
	return false;
    
}
