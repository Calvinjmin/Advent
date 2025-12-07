#include "../../utils/utils.h"
#include "map"
#include "queue"
#include "set"
#include <iostream>
#include <utility>
using namespace std;

vector<vector<char>> grid;
queue<pair<int, int>> startingPoints;
set<pair<int, int>> splitters;
set<pair<int, int>> visited;
map<pair<int, int>, long long> memo;

bool validPoint(const int &x, const int &y) {
  return (x >= 0 && y >= 0) && (x < grid.size() && y < grid[0].size());
}

void printGrid() {
  for (auto r : grid) {
    for (auto p : r) {
      cout << p;
    }
    cout << endl;
  }
}

// BFS Approach - queue starting points and traverse down
// Do not revisit same locations
void part1() {
  string file_path = "./input.txt";
  vector<string> lines = read_file(file_path);

  int numSplits = 0;

  for (int i = 0; i < lines.size(); i++) {
    auto s = lines[i];
    vector<char> row;
    for (int j = 0; j < s.length(); j++) {
      auto c = s[j];
      if (c == 'S')
        startingPoints.push(make_pair(i, j));
      row.push_back(c);
    }
    grid.push_back(row);
  }

  while (!startingPoints.empty()) {
    int curr = startingPoints.size();
    for (int i = 0; i < curr; i++) {
      pair<int, int> p = startingPoints.front();
      startingPoints.pop();

      // Skip if already visited
      if (visited.count(p)) {
        continue;
      }
      visited.insert(p);

      // Look Down
      pair<int, int> downPoints = {p.first + 1, p.second};
      if (validPoint(downPoints.first, downPoints.second) &&
          !visited.count(downPoints)) {
        // check if split
        if (grid[downPoints.first][downPoints.second] == '^') {
          // check valid next to split
          if (validPoint(downPoints.first + 1, downPoints.second + 1)) {
            pair<int, int> rightDiag =
                make_pair(downPoints.first + 1, downPoints.second + 1);
            if (!visited.count(rightDiag)) {
              startingPoints.push(rightDiag);
            }
          }
          if (validPoint(downPoints.first + 1, downPoints.second - 1)) {
            pair<int, int> leftDiag =
                make_pair(downPoints.first + 1, downPoints.second - 1);
            if (!visited.count(leftDiag)) {
              startingPoints.push(leftDiag);
            }
          }
          splitters.insert(downPoints);
        } else {
          startingPoints.push(downPoints);
        }
      }
    }
  }

  cout << "Number of Splits: " << splitters.size() << endl;
}

long long dfs(int r, int c) {

  // Skip Case
  pair<int, int> pos = make_pair(r, c);
  if (memo.count(pos)) {
    return memo[pos];
  }

  int nr = r + 1, nc = c;

  // Base Case
  if (!validPoint(nr, nc)) {
    return 1;
  }

  long long result;
  if (grid[nr][nc] == '^') {
    long long left = 0, right = 0;

    if (validPoint(nr + 1, nc + 1)) {
      right = dfs(nr + 1, nc + 1);
    }

    if (validPoint(nr + 1, nc - 1)) {
      left = dfs(nr + 1, nc - 1);
    }

    result = left + right;
  } else {
    result = dfs(nr, nc);
  }

  memo[pos] = result;
  return result;
}

// DFS Approach - find all possible combinations of unique paths without other interference
void part2() {
  string file_path = "./input.txt";
  vector<string> lines = read_file(file_path);

  int startR = -1;
  int startC = -1;

  // Build grid and find starting position
  for (int i = 0; i < lines.size(); i++) {
    auto s = lines[i];
    vector<char> row;
    for (int j = 0; j < s.length(); j++) {
      auto c = s[j];
      if (c == 'S') {
        startR = i;
        startC = j;
      }
      row.push_back(c);
    }
    grid.push_back(row);
  }

  // Count total timelines using DFS
  long long totalTimelines = dfs(startR, startC);
  cout << "Total Timelines: " << totalTimelines << endl;
}

int main() {
  part1();
  part2();
}
