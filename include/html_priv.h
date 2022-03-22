#ifndef HTML_PRIV_H_
#define HTML_PRIV_H_

#include <stdio.h>
#include <stdint.h>
#include "calendar_calc_pub.h"

static void write_year_calendar(FILE * const, uint16_t);
static void create_months_tables(FILE * const, const struct Year_Calendar * const);
static void write_month_table(FILE * const , enum month_in_year, const struct Month_Calendar * const);
static void write_date_data (FILE * const, uint8_t);

#endif