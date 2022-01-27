/*
 * Remi Andruccioli <remi.andruccioli@gmail.com>
 * Gilbert Andruccioli
 * June 2018
 * 
 * This program is in the public domain.
 * 
 * Usage: perpetual-calendar <year> [<month>]
 * 
 * This program will generate a calendar for a given year and month.
 * If no month is provided, the program will generate a calendar for the whole
 * given year.
 * 
 * The original formula was given to me by my grandfather Gilbert Andruccioli
 * who used to implement it in BASIC on the TI-99/4A computer. We reimplemented
 * it in C and added some features.
 * This program takes into account the actual formula to determine leap years
 * (instead of just dividing by 4).
 * https://en.wikipedia.org/wiki/Leap_year
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>

static const int daysInMonth[] = {
  31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static const char* months[] = {
  "January",
  "February",
  "March",
  "April",
  "May",
  "June",
  "July",
  "August",
  "September",
  "October",
  "November",
  "December"
};

static const int referenceYearFirstDays[] = {
  0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5
};

static const char *weekDays[] = {
  "mon",
  "tue",
  "wed",
  "thu",
  "fri",
  "sat",
  "sun"
};

static const int firstDayOfMonth = 1;

static const int referenceYear = 1703;

static const int fieldWidth = 4;

static void
die(const char * const fmt, ...)
{
  va_list args;
  
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);

  exit(EXIT_FAILURE);
}

static int
allCharsDigit(const char * const s)
{
  const char * c;

  for (c = s; *c != '\0'; ++c) {
    if (isspace(*c)) {
      continue;
    }

    if (!isdigit(*c)) {
      return 0;
    }
  }

  return 1;
}

static int 
isDivisible(const int year, const int i)
{
  return (year % i) == 0;
}

static int
testLeapYear(const int year)
{
  return (isDivisible(year, 4) && !isDivisible(year, 100)) || (isDivisible(year, 400));  
}

static int
countLeapYears(const int startYear, const int endYear, int * const isLeapYear)
{
  int i;
  int totalLeapYears = 0;

  for (i = startYear; i < endYear; ++i) {
    if (testLeapYear(i)) {
      ++totalLeapYears;
    }
  }

  *isLeapYear = testLeapYear(endYear);  

  return totalLeapYears;
}

static int
obtainArgs(int * const month, int * const year, const int argc, char * argv[]) {
  char *s;

  if (3 != argc && 2 != argc) {        
    die("Usage: %s <year> [<month>]\n", argv[0]);
  }

  s = argv[1];
  if (!allCharsDigit(s)) {
    die("The year must be all digits.\n");
  }

  *year = atoi(s);

  if (*year < referenceYear) {
    die("The year must be at least %d.\n", referenceYear);
  }

  if (3 == argc) {
    s = argv[2];
    if (!allCharsDigit(s)) {
      die("The month must be all digits.\n");
    }

    *month = atoi(s);
    if (*month < 1 || *month > 12) {
      die("The month must be between 1 and 12.\n");
    }

    return 1;
  } 

  return 0;
}

static int
printMonth(int month, int year, int offset, int isLeapYear) {
  int lastDayInMonth; 
  int i;

  fprintf(stdout, "%s %d\n", months[month -1], year);

  for (i = 0; i < 7; ++i) {
    fprintf(stdout, "%-*s", fieldWidth, weekDays[i]);
  }

  fputc('\n', stdout);

  for (i = 0; i < offset; ++i) {
    fprintf(stdout, "%*s", fieldWidth, "");
  }

  lastDayInMonth = daysInMonth[month - 1];

  if (2 == month && isLeapYear) {
    lastDayInMonth++;
  }

  for (i = firstDayOfMonth; i <= lastDayInMonth; ++i) {
    fprintf(stdout, "%-*d", fieldWidth, i);

    if (7 == ++offset) {
      if (i != lastDayInMonth) {
        fputc('\n', stdout);
      }

      offset = 0;
    }
  }

  fputc('\n', stdout);
    
  return offset;
}

int
main(int argc, char *argv[])
{
  int month;
  int year;
  int sum;
  int offset;
  int i;
  int isLeapYear;
  const int withMonth = obtainArgs(&month, &year, argc, argv);
  
  if(!withMonth) {
    month = 1;  
  }

  sum = year - referenceYear;
  sum += referenceYearFirstDays[month - 1];
  sum += countLeapYears(referenceYear, year, &isLeapYear);

  if (isLeapYear && withMonth && (month > 2)) {
    ++sum;
  }
  
  offset = sum % 7;

  if (withMonth) {
    printMonth(month, year, offset, isLeapYear);
  } else {
    for (i = 1; i <= 12; ++i) {
      offset = printMonth(i, year, offset, isLeapYear);
      fputc('\n', stdout);
    }
  }
    
  exit(EXIT_SUCCESS);
}
