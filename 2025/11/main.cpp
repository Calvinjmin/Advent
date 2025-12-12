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
map<tuple<string,bool,bool>, unsigned long long> memo;

void dfs( int& recur, const string& key ) {
    if ( key == endNode ) {
        recur += 1;
    }
    vector<string>& currEdge = edges[key];
    for ( const string& node: currEdge ) {
        dfs(recur, node);
    }
}

unsigned long long dfs2( const string& key, bool hasDac, bool hasFft ) {
    if ( key == "dac" ) hasDac = true;
    if ( key == "fft" ) hasFft = true;

    if ( key == endNode ) {
        return (hasDac && hasFft) ? 1 : 0;
    }

    unsigned long long total = 0;

    // assumption - no cycle, use memo to capture state and return totals AKA cache
    auto state = make_tuple(key, hasDac, hasFft);
    if ( memo.count(state) ) return memo[state];
    for ( const string& node: edges[key] ) {
        total += dfs2(node, hasDac, hasFft);
    }
    return memo[state] = total;
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

    unsigned long long recur = 0;
    unordered_set<string> path;
    recur = dfs2( startNodeP2, false, false);
    cout << "Answer: " << recur << endl;
}

int main() {
    //part1();
    part2();
}
