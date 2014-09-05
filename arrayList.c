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
            printf("getSize has and invalid type, please fix this");
            exit(0);
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
       int newSize = arylstP->arraySize * getSize( arylstP->type ) * 2;
       arylstP->array = malloc( newSize );
       //copy the old elements
       memcpy( arylstP->array, oldArray, arylstP->arraySize * getSize( arylstP->type )  );
       //update the array size
       arylstP->arraySize = (arylstP->arraySize) * 2 ;
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
            ((char *) arylstP->array)[arylstP->numElements ] = *((char *)element);
            break;
       case shortType:
            ((short *) arylstP->array)[arylstP->numElements ] = *((short *)element);
            break;
       case intType:
            ((int *) arylstP->array)[arylstP->numElements ] = *((int *)element);
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
        printf("the index is greater than the number of elements!!!!\n");
        exit(0);
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
                    ((short*) arylstP->array)[i-1] = (unsigned short )((short*)arylstP->array)[i];
                    break;
               case intType:
                    ((int*) arylstP->array)[i-1] = (unsigned int)((int*)arylstP->array)[i];
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
         printf("%02x ", (unsigned char) ((char *) arylstP->array)[i]) ;
      else if (arylstP->type == shortType)
         //fill in the missing code that gets the element and &s it with 0xffff
         printf("%04x ", (unsigned short) ((short *)arylstP->array)[i] );
      else if (arylstP->type == intType)
         //fill in the missing code that gets the element and &s it with 0xffffffff
         printf("%08x ", (unsigned int) ((int *)arylstP->array)[i] );
   }
   printf("\n");
}

