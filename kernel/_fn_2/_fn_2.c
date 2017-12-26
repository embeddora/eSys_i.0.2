
typedef void (*functype0)(void *, void *);

void _fn_2 (functype0 UnchainCallbackFromTasklist,
	    void * par1,
	    void * addr_of_first_targ,
	    void * addr_of_second_targ,
	    void * addr_of_third_targ,
	    void * addr_of_fourth_targ)
{
/* temporary variable to store contents of reg. EAX */
volatile void * _actual_target;

    /* get *EAX into _actual_target: tested on Linux 2.4.20 (GCC 3.2.1), Linux 2.2.5 (and his GCC), and some others */
    __asm__ volatile ("movl %%eax, %0" : "=a" (_actual_target));	

    /* is both pointers - to callbackchain and function _UnchainCallbackFromTasklist() are not zeros */
    if (par1 && UnchainCallbackFromTasklist)
    {
	/* addr_of_first_targ - addr. of function to be unchained from taskchain, or NULL */
	if (addr_of_first_targ)
	    /* unchain function pointed by 'addr_of_first_targ' by means of function pointed by 'UnchainCallbackFromTasklist' */
	    UnchainCallbackFromTasklist ( (void*)par1 , (void*) addr_of_first_targ );

	/* addr_of_second_targ - addr. of function to be unchained from taskchain, or NULL */
	if (addr_of_second_targ)
	    /* unchain function pointed by 'addr_of_second_targ' by means of function pointed by 'UnchainCallbackFromTasklist' */
	    UnchainCallbackFromTasklist ( (void*)par1 , (void*) addr_of_second_targ );

	/* addr_of_third_targ - addr. of function to be unchained from taskchain, or NULL */
	if (addr_of_third_targ)
	    /* unchain function pointed by 'addr_of_third_targ' by means of function pointed by 'UnchainCallbackFromTasklist' */
	    UnchainCallbackFromTasklist ( (void*)par1 , (void*) addr_of_third_targ);
    
	/* addr_of_fourth_targ - addr. of function to be unchained from taskchain, or NULL */
	if (addr_of_fourth_targ)
	    /* unchain function pointed by 'addr_of_fourth_targ' by means of function pointed by 'UnchainCallbackFromTasklist' */
	    UnchainCallbackFromTasklist ( (void*)par1 , (void*) addr_of_fourth_targ );


        /* unchain function _fn_2() by means of function pointed by 'UnchainCallbackFromTasklist' */
	UnchainCallbackFromTasklist( (void*)par1 , (void *)_actual_target);

    }

    return;
}
