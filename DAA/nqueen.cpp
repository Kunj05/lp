#include <iostream>
#include <vector>
#include<bits/stdc++.h>

using namespace std;

bool isSafe(const vector<vector<int>>& board, int row, int col, int n) {
    // Check this column on upper side
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 1) {
            return false;
        }
    }

    // Check upper diagonal on left side
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    // Check upper diagonal on right side
    for (int i = row, j = col; i >= 0 && j < n; i--, j++) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    return true;
}

void printBoard(const vector<vector<int>>& board) {
    for (const auto& row : board) {
        for (int cell : row) {
            cout << (cell ? "Q " : ". ");
        }
        cout << endl;
    }
    cout << endl;
}


bool solveNQueensUtil(vector<vector<int>>& board, int row, int n,int &count) {
    // Base case: If all queens are placed
    if (row >= n) {
        printBoard(board);
        count++;
        return true;
    }

    bool foundSolution = false;
    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col, n)) {
            // Place queen
            board[row][col] = 1;
            // Recur to place the next queen
            foundSolution = solveNQueensUtil(board, row + 1, n,count) || foundSolution;
            // Backtrack
            board[row][col] = 0; 
        }
    }
    return foundSolution;
}

void solveNQueens(int n) {
    int count=0;
    vector<vector<int>> board(n, vector<int>(n, 0));
    if (!solveNQueensUtil(board, 0, n,count)) {
        cout << "No solution exists" << endl;
    }
    cout<<"\n Count of total : "<<count<<endl;
}

int main() {
    int n;
    cout << "Enter the number of queens: ";
    cin >> n;
    solveNQueens(n);
    return 0;
}

// 1 Queen (1x1 board): 1 solution
// 2 Queens (2x2 board): 0 solutions
// 3 Queens (3x3 board): 0 solutions
// 4 Queens (4x4 board): 2 solutions
// 5 Queens (5x5 board): 10 solutions
// 6 Queens (6x6 board): 4 solutions
// 7 Queens (7x7 board): 40 solutions
// 8 Queens (8x8 board): 92 solutions
// 9 Queens (9x9 board): 352 solutions
// 10 Queens (10x10 board): 724 solutions
