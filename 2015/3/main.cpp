#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <unordered_map>

using namespace std;

int main()
{
    ifstream file("./3/input.txt");
    if (!file.is_open())
    {
        cerr << "Could not open file." << endl;
    }

    stringstream buffer;
    buffer << file.rdbuf();

    string input = buffer.str();
    set<pair<int, int>> visited;

    pair<int, int> location = {0, 0};
    pair<int,int> robo_location = {0,0};
    visited.insert(location);

    unordered_map<char, pair<int, int>> mapping;
    mapping['^'] = {1, 0};  // North
    mapping['v'] = {-1, 0}; // South
    mapping['>'] = {0, 1};  // East
    mapping['<'] = {0, -1}; // West

    pair<int, int> move;
    bool robo = false;
    for (char dir : input)
    {
        move = mapping[dir];
        if ( robo ) {
            robo = false;
            int nx = robo_location.first + move.first;
            int ny = robo_location.second + move.second;
            robo_location = {nx, ny};
            visited.insert(robo_location);
        }
        else {
            robo = true;
            int nx = location.first + move.first;
            int ny = location.second + move.second;
            location = {nx, ny};
            visited.insert(location);
        }
    }

    cout << "Number of Houses: " << visited.size() << endl;
}