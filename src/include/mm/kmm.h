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
 * kmm.h
 *
 * Physical memory allocator, intended to allocate memory for user processes, kernel stacks, page table pages,
 * and pipe buffers. Allocates 4096-byte pages.
 *
 *  Created on: Jan 22, 2014
 *      Author: sihai
 */

#ifndef _SPARROW_KMM_H_
#define _SPARROW_KMM_H_

#include "spin_lock.h"

//----------------------------------------------------------
//				data struct
//----------------------------------------------------------
struct run {
  struct run *next;
};

struct kmem {
  struct spin_lock lock;
  int use_lock;
  struct run *free_list;
};

//----------------------------------------------------------
//				exported functions
//----------------------------------------------------------

/**
 * \brief          	Initialization happens in two phases.
 * 					1. main() calls kinit1() while still using entrypgdir to place just the pages mapped by entrypgdir on free list.
 *					2. main() calls kinit2() with the rest of the physical pages after installing a full page table that maps them on all cores.
 *
 * \param vstart
 * \param vend
 *
 */
void kinit1(void *vstart, void *vend);

#endif /* _SPARROW_KMM_H_ */
