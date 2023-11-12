#include <iostream>
#include <vector>

using namespace std;

bool isSafe(vector<vector<int>>& board, int row, int col, int n) {
    // Check if there is a queen in the same column
    for (int i = 0; i < row; ++i) {
        if (board[i][col] == 1) {
            return false;
        }
    }

    // Check if there is a queen in the left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; --i, --j) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    // Check if there is a queen in the right diagonal
    for (int i = row, j = col; i >= 0 && j < n; --i, ++j) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    return true;
}

bool solveNQueensUtil(vector<vector<int>>& board, int row, int n) {
    if (row == n) {
        // All queens are placed successfully
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << (board[i][j] == 1 ? "Q" : ".") << " ";
            }
            cout << endl;
        }
        cout << endl;

        // Print the position of each queen in a new line
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == 1) {
                    cout << "Queen "<< i <<" at position: " << j << endl;
                }
            }
        }

        return true;
    }

    for (int col = 0; col < n; ++col) {
        if (isSafe(board, row, col, n)) {
            // Place the queen and move to the next row
            board[row][col] = 1;

            // Recur to place the rest of the queens
            if (solveNQueensUtil(board, row + 1, n)) {
                return true;
            }

            // If placing the queen in the current position doesn't lead to a solution, backtrack
            board[row][col] = 0;
        }
    }

    // If no column is found to place the queen, return false
    return false;
}

void solveNQueens(int n) {
    // Initialize the chessboard
    vector<vector<int>> board(n, vector<int>(n, 0));

    if (!solveNQueensUtil(board, 0, n)) {
        cout << "No solution exists." << endl;
    }
}

int main() {
   
    int n ;  
    cout<<"Enter the number of Queens : ";
    cin>>n;
    solveNQueens(n);

    return 0;
}
