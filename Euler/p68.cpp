#include "euler.h"
#include <vector>
#include <algorithm>

// https://projecteuler.net/problem=68

char itoc(int i) {
	return (char)(i + '0');
}

int ctoi(char c) {
	return c - '0';
}

vector<int> sToIntVector(string s) {
	vector<int> vec;
	for (char c : s) {
		vec.push_back(ctoi(c));
	}
	return vec;
}

class MagicGon {
	int gon_size;

	// comparator for strings in descending order
	bool stringOrderComparator(string s1, string s2) {
		return s1.size() > s2.size();
	}

	// Note no matter what the size of the gon, the a line will consist of 3 numbers
	// also note that in the returned string, a char that is greater than 9 will show its corresponding char above 9 in ACSII value
	// Input num as zero if the number is unknown, assuming only one of the num are being defined
	vector<string> getLineCombinations(vector<int> used_nums, int line_total, int first_num = 0, int second_num = 0, int third_num = 0) {
		vector<string> combos;

		string combo = "   ";
		int given_num;
		if (first_num != 0) {
			combo[0] = itoc(first_num);
			given_num = first_num;
		}
		else if (second_num != 0) {
			combo[1] = itoc(second_num);
			given_num = second_num;
		}
		else {
			combo[2] = itoc(third_num);
			given_num = third_num;
		}
		// next number can be any num less than (line total) - (first num) and isnt in the used_nums and isn't the first number and less than or equal to the max num of the gon
		for (int next_num = 1; (next_num < line_total - given_num) && next_num <= gon_size * 2; next_num++) {
			if (find(used_nums.begin(), used_nums.end(), next_num) == used_nums.end() && next_num != given_num) {
				// last number (line total) - (first num) - (second num) must not be a used_num as well and isn't the first or second number and less than or equal to the max num of the gon
				int last_num = line_total - given_num - next_num;
				if (find(used_nums.begin(), used_nums.end(), last_num) == used_nums.end() && last_num != given_num && last_num != next_num && last_num <= gon_size * 2) {
					if (first_num != 0) {
						combo[1] = itoc(next_num);
						combo[2] = itoc(last_num);
					}
					else if (second_num != 0) {
						combo[0] = itoc(next_num);
						combo[2] = itoc(last_num);
					}
					else if (third_num != 0) {
						combo[0] = itoc(next_num);
						combo[1] = itoc(last_num);
					}
					combos.push_back(combo);
				}
			}
		}
		return combos;
	}

public:
	MagicGon(int size) {
		gon_size = size;
	}

	string maxStringWithLargestNumOnEndNode() {
		int largest_num = gon_size * 2;
		vector<string> unorderedStrings;
		// Check for all possible line totals which from (largest num + 3) to (largest num * 3 - 3)
		for (int line_total = largest_num + 3; line_total <= largest_num * 3 - 3; line_total++) {
			vector<string> stringsOfTotal;
			for (string start_line : getLineCombinations({}, line_total, largest_num)) {
				stringsOfTotal.push_back(start_line);
			}

			// go through the remainder of lines that need to be generated other than the last one
			for (int i = 1; i < gon_size - 1; i++) {
				// for each current string, generate the next line and add the added to string
				int stringsSizeBeforeAddingTo = stringsOfTotal.size();
				for (int str_ind = 0; str_ind < stringsSizeBeforeAddingTo; str_ind++) {
					string cur_str = stringsOfTotal.at(str_ind);
					vector<int> used_nums = sToIntVector(cur_str.substr(0, cur_str.length() - 1));
					vector<string> next_line_combos = getLineCombinations(used_nums, line_total, 0, ctoi(cur_str.back()));
					for (string next_line : next_line_combos) {
						stringsOfTotal.push_back(cur_str + next_line);
					}
				}
				// remove all the smaller string worked of beforing adding
				stringsOfTotal.erase(stringsOfTotal.begin(), stringsOfTotal.begin() + stringsSizeBeforeAddingTo);
			}

			// for each string check that the last num to add and complete the last line of the gon is not an already used num and a valid number, remove if not
			for (int str_ind = 0; str_ind < stringsOfTotal.size(); str_ind++) {
				string * cur_str = &(stringsOfTotal[str_ind]);
				int third_num_of_line = ctoi((*cur_str)[1]);
				int second_num_of_line = ctoi((*cur_str).back());
				int last_num = line_total - third_num_of_line - second_num_of_line;
				if ((*cur_str).find(itoc(last_num)) == string::npos && last_num > 0 && last_num <= largest_num) {
					*cur_str = *cur_str + to_string(last_num) + to_string(second_num_of_line) + to_string(third_num_of_line);
				}
				else {
					stringsOfTotal.erase(stringsOfTotal.begin() + str_ind--);
				}
			}

			unorderedStrings.insert(unorderedStrings.end(), stringsOfTotal.begin(), stringsOfTotal.end());
		}

		// order strings starting from the group of three with the numerically lowest external node
		for (auto& s : unorderedStrings) {
			// get the min digit of each third char starting from the first char (which represents the external nodes) and that is our starting point so shift that index to the beginning of the string
			int min_digit_index = 0;
			for (int i = 3; i < s.length(); i+= 3) {
				if (s[min_digit_index] > s[i]) {
					min_digit_index = i;
				}
			}

			s = s.substr(min_digit_index) + s.substr(0, min_digit_index);
		}

		sort(unorderedStrings.begin(), unorderedStrings.end());
		string max_string = unorderedStrings.back();

		// last thing to do is convert any chars that represent more than 9 to its proper number in the string. (ex. 10 would currently be represented by a ':')
		for (int s_ind = 0; s_ind < max_string.length(); s_ind++) {
			int char_int = ctoi(max_string[s_ind]);
			if (char_int > 9) {
				string intStr = to_string(char_int);
				max_string.replace(s_ind, 1, intStr);
				s_ind += intStr.length() - 1;
			}
		}
		return max_string;
	}
};

string p68() {
	MagicGon magic5Gon(5);
	string str = magic5Gon.maxStringWithLargestNumOnEndNode();

	return str;
}