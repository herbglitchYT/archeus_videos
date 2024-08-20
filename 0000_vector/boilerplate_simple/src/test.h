#ifndef ARC_TEST_H_
#define ARC_TEST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>

extern uint32_t *temp_arc_test_num_checks_run__ARC_TEST__;
extern uint32_t *temp_arc_test_num_checks_passed__ARC_TEST__;

void ARC_Test_SetErrnoStream(void) __attribute__ ((constructor));
void ARC_Test_UnsetErrnoStream(void) __attribute__ ((destructor));

#define ARC_TEST_START_MESSAGE(MESSAGE) void ARC_TEST_START_MESSAGE__ ## MESSAGE(void) __attribute__ ((constructor));\
    uint32_t arc_test_num_checks_run__ARC_TEST__ ## MESSAGE = 0;\
    uint32_t arc_test_num_checks_passed__ARC_TEST__ ## MESSAGE = 0;\
    void ARC_TEST_START_MESSAGE__ ## MESSAGE(void){\
        printf("[ARC TEST] Running: %s\n", #MESSAGE);\
        temp_arc_test_num_checks_run__ARC_TEST__ = &arc_test_num_checks_run__ARC_TEST__ ## MESSAGE; \
        temp_arc_test_num_checks_passed__ARC_TEST__ = &arc_test_num_checks_passed__ARC_TEST__ ## MESSAGE; \
    }

#define ARC_TEST_END_MESSAGE(MESSAGE) void ARC_TEST_END_MESSAGE__ ## MESSAGE(void) __attribute__ ((destructor));\
    void ARC_TEST_END_MESSAGE__ ## MESSAGE(void){\
        printf("[ARC TEST] RUN: %4u, PASSED: %4u, FAILED: %4u, Completed: %s\n", arc_test_num_checks_run__ARC_TEST__ ## MESSAGE, arc_test_num_checks_passed__ARC_TEST__ ## MESSAGE, arc_test_num_checks_run__ARC_TEST__ ## MESSAGE - arc_test_num_checks_passed__ARC_TEST__ ## MESSAGE, #MESSAGE);\
    }

#define ARC_TEST(MESSAGE) ARC_TEST_START_MESSAGE(MESSAGE) ARC_TEST_END_MESSAGE(MESSAGE) void ARC_TEST__ ## MESSAGE(void) __attribute__ ((constructor)); void ARC_TEST__ ## MESSAGE (void)

#define ARC_CHECK(TEST)\
    if(temp_arc_test_num_checks_run__ARC_TEST__ == NULL || temp_arc_test_num_checks_passed__ARC_TEST__ == NULL){ return; }\
    printf("  %4u) ", *temp_arc_test_num_checks_run__ARC_TEST__);\
    ++*temp_arc_test_num_checks_run__ARC_TEST__;\
    if(TEST){ printf("PASS\t\n"); ++*temp_arc_test_num_checks_passed__ARC_TEST__; }\
    else { printf("FAIL\t%s\n", #TEST); }

#ifdef __cplusplus
}
#endif

#endif // !ARC_TEST_H_
