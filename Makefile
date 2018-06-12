.PHONY: all
all: perpetual-calendar

perpetual-calendar: perpetual-calendar.c
	gcc -Wall -Wextra -Werror -std=c89 -O2 perpetual-calendar.c -o perpetual-calendar

.PHONY: clean
clean:
	rm -rfv perpetual-calendar
