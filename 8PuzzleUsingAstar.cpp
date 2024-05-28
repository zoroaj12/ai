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

struct CompareNode{
    bool operator()(Node* a,Node* b){
        return( a->cost > b->cost);
    }
};

void solve(int intial[N][N],int x,int y,int final[N][N]){
    priority_queue<Node*,vector<Node*>,CompareNode>q;
    Node * root= new Node;
    root=newNode(intial,x,y,x,y,0,NULL,"");
    q.push(root);
    root->cost=0+ heuristics(root->mat,final);
    while (!q.empty())
    {
        Node * curr= q.top();
        q.pop();
        if (isGoalState(curr->mat,final))
        {
            cout<<"Goal State Achieved: "<<endl;
            printPath(curr);
            return ;
        }
        int row[4]={0 ,-1, 0, 1};
        int col[4]={-1,0,1,0};
        vector<string> direction={"Left","Up","Right","Down"};
        for (int i = 0; i < 4; i++)
        {
            int newx=curr->x+row[i];
            int newy=curr->y+col[i];
            if (newx>=0 && newx<N && newy>=0 && newy<N)
            {
                Node * child=newNode(curr->mat,curr->x,curr->y,newx,newy,curr->depth+1,curr,direction[i]);
                child->cost=child->depth+heuristics(child->mat,final);
                q.push(child);
            }
        }
    }
    cout<<"goal State Not Achieved"<<endl;
}
int main() {
      int initial[N][N] = {{2, 8, 3},
                         {1, 6, 4},
                         {7, 0, 5}};

    int goal[N][N] = {{1, 2, 3},
                      {8, 0, 4},
                      {7, 6, 5}};


    int x = 2, y = 1 ;  
    solve(initial, x, y, goal);

    return 0;
}