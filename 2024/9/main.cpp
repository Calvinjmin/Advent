#include "../utils.h"
#include <iostream>
#include <string>
using namespace std;

long long calculateCheckSum(vector<string> memory) {
  long long checksum = 0;
  for (int i = 0; i < memory.size(); i++) {
    if (memory[i] != ".") {
      checksum += stoll(memory[i]) * i;
    }
  }
  return checksum;
}

void part1() {
  string file_path = "./input.txt";
  // string file_path = "./small_input.txt";
  vector<string> lines = read_file(file_path);

  int idCounter = 0;
  vector<string> memory;

  // Create Mem Vector Based on Input
  for (const string &s : lines) {
    for (int i = 0; i < s.size(); i += 2) {
      int fileLength = stoi(string(1, s[i]));
      int freeMem = 0;
      if (i == s.size() - 1) {
        freeMem = 0;
      } else {
        freeMem = stoi(string(1, s[i + 1]));
      }

      for (int s = 0; s < fileLength; s++) {
        memory.push_back(to_string(idCounter));
      }
      idCounter += 1;
      for (int s = 0; s < freeMem; s++) {
        memory.push_back(".");
      }
    }
  }

  int firstDot = 0;
  int lastId = memory.size() - 1;

  // Find First Dot and Last ID
  while (firstDot < memory.size() && memory[firstDot] != ".") {
    firstDot++;
  }

  while (lastId >= 0 && memory[lastId] == ".") {
    lastId--;
  }

  // Compact by moving IDs left
  while (firstDot < lastId) {
    // Swap first dot with last ID
    swap(memory[firstDot], memory[lastId]);

    while (firstDot < memory.size() && memory[firstDot] != ".") {
      firstDot++;
    }

    while (lastId >= 0 && memory[lastId] == ".") {
      lastId--;
    }
  }

  // Calculate checksum
  cout << calculateCheckSum(memory) << endl;
}

void part2() {
  string file_path = "./input.txt";
  // string file_path = "./small_input.txt";
  vector<string> lines = read_file(file_path);

  int idCounter = 0;
  vector<string> memory;

  // Create Mem Vector Based on Input
  for (const string &s : lines) {
    for (int i = 0; i < s.size(); i += 2) {
      int fileLength = stoi(string(1, s[i]));
      int freeMem = 0;
      if (i == s.size() - 1) {
        freeMem = 0;
      } else {
        freeMem = stoi(string(1, s[i + 1]));
      }

      for (int s = 0; s < fileLength; s++) {
        memory.push_back(to_string(idCounter));
      }
      idCounter += 1;
      for (int s = 0; s < freeMem; s++) {
        memory.push_back(".");
      }
    }
  }

  // Identify file blocks
  vector<tuple<int, int, int, string>> files;
  int n = memory.size();
  for (int i = 0; i < n;) {
    if (memory[i] != ".") {
      int start = i;
      string fileId = memory[i];
      int length = 0;
      while (i < n && memory[i] == fileId) {
        length++;
        i++;
      }
      files.push_back({stoi(fileId), start, length, fileId});
    } else {
      i++;
    }
  }

  // Sort files by ID in descending order
  sort(files.begin(), files.end(),
       [](const tuple<int, int, int, string> &a,
          const tuple<int, int, int, string> &b) {
         return get<0>(a) > get<0>(b);
       });

  // Defragmentation
  for (const auto &[fileId, fileStart, fileLength, fileValue] : files) {
    // Find leftmost contiguous free space
    int bestStart = -1;
    int freeLength = 0;
    for (int i = 0; i < n; i++) {
      if (memory[i] == ".") {
        // Inital Case
        if (freeLength == 0) {
          bestStart = i;
        }
        freeLength++;

        // Most suitable space
        if (freeLength == fileLength) {
          break;
        }
      } else {
        freeLength = 0;
        bestStart = -1;
      }
    }

    // Move file if suitable space found
    if (bestStart != -1 && bestStart < fileStart) {
      // Clear original location
      fill(memory.begin() + fileStart, memory.begin() + fileStart + fileLength,
           ".");

      // Place in new location
      fill(memory.begin() + bestStart, memory.begin() + bestStart + fileLength,
           fileValue);
    }
  }
  cout << calculateCheckSum(memory) << endl;
}

int main() {
  part1();
  part2();
}
