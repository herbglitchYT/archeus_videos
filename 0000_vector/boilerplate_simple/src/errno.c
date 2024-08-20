#include "errno.h"

#include <stdint.h>

int32_t arc_errno = 0;

#if ARC_DEBUG
    #include <stdio.h>
    FILE *arc_errno_log_file = NULL;

    #ifndef ARC_DEBUG_LOG_STREAM_OVERRIDE
        void ARC_Errno_SetDefaultStream(void){
            arc_errno_log_file = stdout;
        }
    #endif
#endif
