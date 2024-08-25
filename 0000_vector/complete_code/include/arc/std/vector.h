#ifndef ARC_STD_VECTOR_H_
#define ARC_STD_VECTOR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "arc/std/bool.h"
#include <stdint.h>

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

#ifdef __cplusplus
}
#endif

#endif // !ARC_STD_VECTOR_H_
