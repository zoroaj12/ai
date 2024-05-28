#include <iostream>
#include <stack>
#include <unordered_set>
#include <vector>

using namespace std;

struct Node {
    int jug1, jug2;
    int depth;
    Node* parent;
    string action;
};

Node* newNode(int jug1, int jug2, int depth, Node* parent, string action) {
    Node* node = new Node;
    node->jug1 = jug1;
    node->jug2 = jug2;
    node->depth = depth;
    node->parent = parent;
    node->action = action;
    return node;
}

void printPath(Node* node) {
    if (node == nullptr)
        return;
    printPath(node->parent);
    if (!node->action.empty()) {
        cout << node->action << endl;
    }
    cout << "Jug1: " << node->jug1 << ", Jug2: " << node->jug2 << endl;
}

bool isGoalState(Node* node, int target) {
    return (node->jug1 == target || node->jug2 == target);
}

void solve(int jug1Capacity, int jug2Capacity, int target) {
    stack<Node*> s;
    unordered_set<string> visited;
    
    Node* root = newNode(0, 0, 0, nullptr, "");
    s.push(root);
    visited.insert("0,0");

    while (!s.empty()) {
        Node* current = s.top();
        s.pop();

        if (isGoalState(current, target)) {
            cout << "Goal state reached" << endl;
            printPath(current);
            cout << "Depth: " << current->depth << endl;
            return;
        }

        vector<Node*> nextStates = {
            newNode(jug1Capacity, current->jug2, current->depth + 1, current, "Fill Jug1"),
            newNode(current->jug1, jug2Capacity, current->depth + 1, current, "Fill Jug2"),
            newNode(0, current->jug2, current->depth + 1, current, "Empty Jug1"),
            newNode(current->jug1, 0, current->depth + 1, current, "Empty Jug2"),
            newNode(max(0, current->jug1 - (jug2Capacity - current->jug2)), min(jug2Capacity, current->jug2 + current->jug1), current->depth + 1, current, "Pour Jug1 -> Jug2"),
            newNode(min(jug1Capacity, current->jug1 + current->jug2), max(0, current->jug2 - (jug1Capacity - current->jug1)), current->depth + 1, current, "Pour Jug2 -> Jug1")
        };

        for (Node* next : nextStates) {
            string stateKey = to_string(next->jug1) + "," + to_string(next->jug2);
            if (visited.find(stateKey) == visited.end()) {
                s.push(next);
                visited.insert(stateKey);
            } else {
                delete next;
            }
        }
    }

    cout << "Goal state not reached" << endl;
}

int main() {
    int jug1Capacity = 3;
    int jug2Capacity = 4;
    int target = 2;

    solve(jug1Capacity, jug2Capacity, target);

    return 0;
}
