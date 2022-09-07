#include "euler.h"
#include <iostream>
#include <string>
#include "MyMethods.h"

// https://projecteuler.net/problem=118

//////////////////
/// UNFINISHED ///
//////////////////


bool uniqueCharacters(string str)
{
	int checker = 0;

	for (int i = 0; i < str.length(); i++) {

		int bitAtIndex = str[i] - '0';

		// if that bit is already set in
		// checker, return false
		if ((checker & (1 << bitAtIndex)) > 0) {
			return false;
		}

		// otherwise update and continue by
		// setting that bit in the checker
		checker = checker | (1 << bitAtIndex);
	}

	// no duplicates encountered, return true
	return true;
}

int numPrimeCombos(int i) {
	int res = 0;
	string i_str = to_string(i);

	char setLastChar = i_str.back();
	if (setLastChar == '8' || setLastChar == '6' || setLastChar == '4') { // if the last digit is an even number (other than 2), the sets last digit will be a non-prime
		return 0;
	}

	if (setLastChar == 2) { // when the last digit is 2 the only way the last digit can be a prime is as 2. So the digit 2 will need to be by itself
		string i_wo_two = i_str.substr(0, i_str.length() - 1);
	}

	// because the loop below is using bit shifting, we can't start on 0 so we can just check if the full number is prime
	if (isPrime(i)) {
		res++;
	}

	// using iterating all of the possible comma placement to make a set through 1 byte a binary, a 1 representing a comma
	for (unsigned short int plcmnt = 1; plcmnt <= 255;) {
		string str_plc = getBinary(plcmnt, 8);
		int prev_c_ind = 0;
		for (int c_ind = 1; c_ind <= 9; c_ind++) {
			if (str_plc[c_ind - 1] == '1' || c_ind == 9) {
				int sub_num = stoi(i_str.substr(prev_c_ind, c_ind));
				if (!isPrime(sub_num)) {
					plcmnt <<= 1;
					goto continuePlacement;
				}

				if (c_ind == 9) {
					res++;
				}

				prev_c_ind = c_ind;
			}
		}

		plcmnt++;

	continuePlacement:
		continue;
	}
}

int p118() {
	int res = 0;

	// iterate through all possible integers sets
	int ind = 8;
	for (int i = 123456789; i <= 987654321;) {
		string i_str = to_string(i);

		// do prime check here
		if (i_str[ind] == 8) {
			ind--;
		}

		swap(i_str[ind], i_str[ind + 1]); // maybe figure something with swapping
	}


	return res;
}