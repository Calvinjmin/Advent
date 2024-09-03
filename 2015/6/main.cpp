#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

enum Action { TURN_ON, TURN_OFF, TOGGLE };

struct Instruction {
  Action action;
  int x1, y1, x2, y2;
};

vector<Instruction> parseInstructions(const string &filename) {
  ifstream file(filename);
  string line;
  vector<Instruction> instructions;
  regex re("(turn on|turn off|toggle) (\\d+),(\\d+) through (\\d+),(\\d+)");
  smatch match;

  while (getline(file, line)) {
    if (regex_search(line, match, re)) {
      Instruction inst;
      if (match[1] == "turn on") {
        inst.action = TURN_ON;
      } else if (match[1] == "turn off") {
        inst.action = TURN_OFF;
      } else {
        inst.action = TOGGLE;
      }
      inst.x1 = stoi(match[2]);
      inst.y1 = stoi(match[3]);
      inst.x2 = stoi(match[4]);
      inst.y2 = stoi(match[5]);
      instructions.push_back(inst);
    }
  }
  return instructions;
}

void processInstructionsPart1(const vector<Instruction> &instructions) {
  const int GRID_SIZE = 1000;
  bool grid[GRID_SIZE][GRID_SIZE] = {{false}};

  for (const auto &inst : instructions) {
    for (int x = inst.x1; x <= inst.x2; ++x) {
      for (int y = inst.y1; y <= inst.y2; ++y) {
        if (inst.action == TURN_ON) {
          grid[x][y] = true;
        } else if (inst.action == TURN_OFF) {
          grid[x][y] = false;
        } else if (inst.action == TOGGLE) {
          grid[x][y] = !grid[x][y];
        }
      }
    }
  }

  // Output the result
  int count = 0;
  for (int x = 0; x < GRID_SIZE; ++x) {
    for (int y = 0; y < GRID_SIZE; ++y) {
      if (grid[x][y]) {
        ++count;
      }
    }
  }
  cout << "Number of lights on: " << count << endl;
}

void processInstructionsPart2(const vector<Instruction> &instructions) {
  const int GRID_SIZE = 1000;
  int grid[GRID_SIZE][GRID_SIZE] = {{0}};

  for (const auto &inst : instructions) {
    for (int x = inst.x1; x <= inst.x2; ++x) {
      for (int y = inst.y1; y <= inst.y2; ++y) {
        if (inst.action == TURN_ON) {
          grid[x][y] += 1;
        } else if (inst.action == TURN_OFF) {
          grid[x][y] = max(grid[x][y] - 1, 0);
        } else if (inst.action == TOGGLE) {
          grid[x][y] += 2;
        }
      }
    }
  }

  int brightness = 0;
  for (int x = 0; x < GRID_SIZE; x++) {
    for (int y = 0; y < GRID_SIZE; y++) {
      brightness += grid[x][y];
    }
  }

  cout << "Final Brightness: " << brightness << endl;
}

int main() {
  string filename = "./6/instructions.txt";
  vector<Instruction> instructions = parseInstructions(filename);
  processInstructionsPart1(instructions);
  processInstructionsPart2(instructions);
  return 0;
}
