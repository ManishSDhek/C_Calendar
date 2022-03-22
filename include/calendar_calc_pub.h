#ifndef CALENDAR_CALC_PUB_H_
#define CALENDAR_CALC_PUB_H_

#include <stdint.h>

#define DAYS_IN_WEEK            7         
#define MONTHS_IN_YEAR          12
#define DAYS_IN_LEAP_YEAR       366
#define DAYS_IN_NON_LEAP_YEAR   365
#define FIRST_GREGORIAN_DAY     4          /* Week day index Friday is 4 */
#define FIRST_GREGORIAN_DATE    1
#define FIRST_GREGORIAN_MONTH   9         /* Month index of October is 9 */
#define FIRST_GREGORIAN_YEAR    1582
#define MAX_SUPPORTED_YEAR      9999

#define CALENDAR_WEEK_ROWS      6
#define NON_VALID_DATE          0


enum day_in_week {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};

enum month_in_year { January, February, March, April, May, June,
                     July, August, September, October, November, December };


struct Month_Calendar{
        uint8_t  date [CALENDAR_WEEK_ROWS * DAYS_IN_WEEK];
};

struct Year_Calendar {
    struct Month_Calendar month[MONTHS_IN_YEAR];
};

extern const uint16_t days_in_month[MONTHS_IN_YEAR];
extern const char* const name_of_months[MONTHS_IN_YEAR];

extern const struct Year_Calendar* const generate_calendar_data(uint16_t);

#endif