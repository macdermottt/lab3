#include <stdlib.h>
#include <stdio.h>
#include "arrayList.h"
#include <string.h>
/* Lab3  ArrayList
 * Dr Norris CS3481 Fall 2014 
 *
 * author: Tobin MacDermott
 */

//getSize not accessed outside of this file so declare it to be static
//static essentially makes it private to this file 
static int getSize(primitiveType type);

/* function initialize
 * initializes a new arralist for the given type
 *
 * params:
 *  primativeType type - one of the primative type enums
 *
 * returns:
 *  arraylist *  - a pointer to the new arraylist
 *
 */
arrayList * initialize(primitiveType type)
{
    arrayList * aList = ( arrayList * ) malloc( sizeof ( arrayList ) );
    aList->elementSize = getSize( type );
    aList->arraySize = 4;
    aList->numElements = 0;
    aList->type = type;
    aList->array = malloc ( getSize( type ) * 4 );
   return aList;
}

/* function getSize
 * calculates the number of bytes needed
 * for the given type
 *
 * params:
 *  primativeType type - the type to calculate the size of
 *
 * returns:
 *  int - the number of bytes needed for the type
 *
 */
int getSize(primitiveType type)
{
    // return the correct size for the type
    int val = 0;
    switch( type ){
        case charType:
            val = sizeof( char );
            break;
        case shortType:
            val = sizeof( short );
            break;
        case intType:
            val = sizeof( int );
            break;
    }
    return val;
}

/* function addElement
 * adds an element to an arraylist
 *
 * params:
 *  arrayList * arylstP - a pointer to the arrayList
 *  void * element - a pointer to the element to add
 *
 * returns:
 *  void
 *
 */
void addElement(arrayList * arylstP, void * element)
{
   // if isn't enough space in the array,
   // double the array, and add the element
   if( arylstP->numElements >= arylstP->arraySize )
   {
       // keep a reference to the old one
       void * oldArray = arylstP->array;
       // calculate the no bytes needed for the new array
       //            size old array           size of type         double it
       int newSize = arylstP->arraySize * getSize( arylstP->type ) * 2;
       arylstP->array = malloc( newSize );
       //copy the old elements
       memcpy( arylstP->array, oldArray, arylstP->arraySize * getSize( arylstP->type )  );
       //update the array size
       arylstP->arraySize = (arylstP->arraySize) * 2 ;
       // free the old array and kill the pointer
       free( oldArray ); oldArray = NULL;
   }
   // now guaranteed to have enough space
   // so add the element to the end of the arrayList
   switch( arylstP->type )
   {
       case charType:
            ((char *) arylstP->array)[arylstP->numElements ] = *((char *)element);
            break;
       case shortType:
            ((short *) arylstP->array)[arylstP->numElements ] = *((short *)element);
            break;
       case intType:
            ((int *) arylstP->array)[arylstP->numElements ] = *((int *)element);
            break;
    }
    // we just added an element
    // so increment the number of elements
    arylstP->numElements++;
    return;
}

/* function removeElement
 * removes an element from an arrayList
 * 
 * params:
 *  arrayList * arylstP - a pointer to the arrayList
 *  int index - the index in the list to remove
 *
 * returns:
 *  void
 */
void removeElement(arrayList * arylstP, int index)
{
    // check that the index is valid
    if( index > arylstP->numElements && index > 0 ) 
    {
        // printing something is better than just dieing
        printf("the index is invalid\n");
        exit(0);
    }
    else{
        // to remove an element
        // shift all remaining elements one space to the left.  
        // then decrement numElements
        int i;
        for( i = index + 1; i <= arylstP->numElements; i++)
        {
            // make sure we are shifting the correct
            // number of bits for the type
            switch ( arylstP->type ){
               case charType:
                    ((char*) arylstP->array)[i-1] = ((unsigned char*)arylstP->array)[i];
                    break;
               case shortType:
                    ((short*) arylstP->array)[i-1] = ((unsigned short*)arylstP->array)[i];
                    break;
               case intType:
                    ((int*) arylstP->array)[i-1] = ((unsigned int*)arylstP->array)[i];
                    break;
            }
        }
        // we just removed an element,
        // so decrement the number of elements
        arylstP->numElements--;
    }
   return;
}
      

/* function printArray
 * prints out the arraylist
 * in a regular manner
 *
 * params:
 *  arrayList * arylstP - a pointer to an arrayList to print
 *
 * returns:
 *  void
 */
void printArray(arrayList * arylstP)
{
   int i;
   printf("array size: %d, num elements: %d contents: ", 
          arylstP->arraySize, arylstP->numElements);
   for (i = 0; i < arylstP->numElements; i++)
   {
      if (arylstP->type == charType)
         //prints a char
         printf("%02x ", (unsigned char) ((char *) arylstP->array)[i]) ;
      else if (arylstP->type == shortType)
         //prints a short
         printf("%04x ", (unsigned short) ((short *)arylstP->array)[i] );
      else if (arylstP->type == intType)
         //prints an int
         printf("%08x ", (unsigned int) ((int *)arylstP->array)[i] );
   }
   printf("\n");
}

