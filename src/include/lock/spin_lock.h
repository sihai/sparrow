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
 * spin_lock.h
 *
 *	Mutual exclusion lock.
 *
 *  Created on: Jan 21, 2014
 *      Author: sihai
 */

#ifndef _SPARROW_SPIN_LOCK_H_
#define _SPARROW_SPIN_LOCK_H_

#include "lock.h"

//----------------------------------------------------------
//				data struct
//----------------------------------------------------------
struct spin_lock {
  uint locked;       // Is the lock held?

  // For debugging:
  char *name;        // Name of lock.
  struct cpu *cpu;   // The cpu holding the lock.
  uint pcs[10];      // The call stack (an array of program counters)
                     // that locked the lock.
};

//----------------------------------------------------------
//				exported functions
//----------------------------------------------------------

/**
 * \brief          	init spin lock, init state is unlocked
 *
 * \param lk      	address of a spin lock
 * \param name		name for this spin lock
 *
 */
void init_spin_lock(struct spin_lock *lk, char *name);

/**
 * \brief          	acquire a spin lock, Loops (spins) until the lock is acquired.
 * 					Holding a lock for a long time may cause, other CPUs to waste time spinning to acquire it.
 *
 * \param lk      	address of a spin lock
 *
 */
void acquire_spin_lock(struct spin_lock *lk);

/**
 * \brief          	release a spin lock
 *
 * \param lk      	address of a spin lock
 *
 */
void release_spin_lock(struct spin_lock *lk);

/**
 * \brief          	Record the current call stack in pcs[] by following the %ebp chain.
 *
 * \param v
 * \param pcs
 */
void record_caller_pcs_spin_lock(void *v, uint pcs[]);

/**
 * \brief          	Check whether this cpu is holding the lock.
 *
 * \param lk
 * \return			0 - not, 1 - yes
 */
int is_holding_spin_lock(struct spin_lock *lk);

#endif /* _SPARROW_SPIN_LOCK_H_ */
