#include <bits/stdc++.h>
using namespace std;

#define N 3

struct Node {
    Node* parent;
    int mat[N][N];  // Current state of the puzzle
    int x, y;  // Coordinates of the empty space (0)
    int cost;  // Cost to reach this node (g(n) + h(n))
    int depth;  // Number of moves so far (g(n))
    bool mark;  // Node marked as solved
    bool solved;  // Node is solved
    vector<Node*> children;  // Child nodes

    Node(int mat_[N][N], int x_, int y_, int depth_, int cost_, Node* parent_ = nullptr) 
        : x(x_), y(y_), depth(depth_), cost(cost_), parent(parent_), mark(false), solved(false) {
        memcpy(mat, mat_, sizeof(mat));
    }
};

int row[4] = {1, 0, -1, 0};
int col[4] = {0, -1, 0, 1};
int edge_cost = 1;

int heuristic(int mat[N][N], int goal[N][N]) {
    int misplaced = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (mat[i][j] && mat[i][j] != goal[i][j]) {
                ++misplaced;
            }
        }
    }
    return misplaced;
}

bool isSafe(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N;
}

void printMatrix(int mat[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void printPath(Node* root) {
    if (root == nullptr) return;
    printPath(root->parent);
    printMatrix(root->mat);
}

bool isGoalState(int mat[N][N], int goal[N][N]) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (mat[i][j] != goal[i][j])
                return false;
    return true;
}

Node* createNode(int mat[N][N], int x, int y, int newX, int newY, int depth, Node* parent, int goal[N][N]) {
    int newMat[N][N];
    memcpy(newMat, mat, sizeof(newMat));
    swap(newMat[x][y], newMat[newX][newY]);
    return new Node(newMat, newX, newY, depth + 1, depth + 1 + heuristic(newMat, goal), parent);
}

void AOStar(Node* root, int goal[N][N]) {
    while (!root->solved) {
        Node* nextNode = root;
        stack<Node*> st;
        while (nextNode && nextNode->mark) {
            if (nextNode->children.empty()) {
                root->solved = true;
                return;
            }
            int minCost = INT_MAX;
            st.push(nextNode);
            Node* bestChild = nullptr;
            for (Node* child : nextNode->children) {
                if (child->cost < minCost) {
                    minCost = child->cost;
                    bestChild = child;
                }
            }
            nextNode = bestChild;
        }

        if (!nextNode) continue;

        for (Node* child : nextNode->children) {
            if (!child->mark) {
                for (int i = 0; i < 4; ++i) {
                    int newX = child->x + row[i];
                    int newY = child->y + col[i];
                    if (isSafe(newX, newY)) {
                        Node* newNode = createNode(child->mat, child->x, child->y, newX, newY, child->depth, child, goal);
                        if (isGoalState(newNode->mat, goal)) {
                            newNode->solved = true;
                            printPath(newNode);
                            cout << "Solved with cost: " << newNode->cost << endl;
                            return;
                        }
                        child->children.push_back(newNode);
                    }
                }
                child->mark = true;
            }
        }

        while (!st.empty()) {
            Node* n = st.top();
            st.pop();
            int finalCost = INT_MAX;
            for (Node* child : n->children) {
                finalCost = min(finalCost, child->cost);
            }
            n->cost = finalCost;
        }
    }
}

int main() {
    int start[N][N] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 0, 8}
    };

    int goal[N][N] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };

    int startX, startY;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (start[i][j] == 0) {
                startX = i;
                startY = j;
                break;
            }
        }
    }

    Node* root = new Node(start, startX, startY, 0, heuristic(start, goal));

    AOStar(root, goal);

    return 0;
}
