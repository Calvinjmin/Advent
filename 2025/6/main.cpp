#include "../../utils/utils.h"
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
using namespace std;

vector<vector<unsigned long long>> equations;

void append_values(const int &eq, const unsigned long long &value) {
  while (equations.size() <= eq) {
    equations.push_back({});
  }
  equations[eq].push_back(value);
}

vector<string> parse_input(const string &input) {
  vector<string> ret;

  // Edge case of input spaces
  int left = 0;
  while (left < input.size() && input.at(left) == ' ')
    left++;

  int right = left + 1;
  while (right < input.size()) {
    if (input.at(right) != ' ') {
      right++;
      continue;
    }

    ret.push_back(input.substr(left, right - left));

    // Move pointers over
    left = right + 1;
    while (left < input.size() && input.at(left) == ' ')
      left++;

    right = left + 1;
  }

  if (left < input.size()) {
    ret.push_back(input.substr(left));
  }

  return ret;
}

void parse_columns(const vector<string> &lines, int max_width,
                   vector<string> &operators) {
  int col = max_width - 1;
  while (col >= 0) {
    // edge case: if the entire value is all spaces
    bool all_spaces = true;
    for (int row = 0; row < lines.size(); row++) {
      if (lines[row][col] != ' ') {
        all_spaces = false;
        break;
      }
    }

    if (all_spaces) {
      col--;
      continue;
    }

    vector<unsigned long long> problem_numbers;
    string op = "";

    while (col >= 0) {

      // Space column means end of this equation
      bool is_space_col = true;
      for (int row = 0; row < lines.size(); row++) {
        if (lines[row][col] != ' ') {
          is_space_col = false;
          break;
        }
      }

      if (is_space_col)
        break;

      // Extract number from this column (top-to-bottom)
      string number_str = "";
      for (int row = 0; row < lines.size() - 1; row++) {
        if (lines[row][col] != ' ') {
          number_str += lines[row][col];
        }
      }

      // Get operator from last row
      if (lines[lines.size() - 1][col] != ' ') {
        op = lines[lines.size() - 1][col];
      }

      // Add number if we found digits
      if (!number_str.empty()) {
        problem_numbers.push_back(stoull(number_str));
      }

      col--;
    }

    if (!problem_numbers.empty() && !op.empty()) {
      // reverse the number - nifty helper function
      reverse(problem_numbers.begin(), problem_numbers.end());

      // append values and operations to complete
      int eq_idx = equations.size();
      for (const auto &num : problem_numbers) {
        append_values(eq_idx, num);
      }
      operators.push_back(op);
    }
  }
}

void part1() {
  string file_path = "./input.txt";
  vector<string> lines = read_file(file_path);

  unsigned long long answer = 0;

  // Append values in equation to vector
  for (int i = 0; i < lines.size() - 1; i++) {
    vector<string> values = parse_input(lines[i]);
    for (int j = 0; j < values.size(); j++) {
      append_values(j, stoull(values[j]));
    }
  }

  // Perform operations
  vector<string> operations = parse_input(lines[lines.size() - 1]);

  for (int i = 0; i < operations.size(); i++) {
    const string &op = operations[i];
    auto values = equations[i];
    if (op == "*") {
      answer += accumulate(values.begin(), values.end(), 1ULL,
                           multiplies<unsigned long long>());
    } else {
      answer += accumulate(values.begin(), values.end(), 0ULL,
                           plus<unsigned long long>());
    }
  }

  cout << "Answer: " << answer << endl;
}

// idea: find the max width then work top-down on col to parse input and number
// parse in a similar fashion to part 1 for numbers, just use reverse() function to help
void part2() {
  string file_path = "./input.txt";
  vector<string> lines = read_file(file_path);

  unsigned long long answer = 0;

  // Find max width
  int max_width = 0;
  for (int i = 0; i < lines.size(); i++) {
    max_width = max(max_width, (int)lines[i].length());
  }

  // Pad lines with spaces to match max width
  for (int i = 0; i < lines.size(); i++) {
    while (lines[i].length() < max_width) {
      lines[i] += ' ';
    }
  }

  // Parse columns and populate equations
  vector<string> operators;
  parse_columns(lines, max_width, operators);

  for (int i = 0; i < operators.size(); i++) {
    const string &op = operators[i];
    vector<unsigned long long> values = equations[i];
    if (op == "*") {
      answer += accumulate(values.begin(), values.end(), 1ULL,
                           multiplies<unsigned long long>());
    } else {
      answer += accumulate(values.begin(), values.end(), 0ULL,
                           plus<unsigned long long>());
    }
  }

  cout << "Answer: " << answer << endl;
}

int main() {
  // part1();
  // part2();
}
