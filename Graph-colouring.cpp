#include <bits/stdc++.h>
using namespace std;

#define V 4

void printSolution(int color[]);

bool isSafe(int v, vector<vector<int>> graph, int color[], int c)
{
    for (int i = 0; i < V; i++)
        if (graph[v][i] && c == color[i])
            return false;

    return true;
}

void graphColouring(vector<vector<int>>graph,int m,int colour[],int i){
    if(i==graph.size()){
        printSolution(colour);
        return;
    }
    for (int c =1; c <= m; c++)
    {
        if (isSafe(i,graph,colour,c))
        {
            colour[i]=c;
            graphColouring(graph,m,colour,i);
            colour[i]=0;
            cout<<"Backtracking from vertex"<< i<<endl; 
        }
    }
}


void printSolution(int color[])
{
    cout << "\nSolution Exists: Following are the assigned colors"<<endl;
    for (int i = 0; i < V; i++)
        cout << " " << color[i] << " ";
    cout << endl;
}

int main()
{
    int v;
    cout<<"Enter Number of Vertices: "<<endl;
    cin>>v;
    vector<vector<int>> graph(v,vector<int>(v,0));
    int e;
    cout<<"Enter Number of Edges: "<<endl;
    cin >>e;
    for (int i = 0; i < e; i++)
    {
        int v1,v2;
        cout<<"Enter vertices for edge"<<i+1<<" :"<<endl;
        cin >>v1;
        cin >>v2;
        graph[v1][v2]=graph[v2][v1]=1;
    }
    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
        {
            cout<<graph[i][j]<<" ";
        }
        cout<<endl;
    }
    
    int m = 4;
    int colour[v]={0};
    graphColouring(graph, m,colour,0);
    return 0;
}
