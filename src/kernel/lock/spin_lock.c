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
 * spin_lock.c
 *
 *  Created on: Jan 22, 2014
 *      Author: sihai
 */

#include "spin_lock.h"

void init_spin_lock(struct spin_lock *lk, char *name) {
	lk->name = name;
	lk->locked = 0;
	lk->cpu = 0;
}

void acquire_spin_lock(struct spin_lock *lk) {
	pushcli(); // disable interrupts to avoid deadlock.
	if (is_holding_spin_lock(lk))
		panic("try to acquire a hold spin lock");

	// The xchg is atomic.
	// It also serializes, so that reads after acquire are not
	// reordered before it.
	while (xchg(&lk->locked, 1) != 0)
		;

	// Record info about lock acquisition for debugging.
	lk->cpu = cpu;
	record_caller_pcs_spin_lock(&lk, lk->pcs);
}

// Release the lock.
void release_spin_lock(struct spin_lock *lk) {
	if (!is_holding_spin_lock(lk))
		panic("try to release a not hold spin lock");

	lk->pcs[0] = 0;
	lk->cpu = 0;

	// The xchg serializes, so that reads before release are
	// not reordered after it.  The 1996 PentiumPro manual (Volume 3,
	// 7.2) says reads can be carried out speculatively and in
	// any order, which implies we need to serialize here.
	// But the 2007 Intel 64 Architecture Memory Ordering White
	// Paper says that Intel 64 and IA-32 will not move a load
	// after a store. So lock->locked = 0 would work here.
	// The xchg being asm volatile ensures gcc emits it after
	// the above assignments (and after the critical section).
	xchg(&lk->locked, 0);

	popcli();
}

void record_caller_pcs_spin_lock(void *v, uint pcs[]) {
	uint *ebp;
	int i;

	ebp = (uint*) v - 2;
	for (i = 0; i < 10; i++) {
		if (ebp == 0 || ebp < (uint*) KERNEL_BASE || ebp == (uint*) 0xffffffff)
			break;
		pcs[i] = ebp[1];     // saved %eip
		ebp = (uint*) ebp[0]; // saved %ebp
	}
	for (; i < 10; i++)
		pcs[i] = 0;
}

int is_holding_spin_lock(struct spin_lock *lock) {
	return lock->locked && lock->cpu == cpu;
}
