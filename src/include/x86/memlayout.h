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
 * memlayout.h
 *
 * memory layout of x86
 *
 *  Created on: Jan 18, 2014
 *      Author: sihai
 */

#ifndef _SPARROW_MEMLAYOUT_H_
#define _SPARROW_MEMLAYOUT_H_

#define EXT_MEMORY_START  	0x100000            	// Start of extended memory
#define PHYIC_MEMORY_STOP 	0xE000000           	// Top physical memory
#define DEVICE_SPACE 		0xFE000000         		// Other devices are at high addresses

// Key addresses for address space layout (see kmap in vm.c for layout)
#define KERNEL_BASE 0x80000000         				// First kernel virtual address
#define KERNEL_LINK (KERNEL_BASE + EXT_MEMORY)  	// Address where kernel is linked

#ifndef __ASSEMBLER__

static inline uint v2p(void *a) { return ((uint) (a))  - KERNEL_BASE; }
static inline void *p2v(uint a) { return (void *) ((a) + KERNEL_BASE); }

#endif

#define V2P(a) (((uint) (a)) - KERNEL_BASE)
#define P2V(a) (((void *) (a)) + KERNEL_BASE)

#define V2P_WO(x) ((x) - KERNEL_BASE)    // same as V2P, but without casts
#define P2V_WO(x) ((x) + KERNEL_BASE)    // same as V2P, but without casts

#endif /* _SPARROW_MEMLAYOUT_H_ */
