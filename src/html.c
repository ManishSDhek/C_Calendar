#include <stdio.h>
#include <string.h>

#include "html_pub.h"
#include "html_priv.h"
#include "calendar_pub.h"
#include "calendar_calc_pub.h"


/**************************************************************************************************
* NAME :            enum error_code generate_calendar_html (uint16_t year, const char* const file_name)
* DESCRIPTION :     Function to genrate the static HTML file - Creates HTML header and calendar
* INPUTS :
*           uint16_t            year        Year
*           char*               filename    HTML file name
* OUTPUTS :
*           enum error_code     return      Error code
****************************************************************************************************/
enum error_code generate_calendar_html (uint16_t year, const char* const file_name) {

    FILE *fPtr;  
    fPtr =fopen(file_name,"w");

    // check if HTML file created
    if (fPtr != NULL) {

        // insert HTML head
        fprintf  (fPtr, "<html>\n");
        fprintf  (fPtr, "<head><title>ETAS Gregorian Calendar</title></head>\n");

        // insert HTML body
        fprintf  (fPtr, "<body>\n");
        fprintf  (fPtr, "<h1 style=\"text-align: center\">Gregorian Calendar : Manish S Dhek</h1> <br/>\n");
        fprintf  (fPtr, "<table border='1'  bordercolor='#666' cellspacing='10' cellpadding='0' align=center>\n");
        fprintf  (fPtr, "<tr>\n");

        // insert past year calendar tables
        fprintf  (fPtr, "<td>\n");
        write_year_calendar(fPtr, year-1);
        fprintf  (fPtr, "</td>\n");

        // insert past year current tables
        fprintf  (fPtr, "<td>\n");
        write_year_calendar(fPtr, year);
        fprintf  (fPtr, "</td>\n");

        // insert future year current tables
        fprintf  (fPtr, "<td>\n");
        write_year_calendar(fPtr, year+1);
        fprintf  (fPtr, "</td>\n");

        fprintf  (fPtr, "</tr>\n");
        fprintf  (fPtr, "</table>\n");
        fprintf  (fPtr, "</body>\n");
        fprintf  (fPtr, "</html>\n");
        
        fclose(fPtr);

        return NO_ERROR;
    }
    else {
        return FILE_WRITE_ERROR;
    }
}

/**************************************************************************************************
* NAME :            void write_year_calendar (FILE * const fPtr, uint16_t year)
* DESCRIPTION :     Function to genrate HTML code for the given year 
* INPUTS :
*           uint16_t        year        Year Number
*           FILE *          fPtr        pointer to the output HTML file
* OUTPUTS :
*           FILE* fPtr is updated for HTML code
****************************************************************************************************/
void write_year_calendar (FILE * const fPtr, uint16_t year) {

    // get the year calendar data
    const struct Year_Calendar* const pCalendarData = generate_calendar_data(year);

    // insert the HTML code for year calendar table
    fprintf  (fPtr, "<table border='1'  bordercolor='#666' cellspacing='10' cellpadding='0' align=left width='33%%'>\n");
    fprintf  (fPtr, "<td colspan=1 align=center bgcolor='#FFFF00'>  </td>\n"); 
    fprintf  (fPtr, "<td colspan=2 align=center bgcolor='#FFFF00'><font size='3' face='Tahoma'><b>%d</b></td>\n", year); 
    fprintf  (fPtr, "<td colspan=1 align=center bgcolor='#FFFF00'>  </td>\n");

    // inster months tables
    create_months_tables(fPtr, pCalendarData);

    fprintf  (fPtr, "</table>\n");

}

/**************************************************************************************************
* NAME :            void create_months_tables (FILE * const fPtr, const struct Year_Calendar* const pCalendarData)
* DESCRIPTION :     Function to genrate HTML code for all months tables 
* INPUTS :
*       PARAMETERS :
*           struct Year_Calendar*         pCalendarData        pointer to Year's calender data
*           FILE *          fPtr        pointer to the output HTML file
* OUTPUTS :
*           FILE* fPtr is updated for HTML code
****************************************************************************************************/
void create_months_tables (FILE * const fPtr, const struct Year_Calendar* const pCalendarData) {

    enum month_in_year month_index;

    // Insert HTML code for first row Jan, Feb, March, April
    fprintf  (fPtr, "<tr>\n");
    for (month_index=January; month_index <= April; month_index++) {

        fprintf  (fPtr, "<td>\n");
        write_month_table(fPtr, month_index, &(pCalendarData->month[month_index]));
        fprintf  (fPtr, "</td>\n");
    }
    fprintf  (fPtr, "</tr>\n");

    // Insert HTML code for second row May, June, July, August
    fprintf  (fPtr, "<tr>\n");
    for (month_index=May; month_index <= August; month_index++) {

        fprintf  (fPtr, "<td>\n");
        write_month_table(fPtr, month_index, &(pCalendarData->month[month_index]));
        fprintf  (fPtr, "</td>\n");
    }
    fprintf  (fPtr, "</tr>\n");

    // Insert HTML code for third row September, October, November, December
    fprintf  (fPtr, "<tr>\n");
    for (month_index=September; month_index <= December; month_index++) {

        fprintf  (fPtr, "<td>\n");
        write_month_table(fPtr, month_index, &(pCalendarData->month[month_index]));
        fprintf  (fPtr, "</td>\n");
    }
    fprintf  (fPtr, "</tr>\n");
}

/**************************************************************************************************
* NAME :            void write_month_table(FILE* const fPtr, enum month_in_year month_index, const struct Month_Calendar* const pMonthData)
* DESCRIPTION :     Function to genrate HTML code for each month tables 
* INPUTS :
*       PARAMETERS :
*           enum month_in_year            month_index   Index for month number  
*           struct Month_Calendar*        pMonthData    pointer to month's calender data
*           FILE *          fPtr        pointer to the output HTML file
* OUTPUTS :
*           FILE* fPtr is updated for HTML code
****************************************************************************************************/
void write_month_table(FILE* const fPtr, enum month_in_year month_index, const struct Month_Calendar* const pMonthData) {

    uint8_t index;
    enum day_in_week weekday_index;

    // Insert HTML code for month header
    fprintf  (fPtr, "<table cellspacing='0' cellpadding='0' align=center  border='4' width='100%%'>\n");
    fprintf  (fPtr, "<td  align=center bgcolor='lightgreen'>  </td>\n"); 
    fprintf  (fPtr, "<td colspan=5 align=center bgcolor='lightgreen'><font size='3' face='Tahoma'><b>%s</b></td>\n", 
              name_of_months[month_index]); 
    fprintf  (fPtr, "<td  align=center bgcolor='lightgreen'>  </td>\n");

    fprintf  (fPtr, "<tr>\n");  
    fprintf  (fPtr, "<td align=center bgcolor='lightgray'><font size='3' face='Tahoma'>M</font></td>\n"); 
    fprintf  (fPtr, "<td align=center bgcolor='lightgray'><font size='3' face='Tahoma'>T</font></td>\n"); 
    fprintf  (fPtr, "<td align=center bgcolor='lightgray'><font size='3' face='Tahoma'>W</font></td>\n"); 
    fprintf  (fPtr, "<td align=center bgcolor='lightgray'><font size='3' face='Tahoma'>T</font></td>\n"); 
    fprintf  (fPtr, "<td align=center bgcolor='lightgray'><font size='3' face='Tahoma'>F</font></td>\n"); 
    fprintf  (fPtr, "<td align=center bgcolor='lightyellow'><font size='3' face='Tahoma'>S</font></td>\n");
    fprintf  (fPtr, "<td align=center bgcolor='lightsalmon'><font size='3' face='Tahoma'>S</font></td>\n"); 
    fprintf  (fPtr, "</tr>\n");

    // loop over all the week rows in month's table
    for(index=0; index< CALENDAR_WEEK_ROWS; index++) {
        fprintf  (fPtr, "<tr>\n");
        // Insert HTML code for each date cell
        for(weekday_index=Monday; weekday_index<DAYS_IN_WEEK; weekday_index++) {
            write_date_data(fPtr, pMonthData->date[(index*DAYS_IN_WEEK) + weekday_index]);   
        }
        fprintf  (fPtr, "</tr>\n");
    }

    fprintf  (fPtr, "</table>\n");
}

/**************************************************************************************************
* NAME :            void write_date_data (FILE* const fPtr, uint8_t date)
* DESCRIPTION :     Function to genrate HTML code for each date cell 
* INPUTS :
*       PARAMETERS :
*           uint8_t         date          date number  
*           FILE *          fPtr        pointer to the output HTML file
* OUTPUTS :
*           FILE* fPtr is updated for HTML code
****************************************************************************************************/
void write_date_data (FILE* const fPtr, uint8_t date) {

    // check if no date value
    if(NON_VALID_DATE == date)
        fprintf  (fPtr, "<td align=center><font size='2' face='Tahoma'> <br></font></td>\n");
    else
        fprintf  (fPtr, "<td align=center><font size='2' face='Tahoma'>%d<br></font></td>\n", date); 
}