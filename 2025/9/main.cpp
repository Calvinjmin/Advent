#include <iostream>
#include <algorithm>
#include <map>
#include <functional>
#include "../../utils/utils.h"
using namespace std;

vector<pair<unsigned long long, unsigned long long>> red_tiles;
unsigned long long rows;
unsigned long long cols;


void printGrid( vector<vector<char>>& grid ) {
    for ( auto r : grid ) {
        for ( auto c: r ) {
            cout << c;
        }
        cout << endl;
    }
}

bool validRec( pair<unsigned long long, unsigned long long> a, pair<unsigned long long, unsigned long long> b, vector<vector<char>> & grid ) {
    unsigned long long minCol = min(a.first, b.first);
    unsigned long long maxCol = max(a.first, b.first);
    unsigned long long minRow = min(a.second, b.second);
    unsigned long long maxRow = max(a.second, b.second);

    /* Define Rectangle
        minRow, minCol       maxRow, minCol


        minRow, maxCol       maxRow,maxCol
    */

    // Check each corner in only its 2 relevant directions
    vector<pair<pair<int,int>, vector<pair<int,int>>>> cornerChecks = {
        {make_pair(minRow, minCol), {{-1, 0}, {0, -1}}},
        {make_pair(minRow, maxCol), {{-1, 0}, {0, 1}}},
        {make_pair(maxRow, minCol), {{1, 0}, {0, -1}}},
        {make_pair(maxRow, maxCol), {{1, 0}, {0, 1}}}
    };

    for ( const auto& [point, directions] : cornerChecks ) {
        if ( grid[point.first][point.second] == 'X' ||  grid[point.first][point.second] == '#') continue;

        int currRow = point.first;
        int currCol = point.second;

        for ( const auto& dir: directions ) {
            int newRow = currRow + dir.first;
            int newCol = currCol + dir.second;

            // Keep going until we hit 'X' or '#'
            bool hitBoundary = false;
            while ( newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols ) {
                if ( grid[newRow][newCol] == 'X' || grid[newRow][newCol] == '#' ) {
                    hitBoundary = true;
                    break;
                }
                newRow += dir.first;
                newCol += dir.second;
            }

            // If we exited the loop without hitting X or #, we went out of bounds without a boundary
            if ( !hitBoundary ) {
                return false;
            }
        }
    }
    return true;
}

void part1() {
    string file_path = "./input.txt";
    vector<string> lines = read_file(file_path);

    rows = -1;
    cols = -1;

    for ( const string& s: lines ) {
        vector<string> loc = split(s, ",");
        cols = max(cols, stoull(loc[0]) + 1); 
        rows = max(rows, stoull(loc[1]) + 1); 
        red_tiles.emplace_back(make_pair(stoull(loc[0]), stoull(loc[1]))); 
    }

    // Brute Force
    unsigned long long maxArea = 0;
    for ( int i = 0; i < red_tiles.size(); i++ ) {
        for ( int j = 0; j < red_tiles.size(); j++ ) {
            if ( i != j ) {
                auto a = red_tiles[i];
                auto b = red_tiles[j];

                // Cannot use ABS with unsigned long long
                unsigned long long width = (b.first > a.first ? b.first - a.first : a.first - b.first) + 1;
                unsigned long long height = (b.second > a.second ? b.second - a.second : a.second - b.second) + 1;
                maxArea = max(maxArea, width * height);
            }
        }
    }

    cout << "Answer: " << maxArea << endl;
}

// Answer too high - 4623431865
void part2() {
    string file_path = "./input.txt";
    vector<string> lines = read_file(file_path);

    rows = 0;
    cols = 0;

    for ( const string& s: lines ) {
        vector<string> loc = split(s, ",");
        cols = max(cols, stoull(loc[0]));
        rows = max(rows, stoull(loc[1]));
        red_tiles.emplace_back(make_pair(stoull(loc[0]), stoull(loc[1]))); 
    }

    rows += 2;
    cols += 2;
    vector<vector<char>> grid;
    grid.resize(rows);
    for (int i = 0; i < rows; i++) {
        grid[i].resize(cols, '.'); 
    }

    for ( pair<int,int> p : red_tiles ) {
        grid[p.second][p.first] = '#'; 
    }

    // 1. Create a border around the tiles
    //  - loop through all the points and find straight line edges
    for ( int i = 0; i < red_tiles.size(); i++ ) {
        auto p1 = red_tiles[i]; 
        for ( int j = i + 1; j < red_tiles.size(); j++ ) {
            auto p2 = red_tiles[j];

            // Boarder has to be on a straight line
            if ( p1.first == p2.first ) {
                // same col 
                int minRow = min(p1.second, p2.second);
                int maxRow = max(p1.second, p2.second);

                for ( int row = minRow; row <= maxRow; row++ ) {
                    if ( grid[row][p1.first] == '.' ) {
                        grid[row][p1.first] = 'X';
                    }
                }
            } else if ( p1.second == p2.second ) {
                // same row 
                int minCol = min(p1.first, p2.first);
                int maxCol = max(p1.first, p2.first);

                // Mark all points between as border
                for ( int col = minCol; col <= maxCol; col++ ) {
                    if ( grid[p1.second][col] == '.' ) {
                        grid[p1.second][col] = 'X';
                    }
                }
            }
        }
    }
    // printGrid(grid);

    // 2. Find the max area of a recetangle that exists within the boarder
    unsigned long long maxArea = 0;

    for ( int i = 0; i < red_tiles.size(); i++ ) {
        // cout << i << " out of " << red_tiles.size() << endl;
        for ( int j = 0; j < red_tiles.size(); j++ ) {
            if ( i != j ) {
                auto a = red_tiles[i];
                auto b = red_tiles[j];

                unsigned long long width = (b.first > a.first ? b.first - a.first : a.first - b.first) + 1;
                unsigned long long height = (b.second > a.second ? b.second - a.second : a.second - b.second) + 1;

                // Optimize
                if ( width * height <= maxArea ) { 
                    continue;
                }

                if ( validRec(a,b, grid) ) {
                    maxArea = max(maxArea, width * height);
                }
            }
        }
    }

    cout << "Answer: " << maxArea << endl;

}

int main() {
    //part1();
    part2();
}
