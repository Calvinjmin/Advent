#include <iostream>
#include <set>
#include <algorithm>
#include "../../utils/utils.h"

using namespace std;

vector<pair<unsigned long long, unsigned long long>> ranges;

void insert_ids(const string& input ) {
    int split = input.find('-');
    unsigned long long first = stoull( input.substr(0,split));
    unsigned long long second = stoull( input.substr(split+1));

    pair<unsigned long long, unsigned long long> range = {first, second};
    ranges.push_back( range );

    // Cumbersome
    sort( ranges.begin(), ranges.end() );
}

bool falls_in_range(unsigned long long target) {
    for (const auto& range : ranges) {
        if (target >= range.first && target <= range.second) {
            return true;
        }
    }
    return false;
}
void part1() {
    string file_path = "./input.txt";
    vector<string> lines = read_file(file_path);

    bool range = true;
    int fresh = 0; 
    for ( const string& s: lines ) {
        if ( s == "" ) {
            range = false;
            continue;
        }
         
        if ( range ) {
            insert_ids( s );
        } else {
            if ( falls_in_range(stoull(s)) ) fresh++;
        }
    }
    cout << "Fresh IDs: " << fresh << endl;
}

void part2() {
    string file_path = "./input.txt";
    vector<string> lines = read_file(file_path);

    for ( const string& s: lines ) {
        if ( s == "" ) {
            break;
        }
        insert_ids(s);
    }

    unsigned long long total_ids = 0;

    // Loop through the ranges - check to see if the next iter.first <= curr.second
        // If so, combine that range and continue until it is false
    for ( int i = 0; i < ranges.size();) {
        pair<unsigned long long, unsigned long long> curr = ranges[i];

        int look_ahead = 1;
        while ( i+look_ahead < ranges.size() && ranges[i+look_ahead].first <= curr.second + 1 ) {
            curr.second = max(curr.second, ranges[i+look_ahead].second);
            look_ahead++;
        }

        total_ids += (curr.second - curr.first + 1);
        i += look_ahead;
    }

    cout << "Total Ingredients: " << total_ids << endl;

}

int main() {
    part1();
    part2();
}
