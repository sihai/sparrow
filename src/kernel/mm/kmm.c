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
 * kmm.c
 *
 *  Created on: Jan 22, 2014
 *      Author: sihai
 */

#include "kmm.h"

extern char end[]; // first address after kernel loaded from ELF file

static struct kmem kmem;

void free_range(void *vstart, void *vend);

void kinit1(void *vstart, void *vend) {
	init_spin_lock(&kmem.lock, "kmem");
	kmem.use_lock = 0;
	free_range(vstart, vend);
}

void kinit2(void *vstart, void *vend) {
	free_range(vstart, vend);
	kmem.use_lock = 1;
}

void free_range(void *vstart, void *vend) {
	char *p;
	p = (char*) PGROUNDUP((uint) vstart);
	for (; p + PGSIZE <= (char*) vend; p += PGSIZE)
		kfree(p);
}

//PAGEBREAK: 21
// Free the page of physical memory pointed at by v,
// which normally should have been returned by a
// call to kalloc().  (The exception is when
// initializing the allocator; see kinit above.)
void kfree(char *v) {
	struct run *r;

	if ((uint) v % PGSIZE || v < end || v2p(v) >= PHYSTOP)
		panic("kfree");

	// Fill with junk to catch dangling refs.
	memset(v, 1, PGSIZE);

	if (kmem.use_lock)
		acquire(&kmem.lock);
	r = (struct run*) v;
	r->next = kmem.freelist;
	kmem.freelist = r;
	if (kmem.use_lock)
		release(&kmem.lock);
}

// Allocate one 4096-byte page of physical memory.
// Returns a pointer that the kernel can use.
// Returns 0 if the memory cannot be allocated.
char*
kalloc(void) {
	struct run *r;

	if (kmem.use_lock)
		acquire(&kmem.lock);
	r = kmem.freelist;
	if (r)
		kmem.freelist = r->next;
	if (kmem.use_lock)
		release(&kmem.lock);
	return (char*) r;
}
