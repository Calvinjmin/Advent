#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
  ifstream file("./5/input.txt");
  string line;

  if (!file.is_open()) {
    cerr << "Could not open file" << endl;
    return 1;
  }

  int nice_string = 0;
  vector<char> vowels = {'a', 'e', 'i', 'o', 'u'};
  vector<string> bad_substrings = {"ab", "cd", "pq", "xy"};

  // Condition 1 - Contains 3 vowels
  // Condition 2 - Contains one letter that appears twice in a row
  // Condition 3 - Does not contain the bad substring
  int vowel_count;
  bool contains_dup;
  bool contains_bad;

  string sub = "";

  // Complexity - O(n) where n = number of characters
  while (getline(file, line)) {
    vowel_count = 0;
    contains_dup = false;
    contains_bad = false;

    int n = line.length();
    if (n < 3) {
      continue;
    }

    if (find(vowels.begin(), vowels.end(), line[0]) != vowels.end()) {
      vowel_count += 1;
    }

    for (int i = 1; i < n; i++) {
      sub = line.substr(i - 1, 2);

      // Condition 3
      if (find(bad_substrings.begin(), bad_substrings.end(), sub) !=
          bad_substrings.end()) {
        contains_bad = true;
        break;
      }

      // Condition 1
      if (find(vowels.begin(), vowels.end(), line[i]) != vowels.end()) {
        vowel_count += 1;
      }

      // Condition 2
      if (sub[0] == sub[1]) {
        contains_dup = true;
      }
    }

    if (contains_dup && !contains_bad && vowel_count > 2) {
      nice_string += 1;
    }
  }

  cout << "Number of Nice Strings: " << nice_string << endl;
}