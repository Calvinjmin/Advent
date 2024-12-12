#include "../utils.h"
#include <iostream>
#include <set>
using namespace std;

vector<vector<char>> grid;
set<pair<int, int>> visited;
int ROWS;
int COLS;

vector<pair<int, int>> dir = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

bool validPoint(int x, int y) {
  return x >= 0 && x < ROWS && y >= 0 && y < COLS;
}

bool outsideGrid(int x, int y) {
  return x < 0 || x >= ROWS || y < 0 || y >= COLS;
}

int bfs(int x, int y, char symbol) {
  queue<pair<int, int>> q;
  q.push({x, y});
  visited.insert({x, y});

  vector<pair<int, int>> region;

  while (!q.empty()) {
    auto [a, b] = q.front();
    region.push_back({a, b});
    q.pop();
    for (int i = 0; i < 4; i++) {
      int newX = a + dir[i].first;
      int newY = b + dir[i].second;
      if (validPoint(newX, newY) && grid[newX][newY] == symbol &&
          visited.find({newX, newY}) == visited.end()) {
        q.push({newX, newY});
        visited.insert({newX, newY});
      }
    }
  }

  cout << "Region Area: " << region.size() << endl;
  int permi = 0;
  for (auto const &[a, b] : region) {
    for (int i = 0; i < 4; i++) {
      int newX = a + dir[i].first;
      int newY = b + dir[i].second;
      if (outsideGrid(newX, newY)) {
        permi += 1;
      } else if (validPoint(newX, newY) && grid[newX][newY] != symbol) {
        permi += 1;
      }
    }
  }
  cout << "Perimeter: " << permi << endl;
  return region.size() * permi;
}

int bfs2(int x, int y, char symbol) {
  queue<pair<int, int>> q;
  q.push({x, y});
  visited.insert({x, y});

  vector<pair<int, int>> region;

  while (!q.empty()) {
    auto [a, b] = q.front();
    region.push_back({a, b});
    q.pop();
    for (int i = 0; i < 4; i++) {
      int newX = a + dir[i].first;
      int newY = b + dir[i].second;
      if (validPoint(newX, newY) && grid[newX][newY] == symbol &&
          visited.find({newX, newY}) == visited.end()) {
        q.push({newX, newY});
        visited.insert({newX, newY});
      }
    }
  }

  cout << "Region Area: " << region.size() << endl;
  set<pair<int, int>> distinctSides;
  for (auto const &[a, b] : region) {
    for (int i = 0; i < 4; i++) {
      int newX = a + dir[i].first;
      int newY = b + dir[i].second;
      if (outsideGrid(newX, newY)) {
        // check up or down
        if ( i == 0 || i == 1 ) {
            distinctSides.insert({b,i});
        }
        else {
            distinctSides.insert({a,i});
        }
      } else if (validPoint(newX, newY) && grid[newX][newY] != symbol) {
        // check up or down
        if ( i == 0 || i == 1 ) {
            distinctSides.insert({b,i});
        }
        else {
            distinctSides.insert({a,i});
        }
      }
    }
  }

    for ( auto pair : distinctSides ) {
        cout << pair.first << " " << pair.second << endl;
    }
    cout << "Sides: " << distinctSides.size() << endl;
  return region.size() * distinctSides.size();
}

void part1() {
  string file_path = "./input.txt";
  vector<string> lines = read_file(file_path);

  ROWS = lines.size();
  COLS = lines[0].size();

  grid = vector<vector<char>>(ROWS, vector<char>(COLS));

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      grid[i][j] = lines[i][j];
    }
  }

  int answer = 0;
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (visited.find({i, j}) == visited.end()) {
        answer += bfs(i, j, grid[i][j]);
      }
    }
  }
  cout << "Total Price: " << answer << endl;
}

void part2() {
  string file_path = "./input.txt";
  vector<string> lines = read_file(file_path);

  ROWS = lines.size();
  COLS = lines[0].size();

  grid = vector<vector<char>>(ROWS, vector<char>(COLS));

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      grid[i][j] = lines[i][j];
    }
  }

  int answer = 0;
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (visited.find({i, j}) == visited.end()) {
        answer += bfs2(i, j, grid[i][j]);
      }
    }
  }
  cout << "Total Price: " << answer << endl;
}

int main() {
  // part1();
  part2();
}
