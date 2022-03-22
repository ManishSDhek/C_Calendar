#ifndef CALENDAR_PRIV_H_
#define CALENDAR_PRIV_H_

#include <stdint.h>

#define IN_MAX_ARGS            3
#define YEAR_ARG_INDEX         1
#define FILENAME_ARG_INDEX     2
#define MAX_YEAR_CHAR_LENGTH   4

static void log_errors (enum error_code);
static uint16_t convert_to_int (const char * const, uint16_t); 

#endif