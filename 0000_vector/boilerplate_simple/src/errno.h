#ifndef ARC_STD_ERRNO_H_
#define ARC_STD_ERRNO_H_

#include <stdint.h>

#define ARC_ERRNO_NULL       -0x01
#define ARC_ERRNO_DATA       -0x02
#define ARC_ERRNO_COPY       -0x03
#define ARC_ERRNO_EXISTS     -0x04
#define ARC_ERRNO_INIT       -0x06
#define ARC_ERRNO_OVERFLOW   -0x05
#define ARC_ERRNO_CONNECTION -0x07

#ifdef __cplusplus
extern "C" {
#endif

extern int32_t arc_errno;

#ifdef ARC_DEBUG
    #include <stdio.h>
    //this is handy to override for if they user is doing terminal output and wants to change where logs are sent
    extern FILE *arc_errno_log_file;

    #ifndef ARC_DEBUG_LOG_STREAM_OVERRIDE
        //this functin will be called on start, handy to set the log file to stdout if it is not overrided
        void __attribute__ ((constructor)) ARC_Errno_SetDefaultStream(void);
    #endif // !ARC_DEBUG_LOG_STREAM_OVERRIDE
#endif // !ARC_DEBUG

#ifdef __cplusplus
}
#endif

#ifdef ARC_DEBUG
    #define ARC_DEBUG_LOG_ERROR(STR) fprintf(arc_errno_log_file, "[ERROR %d] " STR "\n", arc_errno)
    #define ARC_DEBUG_LOG_ERROR_WITH_VARIABLES(STR, ...) fprintf(arc_errno_log_file, "[ERROR %d] " STR "\n", arc_errno, __VA_ARGS__)
#else
    #define ARC_DEBUG_LOG_ERROR(STR)
    #define ARC_DEBUG_LOG_ERROR_WITH_VARIABLES(STR, ...)
#endif // !ARC_DEBUG

#endif // !ARC_STD_ERRNO_H_
