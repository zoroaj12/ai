#include <bits/stdc++.h>
using namespace std;

#define N 3

struct Node {
    int mat[N][N];
    int x, y;
    int cost;
    Node* parent;
    string action;
};

Node* newNode(int mat[N][N], int x, int y, int newX, int newY, Node* parent, string action) {
    Node* node = new Node;
    node->parent = parent;
    node->x = newX;
    node->y = newY;
    node->cost = 0;
    node->action = action;
    memcpy(node->mat,mat,sizeof(node->mat));
    swap(node->mat[x][y], node->mat[newX][newY]);

    return node;
}

bool isEqual(int mat1[N][N], int mat2[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (mat1[i][j] != mat2[i][j]) return false;
        }
    }
    return true;
}

void printMat(int mat[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void printSolution(Node* node) {
    if (node == NULL) {
        return;
    }
    printSolution(node->parent);
    if (!node->action.empty()) {
        cout << "Action: " << node->action << endl;
    }
    printMat(node->mat);
}

bool isSafe(int x, int y) {
    return (x >= 0 && y >= 0 && x < N && y < N);
}

int calculateCost(int initial[N][N], int final[N][N]) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (initial[i][j] && initial[i][j] != final[i][j]) {
                count++;
            }
        }
    }
    return count;
}

bool hillClimbing(Node* root, int final[N][N]) {
    int row[] = { -1, 0, 1, 0 };
    int col[] = { 0, -1, 0, 1 };
    string actions[] = { "Up", "Left", "Down", "Right" };

    Node* current = root;
    current->cost = calculateCost(current->mat, final);

    while (current->cost != 0) {
        Node* nextMove = NULL;
        int minCost = INT_MAX;

        for (int i = 0; i < 4; i++) {
            int newX = current->x + row[i];
            int newY = current->y + col[i];

            if (isSafe(newX, newY)) {
                Node* child = newNode(current->mat, current->x, current->y, newX, newY, current, actions[i]);
                child->cost = calculateCost(child->mat, final);

                if (child->cost < minCost) {
                    minCost = child->cost;
                    nextMove = child;
                }
            }
        }

        if (nextMove == NULL || nextMove->cost >= current->cost) {
            cout << "No better state found, terminating." << endl;
            return false;
        }

        current = nextMove;
    }

    printSolution(current);
    return true;
}

int main() {
    int initial[N][N] = {
        {1, 2, 3},
        {5, 6, 0},
        {7, 8, 4}
    };

    int final[N][N] = {
        {1, 2, 3},
        {7, 5, 6},
        {8, 4, 0}
    };

    int x = 1, y = 2;

    Node* root = newNode(initial, x, y, x, y, NULL, "");

    if (!hillClimbing(root, final)) {
        cout << "Solution not found using Hill Climbing." << endl;
    }

    return 0;
}
