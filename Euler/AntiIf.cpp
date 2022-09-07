#include "euler.h"
#include <iostream>
#include <vector>

// For every number from 1 to n (a positive integer), print a line to the console based on these rules:
// if n is a multiple of 3, print "Gar"
// if n is a multiple of 5, print "Min"
// if n is a multiple of 3 and 5, print "GarMin"
// if n is none of the above, print n

// For this problem a solution is already given and uses 3 if-statements in total. It is the most obvious and straight-forward solution.

// The challenge is to find more ways to complete it by using less total if-statements. One with 2 if-statements, one with 1 if-statements, and one with 0 if-statements.
// else-ifs, tenary operaters and switch case statements also count as using a if-statement
// Hint: look towards the output for ideas

void givenSolution(int n) {
	for (int i = 1; i <= n; i++) {
		if (i % 3 == 0 && i % 5 == 0) {
			cout << "GarMin" << endl;
		}
		else if (i % 5 == 0) {
			cout << "Min" << endl;
		}
		else if (i % 3 == 0) {
			cout << "Gar" << endl;
		}
		else {
			cout << i << endl;
		}
	}
}

// recognized that the strings go in pattern every 15
void only2Ifs(int n) {
	vector<string> garsmins{ "Gar", "Min", "Gar", "Gar", "Min", "Gar", "GarMin" };
	int garsmins_ind = 0;
	for (int i = 1; i <= n; i++) {
		if (i % 3 == 0 || i % 5 == 0) {
			cout << garsmins[garsmins_ind] << endl;
			if (++garsmins_ind >= garsmins.size()) {
				garsmins_ind = 0;
			}
			continue;
		}

		cout << i << endl;
	}
}

// Since it is in such a pattern that the numbers follow as well, can print out individually each line every 15
// Before printing to the console, the one if statement can check if we have gone over n and remove the lines that go over n
void only1If(int n) {
	for (int i = 1; i <= n;) {
		vector<string> lines;
		
		lines.push_back(to_string(i)); i++;
		lines.push_back(to_string(i)); i++;
		lines.push_back("Gar"); i++;
		lines.push_back(to_string(i)); i++;
		lines.push_back("Min"); i++;
		lines.push_back("Gar"); i++;
		lines.push_back(to_string(i)); i++;
		lines.push_back(to_string(i)); i++;
		lines.push_back("Gar"); i++;
		lines.push_back("Min"); i++;
		lines.push_back(to_string(i)); i++;
		lines.push_back("Gar"); i++;
		lines.push_back(to_string(i)); i++;
		lines.push_back(to_string(i)); i++;
		lines.push_back("GarMin"); i++;

		if (i > n + 1) {
			for (int j = 0; j < i - 1 - n; j++) {
				lines.pop_back();
			}
		}

		for (string l : lines) {
			cout << l << endl;
		}
	}
}


// to remove the one if statement from above, we can get the of lines that need to be removed by substracting n from i. If its negative there is nothing to remove so...
// we can convert the negative numbers to zero by using the std::max function and comparing i - n to 0.
void noIfs(int n) {
	for (int i = 1; i <= n;) {
		vector<string> lines;

		lines.push_back(to_string(i)); i++;
		lines.push_back(to_string(i)); i++;
		lines.push_back("Gar"); i++;
		lines.push_back(to_string(i)); i++;
		lines.push_back("Min"); i++;
		lines.push_back("Gar"); i++;
		lines.push_back(to_string(i)); i++;
		lines.push_back(to_string(i)); i++;
		lines.push_back("Gar"); i++;
		lines.push_back("Min"); i++;
		lines.push_back(to_string(i)); i++;
		lines.push_back("Gar"); i++;
		lines.push_back(to_string(i)); i++;
		lines.push_back(to_string(i)); i++;
		lines.push_back("GarMin"); i++;

	    int lines_to_remove = max(i - 1 - n, 0);		
		for (int j = 0; j < lines_to_remove; j++) {
			lines.pop_back();
		}

		for (string l : lines) {
			cout << l << endl;
		}
	}
}

void antiIf() {
	noIfs(100);
}