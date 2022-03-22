#include <stdio.h>

#include "calendar_calc_pub.h"
#include "calendar_calc_priv.h"

// array for the days in month
const uint16_t days_in_month[MONTHS_IN_YEAR] = {31, 28, 31, 30, 
                                                31, 30, 31, 31, 
                                                30, 31, 30, 31 };
// array for the months names
const char* const name_of_months[MONTHS_IN_YEAR] = {"January", "February", "March", "April", 
                                                    "May", "June", "July", "August", 
                                                    "September", "October", "November", "December"};


/**************************************************************************************************
* NAME :            const struct Year_Calendar* const generate_calendar_data(uint16_t year)
* DESCRIPTION :     Function to genrate the year calendar data
* INPUTS :
*           uint16_t                   year        Year
* OUTPUTS :
*           struct Year_Calendar*     return      pointer to Year Calendar Data
****************************************************************************************************/
const struct Year_Calendar* const generate_calendar_data(uint16_t year) {

    // Create calendar data variable
    static struct Year_Calendar calendarData;

    // initialize calendar data
    init_calendar_data (&calendarData);
    // initialize calendar data for the specifc year
    populate_calendar_data(&calendarData, year);

    return &calendarData;
}

/**************************************************************************************************
* NAME :            void init_calendar_data (struct Year_Calendar* const pCalendarData)
* DESCRIPTION :     Function to intiaile the year calendar data to 0
* INPUTS :
*           struct Year_Calendar*     pCalendarData      pointer to Year Calendar Data
* OUTPUTS :
*           struct Year_Calendar is updated for the intitalized data
****************************************************************************************************/
void init_calendar_data (struct Year_Calendar* const pCalendarData) {

    enum month_in_year month_index;
    uint8_t date_index;

    // loop over all the months in year
    for (month_index = January; month_index < MONTHS_IN_YEAR; month_index++) {

        // loop over all the calendar days
        for(date_index = 0; date_index < (CALENDAR_WEEK_ROWS*DAYS_IN_WEEK); date_index++  ) {
            pCalendarData->month[month_index].date[date_index] = NON_VALID_DATE;
        }        
    }
}

/**************************************************************************************************
* NAME :            populate_calendar_data (struct Year_Calendar* const pCalendarData, uint16_t year)
* DESCRIPTION :     Function to populate the calendar data for a given year
* INPUTS :
*           struct Year_Calendar*     pCalendarData      pointer to Year Calendar Data
*           uint16_t                  year               Year
* OUTPUTS :
*           struct Year_Calendar* elemnets are updated for Year specifc calendar data 
****************************************************************************************************/
void populate_calendar_data (struct Year_Calendar* const pCalendarData, uint16_t year) {

    enum month_in_year month_index;
    enum day_in_week weekday_index;
    uint8_t month_days;

    // check if input year is greater than 1582 & less than equal to maximum supported year
    if((year > FIRST_GREGORIAN_YEAR) && (year <= MAX_SUPPORTED_YEAR)) {

        // get the first weekday of the year
        weekday_index = get_first_weekday (year);

        // loop over all the months
        for(month_index = January; month_index < MONTHS_IN_YEAR; month_index++) {

            // get the total number of days in month
            month_days = get_days_in_month (year, month_index);
            // poulate the month calendar data
            weekday_index = poulate_month_data(&(pCalendarData->month[month_index]), month_days,
                                               weekday_index);
        }
    }
    else if (FIRST_GREGORIAN_YEAR == year) {

        // First day of Gregorian Calendar is Friday, 1 October 1582
        weekday_index = FIRST_GREGORIAN_DAY;

        // loop over for the remaining months in 
        for(month_index = FIRST_GREGORIAN_MONTH; month_index < MONTHS_IN_YEAR; month_index++) {

            // get total number of days in month
            month_days = get_days_in_month (year, month_index);
            // poulate the month calendar data            
            weekday_index = poulate_month_data(&(pCalendarData->month[month_index]), month_days, 
                                               weekday_index);
        }
    }
    else {
        // Do nothing
    }

}

/**************************************************************************************************
* NAME :            enum day_in_week poulate_month_data (struct Month_Calendar* const Month_Calendar, 
*                                                        uint8_t month_days, enum day_in_week weekday_index)
* DESCRIPTION :     Function to populate the specif month calendar data for a given year
* INPUTS :
*           struct Month_Calendar*    Month_Calendar      pointer to Month Calendar Data
*           uint8_t                   month_days          Number of days in month
*           enum day_in_week          weekday_index       index for starting weekday for month
* OUTPUTS :
*           enum day_in_week          return              index for starting weekday of next month
*           struct Month_Calendar* elemnets are updated for Month specifc calendar data 
****************************************************************************************************/
enum day_in_week poulate_month_data (struct Month_Calendar* const pMonthData, uint8_t month_days,
                                     enum day_in_week weekday_index) {
                                        

    uint8_t index;

    // loop over all the days in month                              
    for (index = 0; index < month_days; index++) {    
        // populate the date information in the month array      
        pMonthData->date[index + weekday_index] = index + 1;
    }

    return  ((weekday_index+month_days)%DAYS_IN_WEEK);                                    
}

/**************************************************************************************************
* NAME :            uint8_t get_days_in_month (uint16_t year, enum month_in_year month_index)
* DESCRIPTION :     Function to populate the specif month calendar data for a given year
* INPUTS :
*           uint16_t                  year          Year
*           enum month_in_year        month_index   index for month of the year
* OUTPUTS :
*           uint8_t                   return        Total days in the month
****************************************************************************************************/
uint8_t get_days_in_month (uint16_t year, enum month_in_year month_index) {

    uint8_t month_days = 0; 

    // check if feberuary month days in a leap year
    if((February == month_index) && is_leapyear(year))
        // set the February month days to 29
        month_days += (days_in_month[month_index] + 1);
    else
        // set the February month days to 28
        month_days += days_in_month[month_index];    

    return month_days;
}

/**************************************************************************************************
* NAME :            enum day_in_week get_first_weekday(uint16_t year)
* DESCRIPTION :     Function to find the first weekday of specifc year
* INPUTS :
*           uint16_t                  year          Year
* OUTPUTS :
*           enum day_in_week          return        First weekday of year
****************************************************************************************************/
enum day_in_week get_first_weekday(uint16_t year) {

    // intialize total days with the number of calendar days in first Gregorian calendar year (Oct,1582)
    uint32_t total_days = days_in_month[October] + days_in_month[November] + days_in_month[December]; 
    // set the year index to next year of first Gregorian calendar year
    uint16_t year_index = FIRST_GREGORIAN_YEAR + 1;

    // loop over to calculate total number of days from 1/Oct/1582 until begin of given year
    while (year_index < year) {

        // check if leap year
        if(is_leapyear(year_index))
            // add 366 to total days
            total_days += DAYS_IN_LEAP_YEAR;
        else
            // add 366 to total day
            total_days += DAYS_IN_NON_LEAP_YEAR;

        year_index++;
    }

    // return the index of first weekday in given year 
    return ((total_days + FIRST_GREGORIAN_DAY)%DAYS_IN_WEEK);
}

/**************************************************************************************************
* NAME :            inline uint8_t is_leapyear(uint16_t year)
* DESCRIPTION :     Inline Function to check if the given year is a leap year
* INPUTS :
*           uint16_t          year          Year
* OUTPUTS :
*           uint8_t           return        1: Leap Year, 0: Non-Leap Year
****************************************************************************************************/
inline uint8_t is_leapyear(uint16_t year) { 

    // if year is divisible by 400 - Leap Year : return 1
    // else if year is divisible by 100 - Non Leap Year : return 0
    // else if year is divisible by 4 - Leap Year : return 1
    // else - Non Leap Year : return 0
    return   ((year%400)==0 ? 1 : ((year%100)==0 ? 0 : ((year%4)==0? 1 :0)));   
}