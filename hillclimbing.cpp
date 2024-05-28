#include <iostream>
#include <vector>
#include <set>
#include<limits.h>
using namespace std;

int heuristic(vector<vector<int>> curr, vector<vector<int>> goal) {
    int c = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (curr[i][j] != goal[i][j]) c++;
        }
    }
    return c;
}

pair<int, int> find_empty(vector<vector<int>> curr) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (curr[i][j] == 0) return {i, j};
        }
    }
    return {-1, -1};
}

bool isValid(int x, int y) {
    return x >= 0 && x < 3 && y >= 0 && y < 3;
}

void print(vector<vector<int>> temp) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << temp[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int solve(vector<vector<int>> start, vector<vector<int>> goal) {
    set<vector<vector<int>>> visited;
    visited.insert(start);
    vector<vector<int>> curr = start;
    vector<vector<vector<int>>> path;
    path.push_back(start);
    while (true) {
        if (curr == goal) {
            for (int i = 0; i < path.size(); i++)
            {
                print(path[i]);
            }
            return 1;
        }

        vector<pair<int, int>> dir = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        pair<int, int> temp = find_empty(curr);
        int x = temp.first;
        int y = temp.second;
        int h;
        vector<vector<int>> bestNext;
        int best_h = INT_MAX;  // Initialize to a large value

        for (auto i : dir) {
            int xnew = x + i.first;
            int ynew = y + i.second;

            if (isValid(xnew, ynew)) {
                vector<vector<int>> next = curr;
                swap(next[x][y], next[xnew][ynew]);
                if (visited.find(next) == visited.end()) {
                    h = heuristic(next, goal);
                    if (h < best_h) {
                        best_h = h;
                        bestNext = next;
                    }
                }
            }
        }
        if (bestNext.empty()) {
            cout << "No Solution";
            return 0;  
        }
        curr = bestNext;
        path.push_back(curr);
        visited.insert(curr);
    }
}

int main() {
    vector<vector<int>> start = {{1, 2, 3}, {4, 5, 6}, {7, 0, 8}};
    vector<vector<int>> goal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

    if (!solve(start, goal)) cout << "No Solution";

    return 0;
}
