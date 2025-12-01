#include <iostream>
#include "../../utils/utils.h"
using namespace std;

int position = 50;
int answer = 0;

void rotate( bool left, int& value ) {
    if ( left ) {
        position -= value;   
    } else {
        position += value;
    }

    position = position % 100;
    if (position < 0) position += 100;
}

void part1() {
    string file_path = "./input.txt";
    vector<string> lines = read_file(file_path);

    for ( const string& s: lines ) { 
        char dir = s.at(0);
        int temp = stoi(s.substr(1));
        rotate(dir == 'L', temp);

        if ( position == 0 ) answer++;
    }
    cout << "Number of Times @ 0: " << answer << endl;
}

int rotate_2(bool left, int value) {
    int temp; 

    // Normalize Value to 100 base -- cannot start at 0 to count clicks
    if (left) {
        temp = (position == 0) ? 100 : position;
    } else {
        temp = (position == 0) ? 100 : (100 - position);
    }

    int hits = 0;
    if (temp <= value) {
        // Number of times it crosses 100
        hits = 1 + (value - temp) / 100;
    }

    // New Postion without Mods
    int delta = left ? -value : value; 
    position = (position + delta) % 100; // recalibrate with turn
    if (position < 0) position += 100;

    return hits;
}

void part2() {
    string file_path = "./input.txt";
    vector<string> lines = read_file(file_path);

    position = 50;
    answer = 0;

    for (const string &s : lines) {
        char dir = s.at(0);
        int value = stoi(s.substr(1));

        bool goLeft = (dir == 'L');
        answer += rotate_2(goLeft, value);
    }

    cout << "Number of Times @ or Pass 0: " << answer << endl;
}

int main() {
    part1();
    part2();
}
