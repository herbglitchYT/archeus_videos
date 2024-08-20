# What I mean by a vector
My definition of a vector is a expandable array. For math vectors I use `vector2` and `vector3`. I'll be writing this in C, but the concepts should easily be transferred to any other language.

# How does a vector work
For the most basic implementation of a vector, and the implementation we will use, when we run out of space in an array, we will create a new array of double the size and copy the old arrays contents into the new array.
We can use the same idea for downsizing the array.

# Description stuff
In the description I have included a repository that holds, boilerplate for this project, the script I am reading, the finished project we will make, and all other related files.
You might notice I am on linux, I have also tested this code on windows with msys2 using their ucrt MinGW and had no issues with it. If you do have any issues, please let me know.

# ARC_Errno and ARC_Bool
If you are watching this video when it comes out, I most likely won't have made a video for `ARC_Errno` and `ARC_Bool` yet. We will be using them both and they are part of the boilerplate. If you don't want to deal with the boilerplate, using a `printf` or whatever your language uses to output will work for what we use `ARC_Errno` for. And C has `stdbool.h`, which is pretty much all `ARC_Bool` is.

# CMake
Like with ARC_Errno and ARC_Bool, if you are watching when this video releases, I will not have gone over setting up cmake for a library. So for this I'd recommend either making a normal `CMakeLists.txt` which I have a video on and is linked in the description, or using the `CMakeLists.txt` provided in the boilerplate. If the cmake library video has come out, and you have seen it, I would recommend using that `CMakeLists.txt` and adding this to the library

# Make
If you don't like cmake, I have also included a "simple" boilerplate. Though if you use the simple boilerplate, do not include from "arc/std/", I'll let you know the changes when we get there.

# Write the header boilerplate
Headers to me are the best place for documentation. I try to document code as much as possible, though because this process takes a long time I'll speed up the footage of me writing the documentation when we get to it.

I'll write out the boilerplate for those not using a boilerplate. Lets add the include guards, and to keep this from erroring if we want to use this in c++, we will add `extern "c"` if `__cplusplus` is defined and close that out.
```c
#ifndef ARC_STD_VECTOR_H_
#define ARC_STD_VECTOR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "arc/std/bool.h"
#include <stdint.h>



#ifdef __cplusplus
}
#endif

#endif //ARC_STD_VECTOR_H_
```

# How to approach this video
To get more out of this video, I will recommend different challenges to complete while having the video paused.

The first challenge is to write down functions you think a vector will need. You might come up with different functions which could be handy later down the line, so please feel free to keep the functions even if it is not what we end up having in this video. In this video we will be writing an extremely basic system.

I'd recommend pausing the video and trying the challenge now

# Write the header function
For our basic implementation we will have
```c
/**
 * @brief a dynamic array type
 */
typedef struct ARC_Vector ARC_Vector;

/**
 * @brief a callback that allows the user to define a way to check the data stored in a vector for a match
 *
 * @param[in] dataA the first data to check
 * @param[in] dataB the second data to check
 *
 * @return ARC_True when dataA == dataB, and ARC_False otherwise
*/
typedef ARC_Bool (* ARC_Vector_CompareDataFn)(void *dataA, void *dataB);

/**
 * @brief creates an ARC_Vector which is an "expandable" array
 *
 * @note for this basic implementation, the array will double in size every time the capacity is hit
 * @note the array will also half in size when the array is only half filled
 *
 * @param[out] vector        ARC_Vector to initialize
 * @param[in]  compareDataFn a callback that checks if data stored in the array matches,
 *                           if set to NULL and ARC_Vector_Remove is called, the pointer addresses will be compared
 */
void ARC_Vector_Create(ARC_Vector **vector, ARC_Vector_CompareDataFn *compareDataFn);

/**
 * @brief destroys an ARC_Vector
 *
 * @note this will not free the items stored in the vector
 * @note please make sure to clear and free the children before destroying an ARC_Vector
 *
 * @param[in] vector ARC_Vector to free
 */
void ARC_Vector_Destroy(ARC_Vector *vector);

/**
 * @brief adds an item to an ARC_Vector
 *
 * @note this will error if you add more than 4,294,967,295 items (the max value of an unsigned int 32)
 *
 * @param[in] vector ARC_Vector to add to
 * @param[in] data   data that is being added
 */
void ARC_Vector_Add(ARC_Vector *vector, void *data);

/**
 * @brief removes an item from a matching item in an ARC_Vector
 *
 * @note this function uses the ARC_Vector_CompareDataFn that the ARC_Vector was created with
 * @note this function will not throw an error if there is no match
 *
 * @param[in] vector ARC_Vector to remove from
 * @param[in] data   matching data to remove
 */
void ARC_Vector_Remove(ARC_Vector *vector, void *data);

/**
 * @brief removes an item from an ARC_Vector at an index
 *
 * @note this function will error if trying to remove an index that is outside the bounds of the ARC_Vector
 *
 * @param[in] vector ARC_Vector to remove from
 * @param[in] index  position of data to remove
 */
void ARC_Vector_RemoveIndex(ARC_Vector *vector, uint32_t index);

/**
 * @brief gets the current size of an ARC_Vector as an unsigned 32 bit integer
 *
 * @param[in] vector ARC_Vector to get current size from
 *
 * @return the current size as a unsigned 32 bit integer
 */
uint32_t ARC_Vector_GetSize(ARC_Vector *vector);

/**
 * @brief gets an item from an ARC_Vector at a position index
 *
 * @note this function will error if trying to get an index that is outside the bounds of the ARC_Vector
 *
 * @param[in] vector ARC_Vector to get data from
 * @param[in] index  position of data to get
 *
 * @return a void * item, or NULL on error
 */
void *ARC_Vector_Get(ARC_Vector *vector, uint32_t index);
```

# Write the Type
now that we have a basic outline for what a vector will be lets create the ARC_Vector struct in the c file
```c
struct ARC_Vector {

}
```
Now your next challenge is to fill that struct with what you think we will need.

I'd recommend pausing the video and trying the challenge now.

For what we will be using in this video for the basic type are four things. The first will be a `void **` or an array of unknown types, two `uint32_t`for storing the current size and what our current capacity will be, and lastly a callback for a compare data function
```c
#include "arc/std/bool.h"
#include "arc/std/errno.h"
#include <stdint.h>
#include <stdlib.h>

struct ARC_Vector {
    uint32_t currentCapacity;
    uint32_t currentSize;

    void **data;

    ARC_Vector_CompareDataFn compareDataFn;
};
```

# Write the default compareDataFn
The callback `CompareDataFn` is used when removing an item from the vector. This is handy if the vector holds a matching item that is in a different pointer from the one we check.
Though for our default `compareDataFunction` we can just check to see if the pointers are the same, as we don't have more information for what the void pointers holds.
```c
//this is a private function used as the default check for removing data from a given pointer
ARC_Bool ARC_Vector_CompareDataDefaultFn(void *dataA, void *dataB){
    if(dataA == dataB){
        return ARC_True;
    }

    return ARC_False;
}
```

# Write the creation and destruction functions
I like writing creation and destruction functions together and editing them together so I'm a lot less likely to get a memory leak. If you are using a object oriented language, the creation and destruction functions will be your constructors and destructors.

Your next challenge is to try writing the creation and destruction functions.

I'd recommend pausing the video and trying the challenge now.

We'll first `malloc` the vector itself, create the data with one slot and set `currentCapacity` to one, then set `currentSize` to zero. From experience, I recommend always assigning a value to any variable or type you create even if that value is NULL in the creation function or constructor. Lastly we will assign `compareDataFn` with the default function, then assign the value passed in through parameters if it is not NULL. I like doing things this way so I don't have to use the else keyword. I don't know why, but I really don't like the else keyword
```c
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
```

Now to destroy the vector, we need to free everything we have allocated, so we call free on the data, and then the vector itself
```c
void ARC_Vector_Destroy(ARC_Vector *vector){
    //free everything stored in the vector
    free(vector->data);

    //free the vector
    free(vector);
}
```

# Write the add function
Lets now write an add function. You know the drill, the challenge is to take a crack at writing your own add function.

I'd recommend pausing the video and trying the challenge now.

First we need to check if the vector is completely filled up, and if it is, we can't add anything and will throw an error

Next we check to see if the `currentSize` is equal to the `currentCapacity`, if it is we will need to increase the capacity. Because we are simply doubling the vector, we can bit shift `currentCapacity`'s value left one. If bit shifting is confusing to you, feel free to times the value by two. After setting `currentCapacity` to the doubled size, we need to actually double the vectors size. We will use `realloc` as that will change the vectors size and copy the contents at the same time.

Lastly we will add the data to the vector at its `currentSize` and increase that current size by one
```c
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
        vector->data = (void **)realloc(vector->data, sizeof(void *) * vector->currentCapacity);
    }

    //add to the vectors array and increase its current size
    vector->data[vector->currentSize] = data;
    vector->currentSize++;
}
```

# Write the remove index function
For this example we have two different remove functions and to make things easier, we can do most of the logic of removing in one function. We'll do that in the Remove Index function.

The challenge as you probably guessed is to write the remove index function.

I'd recommend pausing the video and trying the challenge now.

To remove with an index, we first should check if the index actually exists in the vector. As we are using an unsigned 32 bit integer, we can just check to see if the index is the same as the `currentSize` or greater, if it is, we are out of bounds.

Next we can iterate from the given index to the end copying the next value back one. This will override the index's value and shift everything back one. To make sure we don't go out out of bounds of the vectors array, we will check if `index + 1` is out of bounds in the for loop.

Now we can decrease the `currentSize` by one.

We should check to see if the current size is not the same as half the capacity or if the capacity is one (there is no reason to have a capacity of zero), and if it is either of those two things, we don't need to do anything else so we can return.

Now we can now safely half the capacity, so we'll bit shift right. Again, if you are uncomfortable bit shifting, feel free to do integer division by two. And we can `realloc` again to size down and copy the contents
```c
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
    vector->data = (void **)realloc(vector->data, sizeof(void *) * vector->currentCapacity);
}
```

# Write the remove function
Most of the heavy lifting went into the remove index function. We will place The remove function in the c file above the remove index, just to match the header.

the challenge is to see if you can write the remove function. a slight hint for if you have followed along with the code, remember there is a callback in the vector struct

I'd recommend pausing the video and trying the challenge now.

Now all we need to do is iterate through the data, checking for a match with the `compareDataFn` and on match remove the item at the index. I personally don't see a reason to throw an error if nothing is removed (at least in the majority of uses I can think of), so we won't do that. Though in the header, there is a note in the documentation letting any user know that this is the case.

```c
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
```

# Write the get size and get functions
For our last non bonus challenge, please try to write the get size and get functions

I'd recommend pausing the video and trying the challenge now.

For the get size function, we can just return the vector's current size. For the get function we should error check for out of bounds, and if it is, we can set the error to null and log that it is out of bounds, then return NULL. Otherwise we can return the data value at the index

```c
uint32_t ARC_Vector_GetSize(ARC_Vector *vector){
    return vector->currentSize;
}

void *ARC_Vector_Get(ARC_Vector *vector, uint32_t index){
    //check to make sure the given index is in bounds of the vector
    if(index >= vector->currentSize){
        arc_errno = ARC_ERRNO_DATA;
        ARC_DEBUG_LOG_ERROR_WITH_VARIABLES("ARC_Vector_Get(vector, %u), null value as the index was out of bounds", index);
        return NULL;
    }

    return vector->data[index];
}
```

# Write test functions
to make sure everything works and that we don't have any memory leaks, lets write some tests for each function. For this I'll be using a testing header and c file I have written included in the boilerplates. For now that file is a nightmare so I won't explain it, but I'll try to clean it up and make a video for how to write a testing system.

Lets open the `testing/std/vector.c` file and write some tests. I have never done testing like this before, but I believe it is an important part of making sure your code works like how you want it to. We won't write a ton of tests, and I'm sure we will miss some important tests. But for this video we are just doing some basic testing.

We will be testing with 32 bit integers, and so we need to create a testing compare data function. All we have to do is de-reference the pointers as 32 bit ints, and check the values.

for a bonus challenge, please try to think up some tests you could write.
To test you define ARC_Test and give it a name that matches what you are testing like `AddATonOfThingsToVector` and add curly braces to the end.
then inside you can write code like normal, and to check output you can use `ARC_CHECK();` with a boolean expresson on the inside
```c
ARC_TEST(AddATonOfThingsToVector){
    int32_t coolVar = 69;
    int32_t chillVar = 420;

    ARC_Test(coolVar != chillVar);
}
```

I'd recommend pausing the video and trying the bonus challenge now.

Alright, for the tests, first we can add remove by index and check that the vector is holding the correct values, I'll be using refrences instead of creating pointers just to keep things simple

Then we can do the same thing but with the regular remove, just remember to pass that callback into the vector creation function

And lastly we can check that the size is working
```c
#include "../test.h"
#include "arc/std/bool.h"
#include "arc/std/vector.h"
#include <stdint.h>

ARC_Bool TEST_Vector_CompareDataFn(void *dataA, void *dataB){
    if(*(int32_t *)dataA == *(int32_t *)dataB){
        return ARC_True;
    }

    return ARC_False;
}

ARC_TEST(AddRemoveByIndexAndCheckValuesInVector){
    ARC_Vector *vector;
    ARC_Vector_Create(&vector, NULL);

    int32_t val0 = 0;
    int32_t val1 = 1;
    int32_t val2 = 2;
    int32_t val3 = 3;
    int32_t val4 = 4;

    ARC_Vector_Add(vector, &val0);
    ARC_Vector_Add(vector, &val1);
    ARC_Vector_Add(vector, &val2);
    ARC_Vector_Add(vector, &val3);
    ARC_Vector_Add(vector, &val4);

    ARC_CHECK(0 == *(int32_t *)ARC_Vector_Get(vector, 0));
    ARC_CHECK(1 == *(int32_t *)ARC_Vector_Get(vector, 1));
    ARC_CHECK(2 == *(int32_t *)ARC_Vector_Get(vector, 2));
    ARC_CHECK(3 == *(int32_t *)ARC_Vector_Get(vector, 3));
    ARC_CHECK(4 == *(int32_t *)ARC_Vector_Get(vector, 4));
    ARC_Vector_RemoveIndex(vector, 0);

    ARC_CHECK(1 == *(int32_t *)ARC_Vector_Get(vector, 0));
    ARC_CHECK(2 == *(int32_t *)ARC_Vector_Get(vector, 1));
    ARC_CHECK(3 == *(int32_t *)ARC_Vector_Get(vector, 2));
    ARC_CHECK(4 == *(int32_t *)ARC_Vector_Get(vector, 3));
    ARC_Vector_RemoveIndex(vector, 3);

    ARC_CHECK(1 == *(int32_t *)ARC_Vector_Get(vector, 0));
    ARC_CHECK(2 == *(int32_t *)ARC_Vector_Get(vector, 1));
    ARC_CHECK(3 == *(int32_t *)ARC_Vector_Get(vector, 2));
    ARC_Vector_RemoveIndex(vector, 1);

    ARC_CHECK(1 == *(int32_t *)ARC_Vector_Get(vector, 0));
    ARC_CHECK(3 == *(int32_t *)ARC_Vector_Get(vector, 1));
    ARC_Vector_RemoveIndex(vector, 1);

    ARC_CHECK(1 == *(int32_t *)ARC_Vector_Get(vector, 0));
    ARC_Vector_RemoveIndex(vector, 0);

    ARC_Vector_Destroy(vector);
}

ARC_TEST(AddRemoveAndCheckValuesInVector){
    ARC_Vector *vector;
    ARC_Vector_CompareDataFn testCompareDataFn = TEST_Vector_CompareDataFn;
    ARC_Vector_Create(&vector, &testCompareDataFn);

    int32_t val0 = 0;
    int32_t val1 = 1;
    int32_t val2 = 2;
    int32_t val3 = 3;
    int32_t val4 = 4;

    ARC_Vector_Add(vector, &val0);
    ARC_Vector_Add(vector, &val1);
    ARC_Vector_Add(vector, &val2);
    ARC_Vector_Add(vector, &val3);
    ARC_Vector_Add(vector, &val4);

    ARC_CHECK(0 == *(int32_t *)ARC_Vector_Get(vector, 0));
    ARC_CHECK(1 == *(int32_t *)ARC_Vector_Get(vector, 1));
    ARC_CHECK(2 == *(int32_t *)ARC_Vector_Get(vector, 2));
    ARC_CHECK(3 == *(int32_t *)ARC_Vector_Get(vector, 3));
    ARC_CHECK(4 == *(int32_t *)ARC_Vector_Get(vector, 4));
    ARC_Vector_Remove(vector, &val0);

    ARC_CHECK(1 == *(int32_t *)ARC_Vector_Get(vector, 0));
    ARC_CHECK(2 == *(int32_t *)ARC_Vector_Get(vector, 1));
    ARC_CHECK(3 == *(int32_t *)ARC_Vector_Get(vector, 2));
    ARC_CHECK(4 == *(int32_t *)ARC_Vector_Get(vector, 3));
    ARC_Vector_Remove(vector, &val4);

    ARC_CHECK(1 == *(int32_t *)ARC_Vector_Get(vector, 0));
    ARC_CHECK(2 == *(int32_t *)ARC_Vector_Get(vector, 1));
    ARC_CHECK(3 == *(int32_t *)ARC_Vector_Get(vector, 2));
    ARC_Vector_Remove(vector, &val2);

    ARC_CHECK(1 == *(int32_t *)ARC_Vector_Get(vector, 0));
    ARC_CHECK(3 == *(int32_t *)ARC_Vector_Get(vector, 1));
    ARC_Vector_Remove(vector, &val1);

    ARC_CHECK(3 == *(int32_t *)ARC_Vector_Get(vector, 0));
    ARC_Vector_Remove(vector, &val3);

    ARC_Vector_Destroy(vector);
}

ARC_TEST(AddAndCheckSizeInVector){
    ARC_Vector *vector;
    ARC_Vector_Create(&vector, NULL);

    int32_t val0 = 0;
    int32_t val1 = 1;
    int32_t val2 = 2;
    int32_t val3 = 3;
    int32_t val4 = 4;

    ARC_Vector_Add(vector, &val0);
    ARC_Vector_Add(vector, &val1);
    ARC_Vector_Add(vector, &val2);
    ARC_Vector_Add(vector, &val3);
    ARC_Vector_Add(vector, &val4);

    ARC_CHECK(5 == ARC_Vector_GetSize(vector));
    ARC_Vector_RemoveIndex(vector, 0);

    ARC_CHECK(4 == ARC_Vector_GetSize(vector));
    ARC_Vector_RemoveIndex(vector, 0);

    ARC_CHECK(3 == ARC_Vector_GetSize(vector));
    ARC_Vector_RemoveIndex(vector, 0);

    ARC_CHECK(2 == ARC_Vector_GetSize(vector));
    ARC_Vector_RemoveIndex(vector, 0);

    ARC_CHECK(1 == ARC_Vector_GetSize(vector));
    ARC_Vector_RemoveIndex(vector, 0);

    ARC_CHECK(0 == ARC_Vector_GetSize(vector));

    ARC_Vector_Destroy(vector);
}
```

We now can run the tests, make sure everything works as it should, and for those on linux and probably mac run valgrind to see if we have any memory leaks, sadly for windows I don't know if there is a tool to check memory leaks like valgrind.

# Help and questions
Thank you for watching this video, if you would like help or if there is something wrong with the video, please check the description for ways to contact me. youtube comments are not a good place to reach me.
