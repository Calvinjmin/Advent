#include "../utils.h"
#include <Eigen/Dense>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;
using namespace Eigen;

class ClawMachine {
private:
  pair<int, int> buttonA;
  pair<int, int> buttonB;
  pair<long, long> prize;

public:
  void parseLine(string val, string line) {
    vector<string> lineVals = split(line, " ");

    string xVal, yVal;
    if (val == "Prize") {
      xVal = lineVals[1].substr(lineVals[1].find("X=") + 2);
      yVal = lineVals[2].substr(lineVals[2].find("Y=") + 2);
    } else {
      xVal = lineVals[2].substr(lineVals[2].find("+") + 1);
      yVal = lineVals[3].substr(lineVals[3].find("+") + 1);
    }

    // Parse into the objects
    if (val == "A") {
      buttonA = {stoi(xVal), stoi(yVal)};
    } else if (val == "B") {
      buttonB = {stoi(xVal), stoi(yVal)};
    } else {
      // prize = {stoi(xVal), stoi(yVal)};
      prize = {stoi(xVal) + 10000000000000, stoi(yVal) + 10000000000000};
    }

    cout << prize.first << " " << prize.second << endl;
  }

  int solve() {
    int minZ = INT_MAX;
    int bestA = 0, bestB = 0;

    for (int a = 0; a <= 100; ++a) {
      for (int b = 0; b <= 100; ++b) {
        if (buttonA.first * a + buttonB.first * b == prize.first &&
            buttonA.second * a + buttonB.second * b == prize.second) {
          int z = 3 * a + b;
          if (z < minZ) {
            minZ = z;
            bestA = a;
            bestB = b;
          }
        }
      }
    }

    if (minZ != INT_MAX) {
      return minZ;
    }
    return 0;
  }

  // answer too low - 14348780
  // value is wrong - 1296705344
  long long solveMatrix() {
    long det =
        buttonA.first * buttonB.second - buttonA.second * buttonB.first;

    if (det == 0) {
      cout << "No unique solution found (determinant is 0)!" << endl;
      return 0;
    }


    // Matrices Definition
    long  x =
        (prize.first * buttonB.second - prize.second * buttonB.first) / det;
    long y =
        (buttonA.first * prize.second - buttonA.second * prize.first) / det;

    if (buttonA.first * x + buttonB.first * y == prize.first &&
        buttonA.second * x + buttonB.second * y == prize.second) {

      long long z = 3 * x + y;

      cout << "Solution found!" << endl;
      cout << "a = " << x << endl;
      cout << "b = " << y << endl;
      cout << "z = " << z << endl;

      return z;
    }

    cout << "No valid solution found!" << endl;
    return 0;
  };
};

void part1() {
  string file_path = "./input.txt";
  vector<string> lines = read_file(file_path);

  int tokensNeeded = 0;
  for (int i = 0; i < lines.size(); i += 4) {
    ClawMachine systems;
    systems.parseLine("A", lines[i]);
    systems.parseLine("B", lines[i + 1]);
    systems.parseLine("Prize", lines[i + 2]);
    tokensNeeded += systems.solve();
  }
  cout << "Tokens Needed : " << tokensNeeded << endl;
}

void part2() {
  string file_path = "./input.txt";
  vector<string> lines = read_file(file_path);

  long long tokensNeeded = 0;
  for (int i = 0; i < lines.size(); i += 4) {
    ClawMachine systems;
    systems.parseLine("A", lines[i]);
    systems.parseLine("B", lines[i + 1]);
    systems.parseLine("Prize", lines[i + 2]);
    tokensNeeded += systems.solveMatrix();
  }
  cout << "Tokens Needed : " << tokensNeeded << endl;
}

int main() {
  // part1();
  part2();
}
