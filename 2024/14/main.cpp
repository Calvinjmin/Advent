#include <iostream>
#include <vector>

#include "../utils.h"
using namespace std;

// GLOBALS
int GRID_ROWS = 101;
int GRID_COLS = 103;
int GRID_LINE_X = GRID_ROWS / 2;
int GRID_LINE_Y = GRID_COLS / 2;

class Robot
{
public:
    pair<int, int> coordinates;
    pair<int, int> velocity;

    Robot(int x, int y, int veloX, int veloY)
    {
        this->coordinates = {x, y};
        this->velocity = {veloX, veloY};
    }

    void setCoordinates(int x, int y)
    {
        this->coordinates = {x, y};
    }
};

int calcQuad(int x, int y)
{
    if (x == GRID_LINE_X || y == GRID_COLS)
    {
        return -1;
    }

    if (x >= 0 && x < GRID_LINE_X && y >= 0 && y < GRID_LINE_Y)
    {
        return 0;
    }
    else if (x > GRID_LINE_X && y >= 0 && y < GRID_LINE_Y)
    {
        return 1;
    }
    else if (x >= 0 && x < GRID_LINE_X && y > GRID_LINE_Y)
    {
        return 2;
    }
    else if (x > GRID_LINE_X && y > GRID_LINE_Y)
    {
        return 3;
    }
    else
    {
        return -1;
    }
}

void part1()
{
    string file_path = "./input.txt";
    vector<string> lines = read_file(file_path);

    vector<Robot> robots;

    // Parse Robot Objects
    for (const string &s : lines)
    {
        // Parse each line and create a Robot Obj
        vector<string> vals = split(s, " ");
        string coord = vals[0].substr(vals[0].find("=") + 1);
        vector<string> coordinates = split(coord, ",");
        string velo = vals[1].substr(vals[1].find("=") + 1);
        vector<string> velocity = split(velo, ",");
        robots.push_back(Robot(stoi(coordinates[0]), stoi(coordinates[1]),
                               stoi(velocity[0]), stoi(velocity[1])));
    }

    int SECONDS = 100;
    for (int i = 0; i < SECONDS; i++)
    {
        for (auto &r : robots)
        {
            // Calculate new Coordinates with wrap around
            int newX = r.coordinates.first + r.velocity.first;
            int newY = r.coordinates.second + r.velocity.second;
            newX = newX < 0 ? GRID_ROWS + newX : newX % GRID_ROWS;
            newY = newY < 0 ? GRID_COLS + newY : newY % GRID_COLS;
            r.setCoordinates(newX, newY);
        }
    }

    vector<int> answer(4);
    for (auto &r : robots)
    {
        // Calc which quad the robot is in
        int quad = calcQuad(r.coordinates.first, r.coordinates.second);
        if (quad != -1)
        {
            answer[quad]++;
        }
    }

    // Return Value
    int ret = 1;
    for (int i = 0; i < 4; i++)
    {
        cout << answer[i] << endl;
        ret *= answer[i];
    }

    /*
    Part 1 answer:
        116
        124
        126
        127
        Answer: 230172768
    */

    cout << "Answer: " << ret << endl;
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
    // Quadrant Lines
    part1();
    // part2();
}
