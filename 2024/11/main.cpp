#include <iostream>
#include <string>
#include <unordered_map>

#include "../utils.h"
using namespace std;

unordered_map<string, vector<string>> memo;

vector<string> evolve(const string& input) {
    auto it = memo.find(input);
    if (it != memo.end()) {
        return it->second;
    }

    vector<string> retVal;
    retVal.reserve(2);

    long long val = stoll(input);
    if (val == 0) {
        retVal.push_back("1");
        memo.emplace(input, retVal); 
        return retVal;
    }

    size_t digits = input.length();
    if (digits % 2 == 0) {
        size_t half = digits / 2;
        long long part1 = stoll(input.substr(0, half));
        long long part2 = stoll(input.substr(half));

        retVal.push_back(to_string(part1));
        retVal.push_back(to_string(part2));
    } else {
        retVal.push_back(to_string(val * 2024));
    }

    memo.emplace(input, retVal);
    return retVal;
}

void part1() {
    string file_path = "./input.txt";
    vector<string> lines = read_file(file_path);
    vector<string> input = split( lines[0] , " " );

    int BLINKS = 25; 

    for ( int i = 0; i < BLINKS; i++ ) {
        vector<string> temp;
        for ( const string& s: input ) {
            vector<string> vals = evolve(s);
            for ( auto &t: vals ) {
                temp.push_back(t);
            }
        }
        input = temp;
    }
    
    cout << "Number of Stones: " << input.size() << endl;
}

void part2() {
    string file_path = "./input.txt";
    vector<string> lines = read_file(file_path);
    vector<string> initial_input = split(lines[0], " ");

    int BLINKS = 75;

    unordered_map<string, long long> freq_map;
    for (const string& s : initial_input) {
        freq_map[s]++;
    }

    for (int i = 0; i < BLINKS; i++) {
        cout << i << endl;
        unordered_map<string, long long> next_freq_map;
        for (const auto& [s, count] : freq_map) {
            vector<string> vals = evolve(s);
            for (const string& t : vals) {
                next_freq_map[t] += count; 
            }
        }
        freq_map.swap(next_freq_map);
    }

    long long total_stones = 0;
    for (const auto& [s, count] : freq_map) {
        total_stones += count;
    }
    
    cout << "Number of Stones: " << total_stones << endl;
}

int main() {
    // part1();
    part2();
}
