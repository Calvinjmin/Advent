#include <iostream>
#include <algorithm>
#include <unordered_set>

#include "../utils.h"
using namespace std;

unordered_set<string> designs;
int maxLook;

bool isPossible( string potentialDesign ) {
    int n = potentialDesign.size();
    vector<bool> dp(n + 1, false);
    dp[0] = true;

    for (int i = 1; i <= n; i++) {
        for (int len = 1; len <= maxLook && i - len >= 0; len++) {
            string curr = potentialDesign.substr(i - len, len);
            if (designs.find(curr) != designs.end() && dp[i - len]) {
                dp[i] = true;
                break;
            }
        }
    }

    return dp[n];
}

// Bottom Up DP Counting
long countWays(const string& potentialDesign) {
    int n = potentialDesign.size();
    vector<long> dp(n + 1, 0);
    dp[0] = 1; 

    for (int i = 1; i <= n; i++) {
        for (int len = 1; len <= maxLook && i - len >= 0; len++) {
            string curr = potentialDesign.substr(i - len, len);
            if (designs.find(curr) != designs.end()) {
                dp[i] += dp[i - len];
            }
        }
    }

    return dp[n];
}

void part1() {
    string file_path = "./input.txt";
    vector<string> lines = read_file(file_path);
    vector<string> availableTowels = split( lines[0], ", ");

    for (const string& s : availableTowels) {
        designs.insert(s);
        maxLook = max(maxLook, int(s.size()));
    }

    vector<string> potentialDesigns;
    int answer = 0;
    for ( int i = 2; i < lines.size(); i++ ) {
        const string &currDesign = lines[i];
        bool possible = isPossible( currDesign );
        answer += possible ? 1 : 0;
    }

    cout << maxLook << endl;
    cout << "Answer: " << answer << endl;
}

void part2() {
    string file_path = "./input.txt";
    vector<string> lines = read_file(file_path);
    vector<string> availableTowels = split( lines[0], ", ");

    for (const string& s : availableTowels) {
        designs.insert(s);
        maxLook = max(maxLook, int(s.size()));
    }

    vector<string> potentialDesigns;
    long long answer = 0;
    for ( int i = 2; i < lines.size(); i++ ) {
        const string &currDesign = lines[i];
        answer += countWays(currDesign);
    }

    cout << maxLook << endl;
    cout << "Answer: " << answer << endl;
}

int main() {
    part1();
    part2();
}

