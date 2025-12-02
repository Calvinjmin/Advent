#include <iostream>
#include "../../utils/utils.h"
using namespace std;

pair<unsigned long long, unsigned long long> parse_range( string& range ) {
    unsigned long long left = stoll(range.substr(0,range.find("-")));
    unsigned long long right = stoll(range.substr(range.find("-") + 1));
    return {left, right};
}

// invaild if digits repeat
// loop with one digit - then 2, then 3 then 4
unsigned long long is_invalid(unsigned long long number) {
    string num_string = to_string(number);

    for ( unsigned long long i = 1; i < num_string.length()/2 + 1; i++ ) {
        string temp = num_string.substr(0,i);

        unsigned long long loc = i;
        while ( loc < num_string.length() ) {
            if ( temp == num_string.substr(loc, loc+i) ) {
                loc += i;
            } else {
                break;
            }
        }

        /* part 1 */
        if ( loc == num_string.length () ) { 
            return number;
        }
    }
    return 0;
}

unsigned long long is_invalid_part2(unsigned long long number) {
    string num_string = to_string(number);

    for ( unsigned long long i = 1; i < num_string.length()/2 + 1; i++ ) {
        string temp = num_string.substr(0,i);

        unsigned long long loc = i;
        while ( loc < num_string.length() ) {
            // Change length of SubStr to length of window
            if ( temp == num_string.substr(loc, i) ) {
                loc += i;
            } else {
                break;
            }
        }

        if ( loc == num_string.length () ) { 
            return number;
        }
    }
    return 0;
}


unsigned long long iter_loop( unsigned long long& left, unsigned long long& right ) {
    unsigned long long answer = 0;
    cout << "Left: " << left << " Right: " << right << endl;
    for ( unsigned long long i = left; i <= right; i++ ) {
        answer += is_invalid_part2(i);
    }
    return answer;
}

void part1() {
    string file_path = "./input.txt";
    vector<string> lines = read_file(file_path); 
    vector<string> ranges;

    unsigned long long answer = 0;

    for ( const string& s: lines ) {
        auto temp = split(s,",");
        for ( string& r: temp ) {
            if ( s.empty() || s == "\n") continue;
            ranges.push_back(r);
        }
    }

    for ( auto temp: ranges ) {
        auto s = parse_range( temp );
        answer += iter_loop( s.first, s.second );
    }

    cout << "Summation Answer: " << answer << endl;
}

void part2() {
    string file_path = "./input.txt";
    vector<string> lines = read_file(file_path); 
    vector<string> ranges;

    unsigned long long answer = 0;

    for ( const string& s: lines ) {
        auto temp = split(s,",");
        for ( string& r: temp ) {
            if ( s.empty() || s == "\n") continue;
            ranges.push_back(r);
        }
    }

    for ( auto temp: ranges ) {
        auto s = parse_range( temp );
        answer += iter_loop( s.first, s.second );
    }

    cout << "Summation Answer: " << answer << endl;
}

int main() {
    part1();
    part2();
}
