#include "arc/std/vector.h"

#include "arc/std/bool.h"
#include "arc/std/errno.h"
#include <stdio.h>
#include <stdlib.h>

struct ARC_Vector {
    uint32_t currentCapacity;
    uint32_t currentSize;

    void **data;

    ARC_Vector_CompareDataFn compareDataFn;
};

//this is a private function used as the default check for removing data from a given pointer
ARC_Bool ARC_Vector_CompareDataDefaultFn(void *dataA, void *dataB){
    if(dataA == dataB){
        return ARC_True;
    }

    return ARC_False;
}

void ARC_Vector_Create(ARC_Vector **vector, ARC_Vector_CompareDataFn *compareDataFn){
    //create the vector
    *vector = (ARC_Vector *)malloc(sizeof(ARC_Vector));

    //initialize all the values stored in the vector
    (*vector)->data            = (void **)malloc(sizeof(void *));
    (*vector)->currentCapacity = 1;
    (*vector)->currentSize     = 0;

    //set a default for compareDataFn, then override it if it is passed in through parameters
    (*vector)->compareDataFn = ARC_Vector_CompareDataDefaultFn;
    if(compareDataFn != NULL){
        (*vector)->compareDataFn = *compareDataFn;
    }
}

void ARC_Vector_Destroy(ARC_Vector *vector){
    //free everything stored in the vector
    free(vector->data);

    //free the vector
    free(vector);
}

void ARC_Vector_Add(ARC_Vector *vector, void *data){
    //check to see if the current size is the same as a max uint32_t and if so it will overflow so throw an error
    if(vector->currentSize == ~((uint32_t)0)){
        arc_errno = ARC_ERRNO_OVERFLOW;
        ARC_DEBUG_LOG_ERROR("ARC_Vector_Add(vector, data), vector at max capacity tried adding another value");
        return;
    }

    //check if we are at the max of the current capacity
    if(vector->currentSize == vector->currentCapacity){
        //increase the current capacity by double
        vector->currentCapacity <<= 1;

        //if for some reason the capacity is 0, we should set it to one so we don't error on realloc
        if(vector->currentCapacity != 0){
            vector->currentCapacity++;
        }

        //resize the vector's array and copy the contents at the same time
        vector->data = (void *)realloc(vector->data, sizeof(void *) * vector->currentCapacity);
    }

    //add to the vectors array and increase its current size
    vector->data[vector->currentSize] = data;
    vector->currentSize++;
}

void ARC_Vector_Remove(ARC_Vector *vector, void *data){
    //iterate through every item to check to see if it exists
    for(uint32_t index = 0; index < vector->currentSize; index++){
        //keep the code cleaner by pulling the current index data into a temp variable
        void *dataB = vector->data[index];

        //check if the data matches, and if so remove by index
        if(vector->compareDataFn(data, dataB) == ARC_True){
            ARC_Vector_RemoveIndex(vector, index);
        }
    }
}

void ARC_Vector_RemoveIndex(ARC_Vector *vector, uint32_t index){
    //check to make sure the given index is in bounds of the vector
    if(index >= vector->currentSize){
        arc_errno = ARC_ERRNO_DATA;
        ARC_DEBUG_LOG_ERROR("ARC_Vector_Add(vector, data), vector at max capacity tried adding another value");
        return;
    }

    //we will be using index to iterate as we won't use it again, so we can skip the first part of the for loop
    for(; index + 1 < vector->currentSize; index++){
        //override the data from index to the end by shifting it back one
        vector->data[index] = vector->data[index + 1];
    }

    //we have removed the item so we can decrease the current size
    vector->currentSize--;

    //if the current size is half the current capacity or the current capacity is at the smallest limit, we don't need to do anything else
    if(vector->currentSize != vector->currentCapacity >> 1 || vector->currentCapacity == 1){
        return;
    }

    //half the capacity and copy it into a smaller array
    vector->currentCapacity >>= 1;
    vector->data = (void *)realloc(vector->data, sizeof(void *) * vector->currentCapacity);
}

uint32_t ARC_Vector_GetSize(ARC_Vector *vector){
    return vector->currentSize;
}

void *ARC_Vector_Get(ARC_Vector *vector, uint32_t index){
    if(index >= vector->currentSize){
        arc_errno = ARC_ERRNO_DATA;
        ARC_DEBUG_LOG_ERROR_WITH_VARIABLES("ARC_Vector_Get(vector, %u), null value as the index was out of bounds", index);
        return NULL;
    }

    return vector->data[index];
}
