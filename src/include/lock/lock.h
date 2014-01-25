/*
 *	------------------------------------------------------------------------------------------------
 *	-	########  ########		   #		 #########	 #########	    #########   #     	   #   -
 *	-  #		  #		  #   	  #	#   	 #		  #	 #		  #    #         #	#		   #   -
 *	-  #		  #		  #	 	 #	 #		 #		  #  #		  #    #	     #	#		   #   -
 *	-  #		  #		  #		#	  #		 #		  #  #		  #	   #		 #  #		   #   -
 *	-	########  ########	   #	   #	 #########	 #########     #		 #  #	  #	   #   -
 *	-		    # #			  ###########	 #	 #		 #   #         #		 #	#	 # #   #   -
 *	-			# #			 #		     #	 #	  #	   	 #    #		   #		 #	#   #   #  #   -
 *	-			# #			#			  #	 #     #	 #	   #	   #         #	#  #     # #   -
 *	-  #########  #		   #			   # #		#	 #		#       #########	 #		  #    -
 *  -                 																			   -
 *  ------------------------------------------------------------------------------------------------
 *
 * lock.h
 *
 *  Created on: Jan 22, 2014
 *      Author: sihai
 */

#ifndef _SPARROW_LOCK_H_
#define _SPARROW_LOCK_H_

//----------------------------------------------------------
//				exported functions
//----------------------------------------------------------

// pushcli/popcli are like cli/sti except that they are matched:
// it takes two popcli to undo two pushcli.  Also, if interrupts
// are off, then pushcli, popcli leaves them off.

inline void pushcli(void) {
	int eflags;

	eflags = readeflags();
	cli();
	if (cpu->ncli++ == 0)
		cpu->intena = eflags & FL_IF;
}

inline void popcli_spin(void) {
	if (readeflags() & FL_IF)
		panic("popcli - interruptible");
	if (--cpu->ncli < 0)
		panic("popcli");
	if (cpu->ncli == 0 && cpu->intena)
		sti();
}

#endif /* _SPARROW_LOCK_H_ */
