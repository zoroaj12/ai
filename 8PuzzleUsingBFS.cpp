#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

#define N 3

struct Node {
    Node* parent;
    int mat[N][N];
    int x, y;
    int depth;
    int cost;
    string action;  
};

bool isGoalState(int mat[N][N], int goal[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (mat[i][j] != goal[i][j])
                return false;
        }
    }
    return true;
}

int heuristics(int mat[N][N], int goal[N][N]) {
    int h = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (mat[i][j] != 0 && mat[i][j] != goal[i][j]) {
                h++;
            }
        }
    }
    return h;
}

void printMatrix(int mat[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

Node* newNode(int mat[N][N], int x, int y, int newX, int newY, int depth, Node* parent, string action) {
    Node* node = new Node;
    memcpy(node->mat,mat,sizeof(node->mat));
    node->x = newX;
    node->y = newY;
    swap(node->mat[x][y], node->mat[newX][newY]);
    node->depth = depth;
    node->parent = parent;
    node->action = action;
    return node;
}

void printPath(Node* root) {
    if (root == nullptr)
        return;
    printPath(root->parent);
    if (!root->action.empty()) {
        cout << "Move: " << root->action << endl;
    }
    printMatrix(root->mat);
}

struct CompareCost {
    bool operator()(Node* a, Node* b) {
        return (a->cost > b->cost);
    }
};

void solve(int initial[N][N], int x, int y, int goal[N][N]) {
    priority_queue<Node*, vector<Node*>, CompareCost> pq;
    Node* root = newNode(initial, x, y, x, y, 0, nullptr, "");
    root->cost = heuristics(initial, goal);
    pq.push(root);

    while (!pq.empty()) {
        Node* current = pq.top();
        pq.pop();

        if (isGoalState(current->mat, goal)) {
            cout << "Goal state reached" << endl;
            printPath(current);
            cout << "Depth: " << current->depth << endl;
            cout << "Cost: " << current->depth << endl;
            return;
        }

        int dx[] = {0, 0, -1, 1};
        int dy[] = {1, -1, 0, 0};
        string directions[] = {"right", "left", "up", "down"};

        for (int i = 0; i < 4; i++) {
            int newX = current->x + dx[i];
            int newY = current->y + dy[i];

            if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
                Node* child = newNode(current->mat, current->x, current->y, newX, newY, current->depth + 1, current, directions[i]);
                child->cost = child->depth + heuristics(child->mat, goal);
                pq.push(child);
            }
        }
    }

    cout << "Goal state not reached" << endl;
}

int main() {
    int initial[N][N] = {
        {1, 2, 3},
        {0, 4, 6},
        {7, 5, 8}
    };

    int goal[N][N] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };

    int x = 1, y = 0;  
    solve(initial, x, y, goal);

    return 0;
}