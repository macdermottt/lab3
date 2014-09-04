#include <stdlib.h>
#include <stdio.h>
#include "arrayList.h"
#include <string.h>

//getSize not accessed outside of this file so declare it to be static
//static essentially makes it private to this file 
static int getSize(primitiveType type);

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

int getSize(primitiveType type)
{
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
        default:
            // something that should blow it up immediately
            val = -100;
    }
    return val;
}

void addElement(arrayList * arylstP, void * element)
{
   // if isn't enough space in the array,
   // double the array, and add the element
   if( arylstP->numElements >= arylstP->arraySize )
   {
       // keep a reference to the old one
       void * oldArray = arylstP->array;
       //malloc a new array
       arylstP->array = malloc( (arylstP->arraySize) * 2 );
       //update the array size
       arylstP->arraySize = (arylstP->arraySize) * 2 ;
       //copy the old elements
       /*
       int i;
       for( i = 0; i < sizeof( oldArray ) ; i++ ){
           (( char * ) arylstP->array)[i] = (( char * ) oldArray)[i];
       }
       */
       memcpy( arylstP->array, oldArray, sizeof(oldArray) );
       // free the old array and kill the pointer
       free( oldArray ); oldArray = NULL;
   }
   // either there was enough space, 
   // or we just made enough space
   // so now add the element to the array

    // maybe need to add a case for each type??
    //
   switch( arylstP->type )
   {
       case charType:
            ((char *) arylstP->array)[arylstP->numElements + 1 ] = *((char *)element);
            break;
       case shortType:
            ((short *) arylstP->array)[arylstP->numElements + 1 ] = *((short *)element);
            break;
       case intType:
            ((int *) arylstP->array)[arylstP->numElements + 1 ] = *((int *)element);
            break;
       default:
           // handle invalid type?
           return;
    }
    arylstP->numElements++;
    return;
}

void removeElement(arrayList * arylstP, int index)
{
    if( index > arylstP->numElements )
    {
        // this is invalid
        // TODO log error or some such
        return;
    }
    else{
        int i;
        for( i = index + 1; i <= arylstP->numElements; i++)
        {
            switch ( arylstP->type ){
               case charType:
                    ((char*) arylstP->array)[i-1] = ((char*)arylstP->array)[i];
                    break;
               case shortType:
                    ((short*) arylstP->array)[i-1] = ((short*)arylstP->array)[i];
                    break;
               case intType:
                    ((int*) arylstP->array)[i-1] = ((int*)arylstP->array)[i];
                    break;
            }
        }
        arylstP->numElements--;
    }
   return;
}
      

void printArray(arrayList * arylstP)
{
   int i;
   printf("array size: %d, num elements: %d contents: ", 
          arylstP->arraySize, arylstP->numElements);
   for (i = 0; i < arylstP->numElements; i++)
   {
      if (arylstP->type == charType)
         //fill in the missing code that gets the element and &s it with 0xff
         printf("%02x ", ((char *) arylstP->array)[i]) ;
      else if (arylstP->type == shortType)
         //fill in the missing code that gets the element and &s it with 0xffff
         printf("%04x ", ((short *)arylstP->array)[i] );
      else if (arylstP->type == intType)
         //fill in the missing code that gets the element and &s it with 0xffffffff
         printf("%08x ", ((int *)arylstP->array)[i] );
   }
   printf("\n");
}

