#ifndef _TINYGL_LOG_H
#define _TINYGL_LOG_H

#include <stdio.h>


// Log Tag
#ifdef __linux__
    #define TINYGL_LOG_TAG_VERBOSE  "\033[97;1mVERBOSE\033[0m"
    #define TINYGL_LOG_TAG_DEBUG    "\033[96;1mDEBUG\033[0m"
    #define TINYGL_LOG_TAG_INFO     "\033[94;1mINFO\033[0m"
    #define TINYGL_LOG_TAG_WARNING  "\033[93;1mWARNING\033[0m"
    #define TINYGL_LOG_TAG_ERROR    "\033[91;1mERROR\033[0m"
#else
    #define TINYGL_LOG_TAG_VERBOSE  "VERBOSE"
    #define TINYGL_LOG_TAG_DEBUG    "DEBUG"
    #define TINYGL_LOG_TAG_INFO     "INFO"
    #define TINYGL_LOG_TAG_WARNING  "WARNING"
    #define TINYGL_LOG_TAG_ERROR    "ERROR"
#endif 


// enum of LOG_LEVEL
#define    TINYGL_LOG_LEVEL_ERROR      0
#define    TINYGL_LOG_LEVEL_WARNING    1
#define    TINYGL_LOG_LEVEL_INFO       2
#define    TINYGL_LOG_LEVEL_DEBUG      3
#define    TINYGL_LOG_LEVEL_VERBOSE    4


// Default LOG_LEVEL
#ifndef TINYGL_LOG_LEVEL
    #define TINYGL_LOG_LEVEL TINYGL_LOG_LEVEL_INFO
#endif // LOG_LEVEL


#if TINYGL_LOG_LEVEL >= TINYGL_LOG_LEVEL_VERBOSE
    #define TINYGL_LOG_VERBOSE(fmt, ...) fprintf(stdout, "[%s:%d][" TINYGL_LOG_TAG_VERBOSE "]: " fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#else
    #define TINYGL_LOG_VERBOSE(fmt, ...)
#endif

#if TINYGL_LOG_LEVEL >= TINYGL_LOG_LEVEL_DEBUG
    #define TINYGL_LOG_DEBUG(fmt, ...) fprintf(stdout, "[%s:%d][" TINYGL_LOG_TAG_DEBUG "]: " fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#else
    #define TINYGL_LOG_DEBUG(fmt, ...)
#endif

#if TINYGL_LOG_LEVEL >= TINYGL_LOG_LEVEL_INFO
    #define TINYGL_LOG_INFO(fmt, ...) fprintf(stdout, "[%s:%d][" TINYGL_LOG_TAG_INFO "]: " fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#else
    #define TINYGL_LOG_INFO(fmt, ...)
#endif

#if TINYGL_LOG_LEVEL >= TINYGL_LOG_LEVEL_WARNING
    #define TINYGL_LOG_WARNING(fmt, ...) fprintf(stdout, "[%s:%d][" TINYGL_LOG_TAG_WARNING "]: " fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#else
    #define TINYGL_LOG_WARNING(fmt, ...)
#endif

#if TINYGL_LOG_LEVEL >= TINYGL_LOG_LEVEL_ERROR
    #define TINYGL_LOG_ERROR(fmt, ...) fprintf(stderr, "[%s:%d][" TINYGL_LOG_TAG_ERROR "]: " fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#else
    #define TINYGL_LOG_ERROR(fmt, ...)
#endif

#endif // _TINYGL_LOG_H