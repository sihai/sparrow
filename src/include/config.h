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
 * config.h
 *
 *  Created on: Jan 20, 2014
 *      Author: sihai
 */

#ifndef _SPARROW_CONFIG_H_
#define _SPARROW_CONFIG_H_

#define MAX_PROCESS        				64  	// maximum number of processes
#define KERNEL_STACK_SIZE 				4096  	// size of per-process kernel stack
#define MAX_CPU          				8  		// maximum number of CPUs
#define MAX_OPEN_FILES_PRE_PROCESS      16  	// open files per process
#define MAX_OPEN_FILES       			100  	// open files per system
#define MAX_BUFFERS         			10  	// size of disk block cache
#define MAX_ACTIVE_INODES       		50  	// maximum number of active i-nodes
#define MAX_DEVICE         				10  	// maximum major device number
#define ROOT_DEVICE       				0  		// device number of file system root disk
#define MAX_ARGS       					32  	// max exec arguments
#define MAX_LOG_SIZE      				10  	// max data sectors in on-disk log

#endif /* _SPARROW_CONFIG_H_ */
