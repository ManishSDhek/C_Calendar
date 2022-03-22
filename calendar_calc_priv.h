#ifndef CALENDAR_CALC_PRIV_H_
#define CALENDAR_CALC_PRIV_H_

#include <stdint.h>

static void init_calendar_data (struct Year_Calendar* const);
static void populate_calendar_data (struct Year_Calendar* const, uint16_t);
static enum day_in_week poulate_month_data (struct Month_Calendar * const, uint8_t, enum day_in_week);
static uint8_t get_days_in_month (uint16_t , enum month_in_year);
static enum day_in_week get_first_weekday(uint16_t);
static inline uint8_t is_leapyear(uint16_t);

#endif