.PHONY: all
all: perpetual-calendar

perpetual-calendar: perpetual-calendar.c
	gcc -Wall -Wextra -Werror -std=c89 -O3 perpetual-calendar.c -o perpetual-calendar

.PHONY: clean
clean:
	rm -rfv perpetual-calendar
