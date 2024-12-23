#include <iostream>
#include <vector>
#include <unordered_map>
#include "../utils.h"
using namespace std;

int ROWS;
int COLS;
pair<int, int> currLocation;
vector<vector<char>> grid;
unordered_map<char, pair<int, int>> look = {
    {'^', {-1, 0}},
    {'v', {1, 0}},
    {'<', {0, -1}},
    {'>', {0, 1}},
};

bool validPoint(int x, int y)
{
    return x >= 0 && x < ROWS && y >= 0 && y < COLS;
}

void shift(vector<pair<int, int>> points, int xDir, int yDir)
{
    if (points.size() == 2)
    {
        return;
    }
    auto temp = points[0];
    char val = grid[temp.first][temp.second];
    grid[temp.first][temp.second] = '.';

    currLocation = {points[1].first, points[1].second};
    for (int i = 1; i < points.size(); i++)
    {
        auto curr = points[i];
        auto currVal = grid[curr.first][curr.second];
        // Here i have the before and after
        grid[curr.first][curr.second] = val;
        val = currVal;
    }
}

void move(int xDir, int yDir)
{
    int currX = currLocation.first;
    int currY = currLocation.second;
    int newX = currX + xDir;
    int newY = currY + yDir;

    // Move to open spot
    if (validPoint(newX, newY))
    {
        char look = grid[newX][newY];
        if (look == '.')
        {
            grid[currX][currY] = '.';
            grid[newX][newY] = '@';
            currLocation = {newX, newY};
        }
        else if (look == '#')
        {
            return;
        }
        else
        {
            vector<pair<int, int>> points;
            points.push_back({currX, currY}); 
            points.push_back({newX, newY}); 

            int checkX = newX;
            int checkY = newY;

            while (true) {
                checkX += xDir;
                checkY += yDir;
                
                if (!validPoint(checkX, checkY)) break;
                
                char checkCell = grid[checkX][checkY];
                if (checkCell == '#') break; 
                if (checkCell == '.') {
                    points.push_back({checkX, checkY});
                    shift(points, xDir, yDir);
                    break;
                }
                if (checkCell == 'O') {
                    points.push_back({checkX, checkY});
                    continue;
                }
            }
        }
    }
}

void conductMovements(vector<string> directions)
{
    for (int i = 0; i < directions.size(); i++)
    {
        string dir = directions[i];
        for (int j = 0; j < dir.size(); j++)
        {
            auto p = look[dir[j]];
            cout << "Direction: " << dir[j] << endl;
            move(p.first, p.second);
            for (int i = 0; i < ROWS; i++)
            {
                for (int j = 0; j < COLS; j++)
                {
                    cout << grid[i][j];
                }
                cout << endl;
            }
            cout << "Current Location : " << currLocation.first << " " << currLocation.second << endl;
        }
    }
    cout << currLocation.first << "," << currLocation.second << endl;
}

void calculateSum() {
    long long sum = 0;
    for ( int i = 0; i < ROWS; i++ ) {
        for ( int j = 0; j < COLS; j++ ) {
            if ( grid[i][j] == 'O' ) {
                sum += (100 * i) + j;
            }
        }
    }
    cout << "Sum of Coordinates: " << sum << endl;
}

void part1()
{
    string file_path = "./input.txt";
    vector<string> lines = read_file(file_path);
    vector<string> gridInput;
    vector<string> directions;

    int index = 0;
    // Parse Input
    while (true)
    {
        if (lines[index] == "")
        {
            break;
        }
        gridInput.push_back(lines[index]);
        index++;
    }
    for (int i = index + 1; i < lines.size(); i++)
    {
        directions.emplace_back(lines[i]);
    }

    // Create Grid
    ROWS = gridInput.size();
    COLS = gridInput[0].size();
    grid = vector<vector<char>>(ROWS, vector<char>(COLS));

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            grid[i][j] = gridInput[i][j];
            if (grid[i][j] == '@')
            {
                currLocation = {i, j};
            }
        }
    }

    conductMovements(directions);
    calculateSum();
}

void part2()
{
    string file_path = "./input.txt";
    vector<string> lines = read_file(file_path);

    for (const string &s : lines)
    {
        cout << s << endl;
    }
}

int main()
{
    part1();
    // part2();
}
