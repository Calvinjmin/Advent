#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/*
 * Sorts the sides and returns them in a vector<int> from smallest to biggest
 */
vector<int> sort_sides(int length, int width, int height) {
  vector<int> ans;
  ans.push_back(length);
  ans.push_back(width);
  ans.push_back(height);
  sort(ans.begin(), ans.end());
  return ans;
}

/*
 * Calculates the Wrapping Paper Size
 */
int wrapping_paper_size(int length, int width, int height) {
  int side1 = (2 * length * width);
  int side2 = (2 * width * height);
  int side3 = (2 * height * length);
  int minSide = min((length * width), min((width * height), (length * height)));
  return side1 + side2 + side3 + minSide;
}

/*
 * Calculates the Ribbon Size
 */
int ribbon_size(int length, int width, int height) {
  int bow_size = length * width * height;
  vector<int> sorted_sides = sort_sides(length, width, height);
  int wrap = (2 * sorted_sides[0]) + (2 * sorted_sides[1]);
  return bow_size + wrap;
}

/*
 * Parses through each string and breaks it up by 'x' to get vector<int> of each
 * dimension
 */
vector<int> get_dimensions(string dimensions) {
  vector<int> dim;

  // While loop to grab values
  int left = 0;
  for (int right = 1; right <= dimensions.length(); right++) {
    if (right == dimensions.length() || dimensions[right] == 'x') {
      int length = right - left;
      dim.push_back(stoi(dimensions.substr(left, length)));
      left = right + 1;
    }
  }

  return dim;
}

int main() {
  ifstream file("./2/input.txt");
  string line;

  if (!file.is_open()) {
    cerr << "Could not open file" << endl;
    return 1;
  }

  vector<int> dim;
  int runningCount = 0;
  int ribbonCount = 0;
  while (getline(file, line)) {
    dim = get_dimensions(line);
    runningCount += wrapping_paper_size(dim[0], dim[1], dim[2]);
    ribbonCount += ribbon_size(dim[0], dim[1], dim[2]);
  }
  file.close();

  cout << "FINAL WRAPPING PAPER NUMBER: " << runningCount << endl;
  cout << "FINAL RIBBON COUNT: " << ribbonCount << endl;
}