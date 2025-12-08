#include <iostream>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include "../../utils/utils.h"
using namespace std;

vector<tuple<int, int, int>> jBoxes;
vector<int> parent;
vector<int> rankVec;

// Disjoint Union Set Algorithm
// Idea: create grouping based off the root, combine and count members in groupings
int find( int i ) {
    if ( parent[i] == i ) {
        return i;
    }
    return parent[i] = find(parent[i]);
}
void mergeSets(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);

    if (root_i != root_j) { 
        if (rankVec[root_i] < rankVec[root_j]) {
            parent[root_i] = root_j;
        } else if (rankVec[root_i] > rankVec[root_j]) {
            parent[root_j] = root_i;
        } else { 
            parent[root_j] = root_i;
            rankVec[root_i]++;
        }
    }
}

double distance( const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
    double x = pow(get<0>(b) - get<0>(a), 2);
    double y = pow(get<1>(b) - get<1>(a), 2);
    double z = pow(get<2>(b) - get<2>(a), 2);
    return sqrt(x+y+z);
}

void part1() {
    string file_path = "./input.txt";
    vector<string> lines = read_file(file_path);

    for ( const string& s: lines ) {
        vector<string> jBoxes_str = split(s, ",");
        int val1 = stoi(jBoxes_str[0]);
        int val2 = stoi(jBoxes_str[1]);
        int val3 = stoi(jBoxes_str[2]);
        jBoxes.emplace_back(val1, val2, val3);
    }

    // Init Vectors
    int n = jBoxes.size();
    parent.resize(n);
    rankVec.resize(n, 0);
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    // Edge Validation
    vector<tuple<double, int, int>> edges; 
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double dist = distance(jBoxes[i], jBoxes[j]);
            edges.emplace_back(dist, i, j);
        }
    }

    // Sort by distance 
    sort(edges.begin(), edges.end());
    int edges_processed = 0;
    for (const auto& edge : edges) {
        double dist = get<0>(edge);
        int i = get<1>(edge);
        int j = get<2>(edge);

        edges_processed++;

        if (find(i) != find(j)) {
            mergeSets(i, j);
            cout << "Edge " << edges_processed << i << " and " << j << " (dist: " << dist << ")" << endl;
        } 

        if (edges_processed == 1000) {
            break;
        }
    }

    // ANSWER Compliation - Count components 
    map<int, int> component_sizes;
    for (int i = 0; i < n; i++) {
        component_sizes[find(i)]++;
    }

    vector<long long> sizes;
    for (const auto& pair : component_sizes) {
        sizes.push_back(pair.second);
    }
    sort(sizes.rbegin(), sizes.rend());

    long long answer = sizes[0] * sizes[1] * sizes[2];
    cout << "Answer: " << answer << endl;
}

void part2() {
    string file_path = "./input.txt";
    vector<string> lines = read_file(file_path);

    set<tuple<int,int,int>> visited;

    for ( const string& s: lines ) {
        vector<string> jBoxes_str = split(s, ",");
        int val1 = stoi(jBoxes_str[0]);
        int val2 = stoi(jBoxes_str[1]);
        int val3 = stoi(jBoxes_str[2]);
        jBoxes.emplace_back(val1, val2, val3);
    }

    // Init Vectors
    int n = jBoxes.size();
    parent.resize(n);
    rankVec.resize(n, 0);
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    // Edge Validation
    vector<tuple<double, int, int>> edges; 
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double dist = distance(jBoxes[i], jBoxes[j]);
            edges.emplace_back(dist, i, j);
        }
    }

    // Sort by distance 
    sort(edges.begin(), edges.end());
    int edges_processed = 0;
    for (const auto& edge : edges) {
        double dist = get<0>(edge);
        int i = get<1>(edge);
        int j = get<2>(edge);

        auto a = jBoxes[i];
        auto b = jBoxes[j];
        visited.insert(a);
        visited.insert(b);

        edges_processed++;

        if (find(i) != find(j)) {
            mergeSets(i, j);
            cout << "Edge " << edges_processed << i << " and " << j << " (dist: " << dist << ")" << endl;
        } 

        // Stop when we visit all unique points 
        if ( visited.size() == n ) {
            unsigned long long answer = (unsigned long long) get<0>(a) * get<0>(b);
            cout << "Answer: " << answer << endl;
            break;
        }
    }
}

int main() {
    part1();
    part2();
}
