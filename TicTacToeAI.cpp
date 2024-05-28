#include<iostream>
using namespace std;
#include <limits.h>

int board[9]={2,2,2,2,2,2,2,2,2};
int win[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
void printBoard(){
    cout<<"Current Board Position: \n";
    string ele;
    cout<<"-------------\n";
    for(int i=0; i<9; i++){
        if(board[i]==2) ele = "   ";
        if(board[i]==3) ele = " X ";
        if(board[i]==5) ele = " O ";
        cout<<"|"<<ele;
        if((i+1)%3==0) cout<<"|"<<'\n'<<"-------------\n";
    }
}
int winner(int x){
    for(int i=0; i<8; i++){
        int c=0;
        for(int j=0; j<3; j++){
            if(board[win[i][j]] == x) c++;
        }
        if (c==3) return 1;
    }
    return 0;
}
void playerMove(){
    int pos;
    cin>>pos;
    if(board[pos]==2) board[pos]=3;
    else {
        cout<<"Position is already Fiiled";
        playerMove();
    }
}
int isWin(int x){
    for(int i=0; i<8; i++){
        int c=0;
        for(int j=0; j<3; j++){
            if(board[win[i][j]] == x) c++;
        }
        if (c==3) return 1;
    }
    return 0;
}
int draw(){
    for(int i=0; i<8; i++){
        if(board[i]==2) return 0;
    }
    return 1;
}
int minimax(bool isMaximizing){
    if(winner(5)) return 1;
    if(winner(3)) return -1;
    if(draw()) return 0;

    if(isMaximizing){
        int bestScore=INT_MIN;
        for (int i = 0; i < 9; i++)
        {
            if(board[i]==2){
                board[i]=5;
                int score = minimax(false);
                bestScore = max(score,bestScore);
                board[i]=2;
            }
        }
        return bestScore;
        
    }else{
        int bestScore=INT_MAX;
        for (int i = 0; i < 9; i++)
        {
            if(board[i]==2){
                board[i]=3;
                int score = minimax(true);
                bestScore = min(score,bestScore);
                board[i]=2;
            }
        }
        return bestScore;
    }
}
void compMove(){
    int bestPos =0;
    int bestScore=INT_MIN;
    for(int i=0; i<9; i++){
        if(board[i]==2) {
            board[i]=5;
            int score = minimax(false);
            board[i]=2;
            if(score>bestScore){
                bestScore = score;
                bestPos = i;
            }
        }
       
    }
     board[bestPos] = 5;
}
int main(){
    while(1){
        cout<<"Enter User Move: "<<endl;
        playerMove();
        printBoard();
        if(isWin(3)) break;
        if(draw()) break;
        
        compMove();
        printBoard();
        if(isWin(5)) break;
        if(draw()) break;
    }
}