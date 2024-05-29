#include <bits/stdc++.h>
using namespace std;

struct Condition {
    vector<string> AND;
    vector<string> OR;
};

struct Node {
    string name;
    int heuristic;
    Condition condition;
};

map<string, int> calculateCost(map<string, int>& heuristics, Condition& condition, int weight) {
    map<string, int> cost;

    if (!condition.AND.empty()) {
        int totalCost = 0;
        for (const string& node : condition.AND) {
            totalCost += heuristics[node] + weight;
        }
        string path = "AND " + accumulate(condition.AND.begin(), condition.AND.end(), string(),
                                          [](const string& a, const string& b) { return a + (a.length() > 0 ? " AND " : "") + b; });
        cost[path] = totalCost;
    }

    if (!condition.OR.empty()) {
        int minCost = INT_MAX;
        string bestNode;
        for (const string& node : condition.OR) {
            int currentCost = heuristics[node] + weight;
            if (currentCost < minCost) {
                minCost = currentCost;
                bestNode = node;
            }
        }
        cost["OR " + bestNode] = minCost;
    }

    return cost;
}

map<string, map<string, int>> updateCost(map<string, int>& heuristics, map<string, Condition>& conditions, int weight) {
    vector<string> mainNodes;
    for (const auto& pair : conditions) {
        mainNodes.push_back(pair.first);
    }
    reverse(mainNodes.begin(), mainNodes.end());

    map<string, map<string, int>> leastCost;

    for (const string& key : mainNodes) {
        Condition& condition = conditions[key];
        map<string, int> cost = calculateCost(heuristics, condition, weight);
        heuristics[key] = min_element(cost.begin(), cost.end(),
                                      [](const pair<string, int>& a, const pair<string, int>& b) { return a.second < b.second; })
                              ->second;
        leastCost[key] = cost;
    }

    return leastCost;
}

string shortestPath(const string& start, map<string, map<string, int>>& updatedCost, map<string, int>& heuristics) {
    string path = start;
    if (updatedCost.find(start) != updatedCost.end()) {
        auto& costs = updatedCost[start];
        auto minCost = min_element(costs.begin(), costs.end(),
                                   [](const pair<string, int>& a, const pair<string, int>& b) { return a.second < b.second; });
        string nextPath = minCost->first;
        stringstream ss(nextPath);
        string segment;
        vector<string> nodes;

        while (getline(ss, segment, ' ')) {
            if (segment != "AND" && segment != "OR") {
                nodes.push_back(segment);
            }
        }

        if (nodes.size() == 1) {
            path += "<--" + shortestPath(nodes[0], updatedCost, heuristics);
        } else {
            path += "<--(" + nextPath + ") [" + shortestPath(nodes[0], updatedCost, heuristics) + " + " +
                    shortestPath(nodes[1], updatedCost, heuristics) + "]";
        }
    }
    return path;
}

int main() {
    map<string, int> heuristics = {
        {"A", -1}, {"B", 5}, {"C", 2}, {"D", 4}, {"E", 7}, {"F", 9},
        {"G", 3},  {"H", 0}, {"I", 0}, {"J", 0}};

    map<string, Condition> conditions;
    conditions["A"].OR = {"B"};
    conditions["A"].AND = {"C", "D"};
    conditions["B"].OR = {"E", "F"};
    conditions["C"].OR = {"G"};
    conditions["C"].AND = {"H", "I"};
    conditions["D"].OR = {"J"};

    int weight = 1;

    cout << "Updated Cost :" << endl;
    map<string, map<string, int>> updatedCost = updateCost(heuristics, conditions, weight);
    for (const auto& pair : updatedCost) {
        cout << pair.first << ": ";
        for (const auto& cost : pair.second) {
            cout << cost.first << " => " << cost.second << ", ";
        }
        cout << endl;
    }

    cout << string(75, '*') << endl;
    cout << "Shortest Path :" << endl;
    cout << shortestPath("A", updatedCost, heuristics) << endl;

    return 0;
}
