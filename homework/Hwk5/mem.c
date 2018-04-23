#include <stdio.h>    /* for printf statements when debugging */
#include <stdlib.h>   /* for malloc() and free() */
#include "mem.h"

/*
  Physical memory array. This is a static global array for all
  functions in this file.  An element in the array with a value of
  zero represents a free unit of memory.
*/
static dur_t* memory;

/*
 The size (i.e. number of units) of the physical memory array. This is
 a static global variable used by functions in this file.
 */
static int mem_size;


/*
 The last_placement_position variable contains the end position of the
 last allocated unit used by the next fit placement algorithm.
 */
static int last_placement_position;

/*
  Using the memory placement algorithm, strategy, allocate size
  units of memory that will reside in memory for duration time units.

  If successful, this function returns the number of contiguous blocks
  (a block is a contiguous "chuck" of units) of free memory probed while 
  searching for a suitable block of memory according to the placement 
  strategy specified.  If unsuccessful, return -1.

  If a suitable contiguous block of memory is found, the first size
  units of this block must be set to the value, duration.
 */
int mem_allocate(mem_strats_t strategy, int size, dur_t duration)
{
  if(strategy == 0){
    //Bestfit -----------------------------------------------------------------------------------------------------------------------------------------------
    int probe_count = 0;
    int current_bf_place = -1;
    int current_bf_size = -1;
    int count = -1;
    dur_t previous = *memory;

    //find bestfit and count probes
    //goodluck debugging, you did this to yourself
    //IK, its not that bad, debugging done
    for(int i = 0; i < sizeof(dur_t)*mem_size; i+=sizeof(dur_t)){
      if(*(memory+i) == previous){
        count++;
      }
      else{
        count++;
        //if open memory
        if(previous == 0){
          probe_count++;
          if(count >= size){
            if(current_bf_size == -1){
              current_bf_place = (i-count);
              current_bf_size = count;
            }
            else{
              if(count < current_bf_size){
               current_bf_place = (i-count);
               current_bf_size = count;
              }
            }
          }
        }
        count = 0;
      }
      previous = *(memory+i);
    }

    count++;
    if(*(memory+sizeof(dur_t)*mem_size-1) == 0){
      probe_count++;
      if(count >= size){
        if(current_bf_size == -1){
          current_bf_place = ((sizeof(dur_t)*mem_size-1+1)-count);
          current_bf_size = count;
        }
        else{
          if(count < current_bf_size){
            current_bf_place = ((sizeof(dur_t)*mem_size-1+1)-count);
            current_bf_size = count;
          }
        }
      }
    }

    //output
    if(current_bf_place == -1){
      //if allocation was unsuccessful
      return -1;
    }
    else{
      //allocate the memory
      for(int i = current_bf_place; i < current_bf_place+size; i+=sizeof(dur_t)){
        *(memory+i) = duration;
      }
      //return probe count
      return probe_count;
    }
  }

  else if(strategy == 1){
    //Firstfit -------------------------------------------------------------------------------------------------------------------------------
    int probe_count = 0;
    int count = -1;
    dur_t previous = *memory;
    //goodluck again
    //i think its still good, gj - cleaned it up a bit tho
    for(int i = 0; i < sizeof(dur_t)*mem_size; i+=sizeof(dur_t)){
      if(*(memory+i) == previous){
        count++;
      }
      else{
        count++;
        //if open memory
        if(previous == 0){
          probe_count++;
          if(count >= size){
            //allocate memory
            for(int j = (i-count); j < (i-count)+size; j+=sizeof(dur_t)){
              *(memory+j) = duration;
            }
            //return pc
            return probe_count;
          }
        }
        count=0;
      }
      previous = *(memory+i);
    }
    count++;
    if(*(memory+sizeof(dur_t)*mem_size-1) == 0){
      probe_count++;
      if(count >= size){
        //allocate memory
        for(int i = (sizeof(dur_t)*mem_size-count); i < (sizeof(dur_t)*mem_size-count)+size; i+=sizeof(dur_t)){
          *(memory+i) = duration;
        }
        //return pc
        return probe_count;
      }
    }
    //if did not end with any fit
    return -1;


  }else if(strategy == 2){
    //Nextfit ----------------------------------------------------------------------------------------------------------------------------------------
    int probe_count = 0;
    int count = -1;
    dur_t previous = *(memory+last_placement_position);
    //and a third time, GOOD LUCK
    //YUP
    for(int i = last_placement_position; i < sizeof(dur_t)*mem_size; i+=sizeof(dur_t)){
      if(*(memory+i) == previous){
        count++;
      }
      else{
        count++;
        //if open memory
        if(previous == 0){
          probe_count++;
          if(count >= size){
            //allocate memory
            for(int j = (i-count); j < (i-count)+size; j+=sizeof(dur_t)){
              *(memory+j) = duration;
            }
            //return pc
            last_placement_position = (i-count)+size;
            return probe_count;
          }
        }  

        count = 0;
      }
      previous = *(memory+i);
    }
    count++;
    if(*(memory+sizeof(dur_t)*mem_size-1) == 0){
      probe_count++;
      if(count >= size){
        //allocate memory
        for(int i = (sizeof(dur_t)*mem_size-count); i < (sizeof(dur_t)*mem_size-count)+size; i+=sizeof(dur_t)){
          *(memory+i) = duration;
        }
        //return pc
        last_placement_position = (sizeof(dur_t)*mem_size-count)+size;
        return probe_count;
      }
    }

    //loop around front front if no free space found
    //exacly like first fit after this point
    count = -1;
    previous = *memory;
    for(int i = 0; i < sizeof(dur_t)*mem_size; i+=sizeof(dur_t)){
      if(*(memory+i) == previous){
        count++;
      }
      else{
        count++;
        //if open memory
        if(previous == 0){
          probe_count++;
          if(count >= size){
            //allocate memory
            for(int j = (i-count); j < (i-count)+size; j+=sizeof(dur_t)){
              *(memory+j) = duration;
            }
            //return pc
            last_placement_position = (i-count)+size;
            return probe_count;
          }
        }
        count=0;
      }
      previous = *(memory+i);
    }
    count++;
    if(*(memory+sizeof(dur_t)*mem_size-1) == 0){
      probe_count++;
      if(count >= size){
        //allocate memory
        for(int i = (sizeof(dur_t)*mem_size-count); i < (sizeof(dur_t)*mem_size-count)+size; i+=sizeof(dur_t)){
          *(memory+i) = duration;
        }
        //return pc
        last_placement_position = (last_placement_position-count)+size;
        return probe_count;
      }
    }



    //if did not end with any fit
    //could get messy if it gets stuck in the middle if all is clear
    //might lead to larger probe later needs testing
    //last_placement_position = 0;
    return -1;
  }

  // if for some reason none of the correct enums were called
  //should not get here
  printf("THIS SHOULD NOT BE HAPPENING, ERRORs\n");
  return 0;
}

/*
  Go through all of memory and decrement all positive-valued entries.
  This simulates one unit of time having transpired.  NOTE: when a
  memory cell is decremented to zero, it becomes "unallocated".
 */
int mem_single_time_unit_transpired()
{
  //loop through array and decrement any value > 0
  for(int i = 0; i < sizeof(dur_t)*mem_size; i+=sizeof(dur_t)){
    if(*(memory+i) > 0)
      *(memory+i) -= 1;
  }
  //why is this an int and not a void? whatever, I'm not allowed to change it.
  return 0;
}

/*
  Return the number of fragments in memory.  A fragment is a
  contiguous free block of memory of size less than or equal to
  frag_size.
 */
int mem_fragment_count(int frag_size)
{
  //use my print function which finds sections and increment when count <= fragment size
  int frag_count = 0;
  int count = -1;
  dur_t previous = *memory;

  for(int i = 0; i < sizeof(dur_t)*mem_size; i+=sizeof(dur_t)){
    if(*(memory+i) == previous){
      count++;
    }
    else{
      count++;
      if((previous == 0) && (count <= frag_size)){
        frag_count++;
      }
      count = 0;
    }
    previous = *(memory+i);
  }
  count++;
  if((*(memory+sizeof(dur_t)*mem_size-1) == 0) && (count <= frag_size))
    frag_count++;

  return frag_count;
}

/*
  Set the value of zero to all entries of memory.
 */
void mem_clear()
{
  //loop through array and make every entry value 0
  for(int i = 0; i < sizeof(dur_t)*mem_size; i+=sizeof(dur_t)){
    *(memory+i) = 0;
  }
}

/*
 Allocate physical memory to size. This function should 
 only be called once near the beginning of your main function.
 */
void mem_init(int size)
{
  memory = malloc(sizeof(dur_t)*size);
  mem_size = size;
}

/*
 Deallocate physical memory. This function should 
 only be called once near the end of your main function.
 */
void mem_free()
{
  free(memory);
}

/*
  Print memory for testing/debugging purposes.  This is an optional
  routine to write, but highly recommended!  You will need to test and
  debug your allocation algorithms.  Calling this routine in your
  main() after every allocation (successful or not) will help in this
  endeavor.  NOTE: you should print the memory contents in contiguous
  blocks, rather than single units; otherwise, the output will be very
  long.
 */
void mem_print()
{ 
  //breaks up the print into sections so it is readable
  int count = -1;
  dur_t previous = *memory;
  for(int i = 0; i < sizeof(dur_t)*mem_size; i+=sizeof(dur_t)){
    if(*(memory+i) == previous){
      count++;
    }
    else{
      count++;
      printf("Time: %d Size: %d\n", previous, count);
      count = 0;
    }
    previous = *(memory+i);
  }
  count++;
  printf("Time: %d Size: %d\n", previous, count);
  //get full print out
  //for(int i = 0; i < sizeof(dur_t)*mem_size; i+=sizeof(dur_t)){
  //  printf("%d \n", *(memory+i));
  //}
}

//notes
//average number of probes - avg number of probes PER ALLOCATION
// Best fit should be largest
// How many failures per allocation, <1
// A probe is a contiguous block of 0's. each cell is not a probe. found x 0's, will my request fill this block
// if not increment probe count and move on
//probe count starts at 1
//range and duration randomness % max + 1
//2-5 smaller numbers size of 50 20 time units print mem
//-czvf to compress
//-xzvf to extract