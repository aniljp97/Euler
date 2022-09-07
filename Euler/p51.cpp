#include <format>
#include <iostream>
#include <list>

#include "MyMethods.h"
#include "euler.h"

// https://projecteuler.net/problem=51

int p51() {
    int prevNumSize = 2;
    list<string> replacePositions = {};
    for (int i = 101; i < 1000002; i += 2) { // only iterating through odd numbers since an even number cannot be prime
        string iStr = to_string(i);

        // every time the num amount of digits increase, save all the possible ways the replace the num of that size
        // (represented by binary string, where 1 are the digit being replaced. The binary is also one size less than the actual number
        //  because replacing the last digit would never get us the answer so the last digit is ignored)
        if ((int)iStr.length() > prevNumSize) {
            prevNumSize++;
            replacePositions.clear();
            for (int binComb = 1; binComb < pow(2, prevNumSize - 1); binComb++) {
                replacePositions.push_front(getBinary(binComb, prevNumSize - 1));
            }
        }

        // For the current num and each digit replacement combination, check if 8 primes are created from all 10 replacements (aka that number family)
        for (string repPos : replacePositions) {
            int primeFamSize = 0;
            int firstPrime = 0;
            for (int replaceDigit = 0; replaceDigit < 10; replaceDigit++) {
                // replace num and check it for prime
                string newInt = iStr;
                for (int numInd = 0; numInd < prevNumSize - 1; numInd++) {
                    if (repPos[numInd] == '1') {
                        newInt[numInd] = char(replaceDigit + '0');
                    }
                }
                int intInt = stoi(newInt);
                if (newInt[0] != '0' && isPrime(intInt)) {
                    if (primeFamSize == 0) // we save the first prime of each family because that is the value we want
                        firstPrime = intInt;
                    primeFamSize++;
                }
                if (primeFamSize == 8) {
                    return firstPrime;
                }
            }
        }
    }

    return 0;
}
