# Perpetual Calendar in C

Usage: `perpetual-calendar <year> [<month>]`

This program will generate a calendar for a given year and month on stdout.  
If no month is provided, the program will generate a calendar for the whole
given year.  

This program takes into account the actual formula to determine leap years
(instead of just dividing by 4). See https://en.wikipedia.org/wiki/Leap_year

## Building
GCC is hard-coded in the makefile, but any C89 compiler can do the job.  
This program only depends on libc.__
To build, simply use `make`. It will generate an executable in the same
directory.

## License

This program is in the public domain.
