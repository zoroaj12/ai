#include <bits/stdc++.h>
using namespace std;

#define N 3
struct Node{
    Node* parent;
    int x,y;
    int mat [N][N];
    int depth;
};
struct Node* newnode(int mat[N][N],int x,int y,int newx,int newy,int depth,Node* parent){
    Node* node = new Node;
    node->parent = parent;
    memcpy(node->mat,mat, sizeof(node->mat));
    swap(mat[x][y],mat[newx][newy]);
    node->x = newx;
    node->y = newy;
    node->depth = depth;
}

int row[4]= {0,1,0,-1};
int col[4]={-1,0,1, 0};

void printmatrix(int mat[N][N]){
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout<<mat[i][j]<<" ";
        }
        cout<<endl;
    }
    
}
void printpath(Node * root){
    if (root==nullptr)
        return ;

    printpath(root->parent);
    cout<<"Depth :"<< root->depth<<endl;
    printmatrix(root->mat);
}
bool issafe(int x,int y){
    if (x>=0 && x<N && y>=0 && y<N)
    {
        return true;
    }
    return false;  
}

bool issame(int mat1[N][N],int mat2[N][N]){
     for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (mat1[i][j] != mat2[i][j])
                return false;
    return true;
}
void solve(int initial[N][N],int x,int y,int final[N][N]){
    Node* root= new Node;
    root=newnode(initial,x,y,x,y,0,NULL);
    queue<Node*>q;
    q.push(root);
    while (!q.empty())
    {
        Node * curr=q.front();
        q.pop();
        if (issame(curr->mat,final))
        {
            printpath(curr);
            return;
        }
        
        for (int i = 0; i < 4; i++)
        {
            int newx=curr->x+row[i];
            int newy=curr->y+col[i];
            if (issafe(newx,newy))
            {
                Node * child= newnode(curr->mat,curr->x,curr->y,newx,newy,curr->depth+1,curr);
                q.push(child);
            }
        }
    }
}
int main()
{
    int initial[N][N] =
    {
        {1, 2, 3},
        {5, 6, 0},
        {7, 8, 4}
    };

    int final[N][N] =
    {
        {1, 2, 3},
        {0, 5, 6},
        {7, 8, 4}
    };
     int x = 1, y = 2;
    int depth = 10; 
    solve(initial ,x,y,final);
    return 0;
}
