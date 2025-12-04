#include <iostream>
#include "../../utils/utils.h"
using namespace std;

vector<vector<char>> grid;
int rows;
int cols;
const char& paper = '@';

vector<pair<int,int>> neighbors = {
    {-1,-1}, {-1,0}, {-1,1},
    {0,-1}, {0,1},
    {1,-1}, {1,0}, {1,1}
};

bool valid_point( int x, int y ) {
    return (x > -1 && y > -1) && ( x < rows && y < cols);
}

int traverse_grid_part1() {
    int valid_papers = 0;
    for ( int r = 0; r < rows; r++ ) {
        for ( int c = 0; c < cols; c++ ) {
            if ( grid[r][c] != paper ) continue;

            // Traverse neighbors
            int count = 0;
            for ( const auto& dir: neighbors ) {
                if ( valid_point(r+dir.first, c+dir.second) && grid[r+dir.first][c+dir.second] == paper ) count++;
            }

            if ( count < 4 ) {
                cout << "(" << r << ", " << c << ") " << count << endl;
                valid_papers++;
            }

        }
    }

    return valid_papers;
}

int traverse_grid_part2() {
    int valid_papers = 0;
    vector<pair<int,int>> troubled_points;

    for ( int r = 0; r < rows; r++ ) {
        for ( int c = 0; c < cols; c++ ) {
            if ( grid[r][c] != paper ) continue;

            // Traverse neighbors
            int count = 0;
            for ( const auto& dir: neighbors ) {
                if ( valid_point(r+dir.first, c+dir.second) && grid[r+dir.first][c+dir.second] == paper ) count++;
            }

            if ( count < 4 ) {
                troubled_points.push_back({r,c});
                valid_papers++;
            }

        }
    }

    for ( const auto& point: troubled_points ) {
        grid[point.first][point.second] = '.';
    }

    return valid_papers;
}

void part1() {
    string file_path = "./input.txt";
    vector<string> lines = read_file(file_path);

    rows = lines.size();
    cols = lines[0].length();

    for ( const string& row: lines ) {
        vector<char> row_vect;
        for ( const auto& point: row ) {
            row_vect.push_back(point);
        }
        grid.push_back(row_vect);
    }
    cout << "Answer: " << traverse_grid_part1();
}

void part2() {
    string file_path = "./input.txt";
    vector<string> lines = read_file(file_path);

    rows = lines.size();
    cols = lines[0].length();

    for ( const string& row: lines ) {
        vector<char> row_vect;
        for ( auto point: row ) {
            row_vect.push_back(point);
        }
        grid.push_back(row_vect);
    }

    int answer = 0;
    int run = traverse_grid_part2();
    while ( run > 0 ) {
        answer += run;
        run = traverse_grid_part2();
    }

    cout << "Answer: " << answer << endl;
}

int main() {
    //part1();
    //part2();
}
