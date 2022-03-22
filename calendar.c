#include <stdio.h>
#include <string.h>
#include <math.h>

#include "calendar_pub.h"
#include "calendar_priv.h"
#include "calendar_calc_pub.h"
#include "html_pub.h"

/**************************************************************************************************
* NAME :            int main (int argc, char* argv[])
* DESCRIPTION :     Main function to genrate calendar for 1582 until 9999
* INPUTS :
*           argv[1]        year        Year [1582,9999]
*           argv[2]        fileName    Name of the outfile (ex. 2020.html)
* NOTE  :
*           How to compile : gcc -o calendar calendar.c html.c calendar_calc.c
*           How to Execute  : ./calendar 2020 2020.html
****************************************************************************************************/
int main (int argc, char* argv[]) {

    uint16_t input_year = UINT16_MAX;
    enum error_code error;
    
    // check if correct number of argument is provided
    if (IN_MAX_ARGS == argc) {

        // check if the year argument is less than 4 character
        if(strlen(argv[YEAR_ARG_INDEX]) <= MAX_YEAR_CHAR_LENGTH) {
            // get the entered year data
            input_year = convert_to_int(argv[YEAR_ARG_INDEX], strlen(argv[YEAR_ARG_INDEX]));
        }

        // check if the input year is within the range
        if ( (input_year >= FIRST_GREGORIAN_YEAR) && (input_year <= MAX_SUPPORTED_YEAR)) {

            // call the function to generate calendar html file
            error = generate_calendar_html (input_year, argv[FILENAME_ARG_INDEX]);
        }
        else {
            error = IP_NOT_IN_RANGE_ERROR; 
        }     
    }
    else {
        error = INVALID_NO_ARG_ERROR;
    }

    // report log
    log_errors(error);

    return 0;
}

/**************************************************************************************************
* NAME :            void log_errors (enum error_code error)
* DESCRIPTION :     Utility function to report output log
* INPUTS :
*          enum error_code      error        Error code
* OUTPUTS :
*          Log output is displayed in the command prompt
****************************************************************************************************/
void log_errors (enum error_code error) {

    // check the error type
    switch (error)
    {
        case NO_ERROR:
            printf ("Calendar HTML has been successfully created\n");
            break;
        case INVALID_NO_ARG_ERROR:
            printf("ERROR 01: Invalid number of arugment provided\n");
            printf("INFO  01: Example : \"./calendar 2020 2020.html\" \n");
            break;
        case IP_NOT_IN_RANGE_ERROR:
            printf ("ERROR 02: The valid year should be between 1582 & 9999\n");
            break;
        case FILE_WRITE_ERROR:
            printf ("ERROR 03: Calendar HTML creation failed\n");
            break;
        default:
            break;
    }
}

/**************************************************************************************************
* NAME :            uint16_t convert_to_int (const char* const data, uint16_t len)
* DESCRIPTION :     Utility function to convert string into integer
* INPUTS :
*          char*      data        pointer to string
*          uint16_t   len         length of the string
* OUTPUTS :
*          uint16_t   return      interger value of string
****************************************************************************************************/
uint16_t convert_to_int (const char* const data, uint16_t len) {

    uint16_t num = 0;
    uint8_t index;

    for(index = 0; index < len; index ++) {
        
        // check in input is a number
        if((data[index] >= '0') && (data[index] <= '9')) {
            // subtracting 48 because the numbers in ASCII starts at 48
            num += ((uint8_t)data[index] - 48) * pow(10, ((len - 1) - index));
        }
        else {
            // if any of character is not digit: return 0
            return 0;
        }
    }
    return num;
}