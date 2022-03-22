# C_Calendar
C Program to generate the calendar

Assumptions:
The first supported date is 1st Oct 1582
The last supported year is 9999
The name of HTML file is provided correctly with *.html extension
Optional CW requirement has not been implemented.


How to compile:    gcc -o calendar calendar.c html.c calendar_calc.c
How to Execute:    ./calendar 2020 2020.html



Code Overview:

The code is divided into the 3 C files.

calendar.c
calendar_priv.h
calendar_pub.h

This file contains the main function and performs the validation check on the inputs provided from the command line.

html.c
html_priv.h
html_pub.h

This file contains the code for the creating the output calendar html file with the HTML code.

calendar_calc.c
calendar_calc_priv.h
calendar_calc_pub.h

This file contains the main logic for the calculation of year specific calendar data values.
