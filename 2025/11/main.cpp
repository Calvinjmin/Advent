#include <iostream>
#include "map"
#include "unordered_set"
#include "../../utils/utils.h"
using namespace std;

// A directed graph with edges
// Count the unique number of occurences to get from you (starting) to out (ending)

const string& startNode = "you";
const string& endNode = "out";

const string& startNodeP2 = "svr";
map<string, vector<string>> edges;

void dfs( int& recur, const string& key ) {
    if ( key == endNode ) {
        recur += 1;
    }
    vector<string>& currEdge = edges[key];
    for ( const string& node: currEdge ) {
        dfs(recur, node);
    }
}

// tldr; too inefficient .... maybe there is an opp for early pruning
void dfs2( int& recur, const string& key, unordered_set<string>& path, bool hasDac, bool hasFft ) {
    if ( key == "dac" ) hasDac = true;
    if ( key == "fft" ) hasFft = true;

    if ( key == endNode ) {
        if ( hasDac && hasFft ) {
            recur += 1;
        }
        return;
    }

    path.insert(key);
    const vector<string>& currEdge = edges[key];
    for ( const string& node: currEdge ) {
        if ( path.count(node) == 0 ) {
            dfs2(recur, node, path, hasDac, hasFft);
        }
    }
    path.erase(key);
}

void part1() {
    string file_path = "./input.txt";
    vector<string> lines = read_file(file_path);

    for ( const string& s: lines ) {
        vector<string> currEdge = split(s, " ");
        string key = currEdge[0].substr(0,currEdge[0].size()-1);
        edges[key] = {};
        for ( int i = 1; i < currEdge.size(); i++ ) {
            vector<string>& temp = edges[key];
            temp.push_back(currEdge[i]);
            edges[key] = temp;
        }
    }

    int recur = 0;
    dfs( recur, startNode);
    cout << "Answer: " << recur << endl;

}

void part2() {
    string file_path = "./input.txt";
    vector<string> lines = read_file(file_path);

    for ( const string& s: lines ) {
        vector<string> currEdge = split(s, " ");
        string key = currEdge[0].substr(0,currEdge[0].size()-1);
        edges[key] = {};
        for ( int i = 1; i < currEdge.size(); i++ ) {
            vector<string>& temp = edges[key];
            temp.push_back(currEdge[i]);
            edges[key] = temp;
        }
    }

    int recur = 0;
    unordered_set<string> path;
    dfs2( recur, startNodeP2, path, false, false);
    cout << "Answer: " << recur << endl;
}

int main() {
    //part1();
    part2();
}
