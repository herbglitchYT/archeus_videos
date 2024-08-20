#include "../test.h"
#include "arc/std/bool.h"
#include "arc/std/errno.h"
#include "arc/std/vector.h"
#include <stdint.h>

ARC_Bool TEST_Vector_CompareDataFn(void *dataA, void *dataB){
    if(*(int32_t *)dataA == *(int32_t *)dataB){
        return ARC_True;
    }

    return ARC_False;
}

ARC_TEST(Vector_Add_RemoveIndex_Get){
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

ARC_TEST(Vector_Add_Remove_Get){
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

ARC_TEST(Vector_Add_RemoveIndex_GetSize){
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

ARC_TEST(Vector_Add_RemoveIndex_Get_Try_Out_Of_Bounds){
    ARC_Vector *vector;
    ARC_Vector_Create(&vector, NULL);

    int32_t val0 = 0;

    ARC_Vector_Add(vector, &val0);
    ARC_CHECK(NULL == ARC_Vector_Get(vector, 1));
    arc_errno = 0;

    ARC_Vector_RemoveIndex(vector, 0);

    ARC_Vector_Destroy(vector);
}
