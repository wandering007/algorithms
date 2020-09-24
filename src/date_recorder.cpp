#include <stdio.h>

int day, month, year;
int dayOfMonth() {
    switch (month) {
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;
        case 2:
            return (year % 100 ? year : year / 100) % 4 ? 28 : 29;
        default: {
            fprintf(stderr, "Illegal month!\n");
            return 0;  // Illegal month!
        }
    }
}
void update(int add) {
    day += add;
    while (day > dayOfMonth()) {
        day -= dayOfMonth();
        if (month != 12)
            month++;
        else {
            year++;
            month = 1;
        }
    }
    return;
}
