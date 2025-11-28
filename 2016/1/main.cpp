#include <iostream>
#include <set>
#include "../../utils/utils.h"
using namespace std;

//     0,-1
// -1,0   1,0
//     0,1

pair<int,int> coords = {0,0};
static const vector<pair<int,int>>& dir = {{0,-1},{1,0},{0,1},{-1,0}};
int facing = 0;

set<pair<int,int>> locations;

void adjust( const char& newDir ) {
    if ( newDir == 'R' ) {
        if (facing == 3 ) {
            facing = 0;
        } else {
            facing++;
        }

    } else {
        if (facing == 0 ) {
            facing = 3;
        } else {
            facing--;
        }

    }
}

void part1() {
    string input1 = "./input.txt";
    vector<string> lines = read_file(input1);
    vector<string> instructions = split( lines[0], ", ");

    for ( const string& s : instructions ) {
        adjust( s.at(0) );
        const string& temp = s.substr(1);
        const int& mult = stoi(temp);
        pair<int,int> face = dir[facing];
        if ( face.first == 0 ) {
            coords.second = coords.second + ( face.second * mult );
        } else {
            coords.first = coords.first + ( face.first * mult );
        }

        // cout << "(" << coords.first << ", " << coords.second << ")" << endl;
    }

    int answer = abs(coords.first) + abs(coords.second);
    cout << "Answer: " << answer << endl;
}

void part2() {
    coords = {0,0};
    string input1 = "./input.txt";
    vector<string> lines = read_file(input1);
    vector<string> instructions = split( lines[0], ", ");

    locations.insert(coords);
    bool found = false;

    for ( const string& s : instructions ) {
        if (found) break;  
        
        adjust( s.at(0) );
        const string& temp = s.substr(1);
        int mult = stoi(temp);

        const pair<int,int>& face = dir[facing];

        if ( face.first == 0 ) {
            while ( mult > 0 ) {
                coords.second = coords.second + face.second;
                if ( locations.find(coords) != locations.end() ) {
                    found = true;
                    break;
                } else {
                    locations.insert( coords );
                } 
                mult--;
            }
        } else {
            while ( mult > 0 ) {
                coords.first = coords.first + face.first;
                if ( locations.find(coords) != locations.end() ) {
                    found = true;
                    break;
                } else {
                    locations.insert( coords );
                } 
                mult--;
            }
        }
    } 

    int answer = abs(coords.first) + abs(coords.second);
    // cout << "(" << coords.first << ", " << coords.second << ")" << endl;
    cout << "Answer: " << answer << endl;
}

int main() {
    part1();
    part2();
}
