#include "euler.h"

// The integer 36 has a peculiar property: it is a perfect square, and is also the sum of the integers from 1 through 8. 
// The next such number is 1225 which is 352, and the sum of the integers from 1 through 49. 
// Find the next number that is a perfect square and also the sum of a series 1...n.
// This next number may be greater than 32767. You may use library functions that you know of, (or mathematical formulas) to make your program run faster.
// It is also possible to write this program using for - loops to determine if a number is a perfect square or a sum of a series.

void addToWhileLower(int* sum, int* n, int limit) {
    while (*sum < limit) {
        *sum += (*n)++;
    }
}

int perfectSquareSum() {
    int n = 1;
    int series_sum = 0;

    for (int i = 1226; i < INT32_MAX; i++) {
        int perfSquare = i * i;
        addToWhileLower(&series_sum, &n, perfSquare);
        if (series_sum == perfSquare) {
            break;
        }
    }
    return series_sum;
}