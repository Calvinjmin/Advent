#ifndef utils_h
#define utils_h

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> read_file( const string& file_path ) {
    ifstream file(file_path);
    vector<string> lines;

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << file_path << std::endl;
        return lines; // Return an empty vector on error
    }

    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }

    file.close();
    return lines;
}

#endif
