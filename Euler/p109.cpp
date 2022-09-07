#include "euler.h"
#include <map>
#include <set>
#include <iostream>

// https://projecteuler.net/problem=109

multimap<int, string> allHits;
multimap<int, string> doubleHits;

void initializeHitCollections() {
	// singles
	for (int i = 1; i <= 20; i++) { // every single and triples (on inner red/green ring)
		allHits.insert({ i, "S" + to_string(i) });
		allHits.insert({ i * 3, "T" + to_string(i) });
	}
	allHits.insert({ 25, "S25" }); // outer bullseye

	// doubles
	for (int i = 1; i <= 20; i++) { // every double on outer red/green ring
		doubleHits.insert({ i * 2, "D" + to_string(i) });
		allHits.insert({ i * 2, "D" + to_string(i) });
	}
	doubleHits.insert({ 50, "D25" }); // inner bullseye
	allHits.insert({ 50, "D25" });
}

int getNumCheckoutCombinations(int score) {
	int combinations = 0;
	// first, we can start with one combination if there is a double that equals the score
	if (doubleHits.count(score) > 0) {
		combinations++;
	}

	set<string> sortedFirst2Hits; // we need the set to make sure we are not including duplicate combos, and we only need to check the first 2 hits for triple hit finishes

	for (auto allIt = allHits.begin(); allIt != allHits.end(); allIt++) {
		// first get all the combinations that can be done with 2 hits
		int value = allIt->first;
		if (value <= score - 2) {
			if (doubleHits.count(score - value) > 0) {
				combinations++;
			}
		}

		// then look for combos that take 3 hits
		// we get all 2 hit less than the score - 2, then check if a double fits in for the third hit
		for (auto allIt2 = allHits.begin(); allIt2 != allHits.end(); allIt2++) {
			int value2 = allIt2->first;
			int first2Total = value + value2;
			// a combination can be added if the third hit fits as a double and the 2 shots have not already been done in the opposite order
			if (doubleHits.count(score - first2Total) > 0 && sortedFirst2Hits.count(allIt2->second + allIt->second) == 0) {
				sortedFirst2Hits.insert(allIt->second + allIt2->second);
				combinations++;
			}
		}
	}

	return combinations;
}

int p109() {
	initializeHitCollections();
	int combinations = 0;
	for (int score = 2; score < 100; score++) {
		combinations += getNumCheckoutCombinations(score);
	}

	return combinations;
}