#include <cmath>
#include "MyMethods.h"

string getBinary(int n, int size)
{
    string res = "";
    while (n > 0) {
        if (n % 2 == 0) {
            res = "0" + res;
        }
        else {
            res = "1" + res;
        }
        n >>= 1;
    }
    while ((int)res.length() < size) {
        res = "0" + res;
    }
    return res;
}

string getBinary(int n)
{
    string res = "";
    while (n > 0) {
        if (n % 2 == 0) {
            res = "0" + res;
        }
        else {
            res = "1" + res;
        }
        n >>= 1;
    }
    return res;
}

// assuming it will not be feed a even number
bool isPrime(int num) {
    for (int i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0)
            return false;
    }
    return true;
}