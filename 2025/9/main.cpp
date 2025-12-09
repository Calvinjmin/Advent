#include <iostream>
#include <algorithm>
#include <map>
#include <functional>
#include "../../utils/utils.h"
using namespace std;

vector<pair<unsigned long long, unsigned long long>> red_tiles;
unsigned long long rows;
unsigned long long cols;

void printGrid(vector<vector<char>> &grid)
{
    for (auto r : grid) {
        for (auto c : r) {
            cout << c;
        }
        cout << endl;
    }
}

bool validRec(pair<unsigned long long, unsigned long long> a, pair<unsigned long long, unsigned long long> b)
{
    unsigned long long minCol = min(a.first, b.first);
    unsigned long long maxCol = max(a.first, b.first);
    unsigned long long minRow = min(a.second, b.second);
    unsigned long long maxRow = max(a.second, b.second);

    int n = (int)red_tiles.size();

    // 1. interior slice of rectangle
    for (int i = 0; i < n; ++i)
    {
        auto p = red_tiles[i];
        auto q = red_tiles[(i + 1) % n];

        unsigned long long x1 = p.first, y1 = p.second;
        unsigned long long x2 = q.first, y2 = q.second;

        if (x1 == x2)
        {
            // vertical line
            if (minCol < x1 && x1 < maxCol)
            {
                unsigned long long segMinY = min(y1, y2);
                unsigned long long segMaxY = max(y1, y2);
                unsigned long long lo = max(segMinY, minRow);
                unsigned long long hi = min(segMaxY, maxRow);
                if (lo < hi)
                    return false;
            }
        }
        else if (y1 == y2)
        {
            // horizontal edge
            if (minRow < y1 && y1 < maxRow)
            {
                unsigned long long segMinX = min(x1, x2);
                unsigned long long segMaxX = max(x1, x2);
                unsigned long long lo = max(segMinX, minCol);
                unsigned long long hi = min(segMaxX, maxCol);
                if (lo < hi)
                    return false; 
            }
        }
    }

    // 2. go right and and cut
    // center point of the rectangle and move to the right
    double cx = (double)(minCol + maxCol) / 2.0;
    double cy = (double)(minRow + maxRow) / 2.0;

    // bool inside = false;
    int inside = 0;
    for (int i = 0; i < n; ++i)
    {
        auto p = red_tiles[i];
        auto q = red_tiles[(i + 1) % n];

        double x1 = (double)p.first;
        double y1 = (double)p.second;
        double x2 = (double)q.first;
        double y2 = (double)q.second;

        bool crossesY = ((y1 > cy) != (y2 > cy));
        // only cross when the middle point makes sense to do so
        if (crossesY)
        {
            double x_int = x1 + (cy - y1) * (x2 - x1) / (y2 - y1);
            if (x_int > cx)
            {
                inside++;   // if it crosses twice, then this should be false
            }
        }
    }

    return inside < 2;
}

void part1()
{
    string file_path = "./input.txt";
    vector<string> lines = read_file(file_path);

    rows = -1;
    cols = -1;

    for (const string &s : lines)
    {
        vector<string> loc = split(s, ",");
        cols = max(cols, stoull(loc[0]) + 1);
        rows = max(rows, stoull(loc[1]) + 1);
        red_tiles.emplace_back(make_pair(stoull(loc[0]), stoull(loc[1])));
    }

    // Brute Force
    unsigned long long maxArea = 0;
    for (int i = 0; i < red_tiles.size(); i++)
    {
        for (int j = 0; j < red_tiles.size(); j++)
        {
            if (i != j)
            {
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

void part2()
{
    string file_path = "./input.txt";
    vector<string> lines = read_file(file_path);

    for (const string &s : lines)
    {
        vector<string> loc = split(s, ",");
        red_tiles.emplace_back(make_pair(stoull(loc[0]), stoull(loc[1])));
    }

    // 1. Find the max area of a recetangle that exists within the boarder
    // Idea from friend
    // a. create a recetangle given two points
    // b. loop through the red_tiles and create edges between them
    // c. if the edges slice the recetangle at any point only going right, return false - not valid
    // d. if the edge is vertical, go right and if you cross two boaders then should false
    // f. else return true
    unsigned long long maxArea = 0;

    for (int i = 0; i < red_tiles.size(); i++)
    {
        // cout << i << " out of " << red_tiles.size() << endl;
        for (int j = 0; j < red_tiles.size(); j++)
        {
            if (i != j)
            {
                auto a = red_tiles[i];
                auto b = red_tiles[j];

                unsigned long long width = (b.first > a.first ? b.first - a.first : a.first - b.first) + 1;
                unsigned long long height = (b.second > a.second ? b.second - a.second : a.second - b.second) + 1;

                // Optimize
                if (width * height <= maxArea)
                {
                    continue;
                }

                if (validRec(a, b))
                {
                    maxArea = width * height;
                }
            }
        }
    }

    cout << "Answer: " << maxArea << endl;
}

int main()
{
    // part1();
    part2();
}
