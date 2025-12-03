#include <iostream>
#include "../../utils/utils.h"
using namespace std;

// algorithm
// go through each line to find two digits (assumption: each battery is a two digit number)
// grab the first digit from 0 - length - 2 (try to find the max char)
// go from loc of first digit to length - 1 (find max char)
int bank(const string& input) {
    int first_loc = 0;
    
    int maxDigit = -1;
    for ( int i = 0; i < input.length() - 1; i++ ) {
        int curr = input.at(i) - '0';
        if ( curr > maxDigit ) {
            first_loc = i;
            maxDigit = curr;
        }
        if ( maxDigit == 9 ) continue;
    }

    int secondDigit = -1;
    for ( int i = first_loc + 1; i < input.length(); i++ ) {
        secondDigit = max(secondDigit, input.at(i) - '0');
        if ( secondDigit == 9) break;
    }

    cout << "First D: " << maxDigit << " | " << secondDigit << endl;

    return maxDigit * 10 + secondDigit;
}

// keep a running track of largest digit and curr size
// size up the number while making sliding the window for possible digits
// ensure there are enough options of digits available for 12-x
unsigned long long bank_part2(const string& input ) {
    vector<int> digits;
    digits.reserve(12);

    int digits_left = 12;
    int last = 0;
    int maxDigit = -1;
    while ( digits.size() < 12 ) {

        maxDigit = -1;        

        for ( int i = last; i < input.size() - digits_left + 1; i++ ) {
            int curr = input.at(i) - '0';
            if ( curr > maxDigit ) {
                last = i;
                maxDigit = curr;
            }
            if ( maxDigit == 9 ) continue; 
        }

        last += 1;
        digits.push_back(maxDigit);
        digits_left -= 1;
    }

    unsigned long long battery = 0;
    for ( auto s: digits ) {
        battery = (10*battery) + s;
    }
    return battery;
}


void part1() {
    string file_path = "./input.txt";
    vector<string> lines = read_file(file_path);

    int answer = 0;
    for ( const string& s: lines ) {
        answer += bank(s);
    }
    cout << "Total Output Voltage: " << answer << endl;
}

void part2() {
    string file_path = "./input.txt";
    vector<string> lines = read_file(file_path);

    unsigned long long answer = 0;
    for ( const string& s: lines ) {
        answer += bank_part2(s);
    }

    cout << "Total Output Voltage: " << answer << endl;
}

int main() {
    part1();
    part2();
}
