#include <iostream>
#include <string>
#include <queue>
#include <set>
#include "../utils.h"

using namespace std;

int ROWS;
int COLS;
vector<vector<int>> grid;

vector<pair<int, int>> dir = {
    {0, -1}, // up
    {0, 1},  // down
    {-1, 0}, // left
    {1, 0}   // right
};

bool validPoint(int x, int y)
{
    return x >= 0 && x < ROWS && y >= 0 && y < COLS;
}

void part1()
{
    // DFS to find all possible routes from 0 to 9
    // For each value of 0, add to a vector
    // Pull from vector and append to a queue
    // Queue should have a tuple<int,int, int val>
    // If there is a valid path, then add plus 1
    string file_path = "./input.txt";
    vector<string> lines = read_file(file_path);

    ROWS = lines.size();
    COLS = lines[0].size();
    grid = vector<vector<int>>(ROWS, vector<int>(COLS));

    vector<pair<int, int>> startVals;

    for (int i = 0; i < ROWS; i++)
    {
        string line = lines[i];
        for (int j = 0; j < COLS; j++)
        {
            int val = line[j] - '0';
            grid[i][j] = val;
            if (grid[i][j] == 0)
            {
                startVals.push_back({i, j});
            }
        }
    }

    int totalTrailHeads = 0;
    
    // <x, y, val>
    stack<tuple<int, int, int>> s;
    for (auto const &[x, y] : startVals)
    {
        set<pair<int, int>> visited;
        s.push(make_tuple(x, y, 0));
        while (!s.empty())
        {
            auto point = s.top();
            s.pop();

            int currX = get<0>(point);
            int currY = get<1>(point);
            int currVal = get<2>(point);
            visited.insert({currX, currY});

            // Exit Condition
            if (currVal == 9)
            {
                totalTrailHeads++;
                continue;
            }

            for (int i = 0; i < 4; i++)
            {
                int nextX = currX + dir[i].first;
                int nextY = currY + dir[i].second;
                if (validPoint(nextX, nextY) && visited.find({nextX, nextY}) == visited.end() && grid[nextX][nextY] == currVal + 1)
                {
                    s.push(make_tuple(nextX, nextY, currVal + 1));
                }
            }
        }
    }

    cout << "Total Trailheads: " << totalTrailHeads << endl;
}

void part2() {
    string file_path = "./input.txt";
    vector<string> lines = read_file(file_path);

    ROWS = lines.size();
    COLS = lines[0].size();
    grid = vector<vector<int>>(ROWS, vector<int>(COLS));

    vector<pair<int, int>> startVals;

    for (int i = 0; i < ROWS; i++)
    {
        string line = lines[i];
        for (int j = 0; j < COLS; j++)
        {
            int val = line[j] - '0';
            grid[i][j] = val;
            if (grid[i][j] == 0)
            {
                startVals.push_back({i, j});
            }
        }
    }

    
    // <x, y, val>
    stack<tuple<int, int, int, vector<pair<int, int>>>> s;
    set<vector<pair<int,int>>> ratings;

    for (auto const &[x, y] : startVals)
    {
        vector<pair<int, int>> path;
        s.push(make_tuple(x, y, 0, path));
        while (!s.empty())
        {
            auto point = s.top();
            s.pop();

            int currX = get<0>(point);
            int currY = get<1>(point);
            int currVal = get<2>(point);
            vector<pair<int, int>> currPath = get<3>(point);
            currPath.push_back({currX, currY});
            
            // Exit Condition
            if (currVal == 9)
            {
                sort( currPath.begin(), currPath.end() );
                ratings.insert( currPath );
                continue;
            }

            for (int i = 0; i < 4; i++)
            {
                int nextX = currX + dir[i].first;
                int nextY = currY + dir[i].second;
                if (validPoint(nextX, nextY) && grid[nextX][nextY] == currVal + 1)
                {
                    s.push(make_tuple(nextX, nextY, currVal + 1, currPath));
                }
            }
        }
    }
    cout << "Ratings : " << ratings.size() << endl;
}

int main()
{
    // part1();
    part2();
}
