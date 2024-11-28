#include <iostream>
#include "../utils.h"
using namespace std;

int main() {
    string file_path = "./input.txt";
    vector<string> lines = read_file(file_path);

    for ( const string& s: lines ) {
        cout << s << endl;
    }
}
