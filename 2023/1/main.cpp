#include <iostream>
#include <ctype.h>
#include "../utils.h"

using namespace std;

int main() {
    string file_path = "./input.txt";
    vector<string> lines = read_file(file_path);

    int answer = 0;
    for (const string &s : lines) {
        // Loop through and grab the two numbers and sum them
        int left = 0;
        int right = s.length() - 1; // Adjusted to the last valid index
        int loc[2] = {-1, -1};

        while (left <= right) {
            if (loc[0] == -1 && isdigit(s.at(left))) {
                loc[0] = left;
            }
            if (loc[1] == -1 && isdigit(s.at(right))) {
                loc[1] = right;
            }
            if (loc[0] != -1 && loc[1] != -1) {
                break;
            }
            if (loc[0] == -1) left++;
            if (loc[1] == -1) right--;
        }

        if (loc[0] != -1 && loc[1] != -1) {
            if (loc[0] == loc[1]) {
                int dig = s.at(loc[0]) - '0'; // Convert char to digit
                answer += (10 * dig) + dig;
            } else {
                int f = s.at(loc[0]) - '0'; // Convert char to digit
                int se = s.at(loc[1]) - '0'; // Convert char to digit
                answer += (10 * f) + se;
            }
        }
    }
    cout << "Answer: " << answer << endl;
}
