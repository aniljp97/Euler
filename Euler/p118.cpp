#include "euler.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include "MyMethods.h"

// https://projecteuler.net/problem=118

/// <summary>
/// Returns the number of partitions of a the set where all the subsets are prime
/// </summary>
/// <param name="start">Keeps track of the set dividing index through the recursive stack</param>
/// <param name="prev">Saves the previously found subset in the recursive check of one set. The set does not count if the previous subset is greater than the next (to avoid duplicates, ex. {2,47,...} and {47,2,...})</param>
/// <param name="set">The full number set (never changed)</param>
/// <param name="res">result as a int passed by reference to make adding up simpler within recursive context</param>
void getNumSubsetCombos(int start, int prev, vector<int> set, int& res) {
	int subset = 0;

	for (; start < set.size(); start++) {
		subset *= 10;
		subset += set.at(start);
		//cout << subset;
		if (subset > prev && isPrime(subset)) {
			//cout << " prime" << endl;
			getNumSubsetCombos(start + 1, subset, set, res);
		}
		//cout << endl;
	}

	if (start == set.size() && subset > prev && isPrime(subset)) {
		//cout <<  "FIN: " << subset << endl;
		res++;
	}
}

void getCombinationsRecursive(vector<int> combo, vector<int> numsToAdd, int& res) {

	if (combo.size() == 2) {
		cout << combo[0] << combo[1] << "%" << endl;
	}

	if (numsToAdd.size() == 0 ) {
		/*for (int c : combo) {
			cout << c;
		}*/
		int lastNum = combo.back();
		if (lastNum != 4 && lastNum != 6 && lastNum != 8) {
			// Get each combination of subsets of the combo number

			int subsets = 0;
			getNumSubsetCombos(0, 0, combo, subsets);
			//cout << " - " << subsets << endl;
			res += subsets;
		}
		/*else {
			cout << endl;
		}*/
		return;
	}

	for (int i = 0; i != numsToAdd.size(); i++) {
		vector<int> allToAdd = numsToAdd;
		combo.push_back(numsToAdd.at(i));
		allToAdd.erase(allToAdd.begin() + i);
		getCombinationsRecursive(combo, allToAdd, res);
		combo.pop_back();
	}
}

int p118() {
	// iterate through all possible integers sets
	int res = 0;
	getCombinationsRecursive({}, { 1,2,3,4,5,6,7,8,9 }, res);
	return res;
}