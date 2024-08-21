#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

using namespace std;

int main() {
  // Input.txt is the input given from Advent Calendar
  ifstream file("./1/input.txt");
  if (!file.is_open()) {
    std::cerr << "Error: Could not open the file!" << std::endl;
    return 1;
  }

  // Read in the Input and store as a string
  stringstream buffer;
  buffer << file.rdbuf();

  int level = 0;
  unordered_map<char, int> dict;
  dict['('] = 1;
  dict[')'] = -1;

  bool first = false;
  int index = 1;

  // Loop through the input string and add/subtract
  // the value of the paren
  for (char ch : buffer.str()) {
    level += dict[ch];

    // Finding Basement Position
    if (!first && level < 0) {

      cout << "Index: " << index << endl;
      first = true;
    }
    index += 1;
  }

  cout << "Answer: " << level << endl;
}
