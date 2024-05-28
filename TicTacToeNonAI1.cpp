#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> board(3, vector<int>(3, 2));
int turn = 1;

int getMagicSquareMove(vector<vector<int>>& board) {
    if (board[1][1] == 2) return 5;
    else {
        if (board[0][1] == 2) {
            return 2;
        }
        else if (board[1][0] == 2) {
            return 4;
        }
        else if (board[2][1] == 2) {
            return 8;
        }
        else if (board[1][2] == 2) {
            return 6;
        }
    }
    return -1;
}

void makeMove(int num, vector<vector<int>>& board) {
    if (turn & 1) {
        board[num / 3][num % 3] = 3;
        turn++;
    }
    else {
        board[num / 3][num % 3] = 5;
        turn++;
    }
}

int checkWin(vector<vector<int>>& board, int player) {
    // rows
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] * board[i][1] * board[i][2] == player * player * 2) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == 2) {
                    return i * 3 + j;
                }
            }
        }
    }

    // columns
    for (int j = 0; j < 3; ++j) {
        if (board[0][j] * board[1][j] * board[2][j] == player * player * 2) {
            for (int i = 0; i < 3; ++i) {
                if (board[i][j] == 2) {
                    return i * 3 + j;
                }
            }
        }
    }

    // diagonal1
    if (board[0][0] * board[1][1] * board[2][2] == player * player * 2) {
        for (int i = 0; i < 3; ++i) {
            if (board[i][i] == 2) {
                return i * 3 + i;
            }
        }
    }
    //diagonal2
    if (board[0][2] * board[1][1] * board[2][0] == player * player * 2) {
        for (int i = 0; i < 3; ++i) {
            if (board[i][2 - i] == 2) {
                return (i * 3) + 2 - i;
            }
        }
    }
    return -1;
}

void playTicTacToe(vector<vector<int>>& board) {
    int position;
    if (turn == 1) {
        makeMove(0, board);
    }
    else if (turn == 2) {
        if (board[1][1] == 2) {
            makeMove(4, board);
        }
        else {
            makeMove(0, board);
        }
    }
    else if (turn == 3) {
        if (board[2][2] == 2) {
            makeMove(8, board);
        }
        else {
            makeMove(3, board);
        }
    }
    else if (turn == 4) {
        position = checkWin(board, 3);
        if (position != -1) {
            makeMove(position, board);
        }
        else {
            makeMove(getMagicSquareMove(board), board);
        }
    }
    else if (turn == 5) {
        position = checkWin(board, 5);
        if (position != -1) {
            makeMove(position, board);
        }
        else {
            position = checkWin(board, 3);
            if (position != -1) {
                makeMove(position, board);
            }
            else if (board[2][2] == 2) {
                makeMove(9, board);
            }
            else {
                makeMove(7, board);
            }
        }
    }
    else if (turn == 6) {
        position = checkWin(board, 5);
        if (position != -1) {
            makeMove(position, board);
        }
        else {
            position = checkWin(board, 3);
            if (position != -1) {
                makeMove(position, board);
            }
            else {
                makeMove(getMagicSquareMove(board), board);
            }
        }
    }
    else if (turn == 7 || turn == 8 || turn == 9) {
        position = checkWin(board, 3);
        if (position != -1) {
            makeMove(position, board);
        }
        else {
            position = checkWin(board, 5);
            if (position != -1) {
                makeMove(position, board);
            }
            else {
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        if (board[i][j] == 2) {
                            makeMove(i * 3 + j, board);
                            return;
                        }
                    }
                }
            }
        }
    }
}

int main() {
    cout << "Welcome to Tic Tac Toe Game" << endl;
    cout << "X-3  O-5" << endl;
    for (int i = 1; i <= 9; i++) {
        playTicTacToe(board);
    }
    for (int i = 0; i < 3; i++) {
        cout << "|";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << "|";
        }
        cout << endl;
    }
    return 0;
}


