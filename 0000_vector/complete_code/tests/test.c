#include "test.h"

#include "arc/std/errno.h"
#include <stdio.h>
#include <stdlib.h>

uint32_t *temp_arc_test_num_checks_run__ARC_TEST__ = NULL;
uint32_t *temp_arc_test_num_checks_passed__ARC_TEST__ = NULL;

void ARC_Test_SetErrnoStream(void){
    arc_errno_log_file = fopen("tests/test_error_out.txt", "w");
}

void ARC_Test_UnsetErrnoStream(void){
    fclose(arc_errno_log_file);
}

#ifndef ARC_TEST_NO_MAIN
int main(void){
    return 0;
}
#endif
