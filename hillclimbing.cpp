#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

struct Point {
    int x, y;
};

double distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// Function to generate neighbors of a given point
vector<Point> getNeighbors(Point current, int gridSize) {
    vector<Point> neighbors;
    if (current.x + 1 < gridSize) {
        neighbors.push_back({current.x + 1, current.y});
    }
    if (current.x - 1 >= 0) {
        neighbors.push_back({current.x - 1, current.y});
    }
    if (current.y + 1 < gridSize) {
        neighbors.push_back({current.x, current.y + 1});
    }
    if (current.y - 1 >= 0) {
        neighbors.push_back({current.x, current.y - 1});
    }
    return neighbors;
}

// Function to perform hill climbing
vector<Point> hillClimbing(Point start, Point goal, int gridSize, const vector<vector<int>> &grid) {
    vector<Point> path;
    Point current = start;

    while (current.x != goal.x || current.y != goal.y) {
        double minDistance = distance(current, goal);
        Point nextMove = current;

        // Generate neighbors
        vector<Point> neighbors = getNeighbors(current, gridSize);

        // Evaluate neighbors
        for (const auto &neighbor : neighbors) {
            if (grid[neighbor.x][neighbor.y] == 1) {
                continue; // Skip obstacles
            }
            double dist = distance(neighbor, goal);
            if (dist < minDistance) {
                minDistance = dist;
                nextMove = neighbor;
            }
        }

        // If no better move is found, break (stuck in a local minimum)
        if (nextMove.x == current.x && nextMove.y == current.y) {
            cout << "Stuck in local minimum at (" << current.x << ", " << current.y << ")" << endl;
            break;
        }

        // Move to the next best position
        current = nextMove;
        path.push_back(current);
    }

    return path;
}

int main() {
    Point start = {0, 0};
    Point goal = {4, 4};
    int gridSize = 5;

    // Create a grid with obstacles
    vector<vector<int>> grid(gridSize, vector<int>(gridSize, 0));
    grid[2][1] = 1; // Obstacle at (2,1)
    grid[2][2] = 1; // Obstacle at (2,2)
    grid[2][3] = 1; // Obstacle at (2,3)

    vector<Point> path = hillClimbing(start, goal, gridSize, grid);

    cout << "Path: ";
    for (const auto &point : path) {
        cout << "(" << point.x << ", " << point.y << ") ";
    }
    cout << endl;

    return 0;
}