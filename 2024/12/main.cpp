#include "../utils.h"
#include <queue>
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

  cout << "Region Area: " << region.size() << symbol << endl;
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

  // Side Calculation
  set<tuple<int, int,int>> distinctSides;
  int sides = 0;
  for ( int i = 0; i < 4; i++ ) {
    queue<tuple<int,int,int>> q;
    for ( auto const &[a,b] : region ) {
        int newX = a + dir[i].first;
        int newY = b + dir[i].second;
        
        // Case for a distinct side
        if ( distinctSides.find({a,b,i}) == distinctSides.end() && ( outsideGrid(newX, newY) || ( validPoint(newX, newY) && grid[newX][newY] != symbol ) ) ) {
          cout << a << " " << b << " " << i << " " << grid[a][b] << endl;
          sides += 1;
          q.push( {a,b,i} );

        // Continuously motion on a distinct side
        while( !q.empty() ) {
          auto point = q.front();
          q.pop();
          if ( distinctSides.find(point) != distinctSides.end() ) {
            continue;
          } else {
            distinctSides.insert(point);
          }

          // Direction is up or down
          if ( i == 2 || i == 3 ) {
            int x = get<0>(point);
            int y = get<1>(point);
            int direction = get<2>(point);
            int left = y - 1;
            int right = y + 1;

            int looking = x + dir[i].first;

            // Make sure the left or right block is the same symbol and the dir we are looking is an edge
            if ( validPoint(x, left) && grid[x][left] == symbol ) {
              if ( outsideGrid(looking, left) || (validPoint(looking,left) && grid[looking][left] != symbol) ) {
                q.push( {x, left, direction} );
              }
            }
            if ( validPoint(x, right) && grid[x][right] == symbol ) {
              if ( outsideGrid(looking, right) || (validPoint(looking,right) && grid[looking][right] != symbol) ) {
                q.push( {x, right, direction} );
              }
            }
            
          } else { // Direction is left or right
            int x = get<0>(point);
            int y = get<1>(point);
            int direction = get<2>(point);
            int up = x - 1;
            int down = x + 1;

            int looking = y + dir[i].second;

            // Make sure the up or down block is the same symbol and the dir we are looking is an edge
            if ( validPoint(up, y) && grid[up][y] == symbol ) {
              if ( outsideGrid(up, looking) || (validPoint(up,looking) && grid[up][looking] != symbol) ) {
                q.push( {up, y, direction} );
              }
            }
            if ( validPoint(down, y) && grid[down][y] == symbol ) {
              if ( outsideGrid(down, looking) || (validPoint(down,looking) && grid[down][looking] != symbol) ) {
                q.push( {down, y, direction} );
              }
            }

          }
        }
      }
    }
  }
  return region.size() * sides; 
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

