#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isSafe(vector<string> &board, int row, int col, int n) {
        // Check column
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 'Q') return false;
        }

        // Check left diagonal
        for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q') return false;
        }

        // Check right diagonal
        for (int i = row, j = col; i >= 0 && j < n; i--, j++) {
            if (board[i][j] == 'Q') return false;
        }

        return true;
    }

    void nQueens(vector<string> &board, int row, int n, vector<vector<string>> &ans) {
        if (row == n) {
            ans.push_back(board);
            return;
        }
        for (int j = 0; j < n; j++) {
            if (isSafe(board, row, j, n)) {
                board[row][j] = 'Q';     // place queen
                nQueens(board, row + 1, n, ans);
                board[row][j] = '.';     // backtrack
            }
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<string> board(n, string(n, '.'));
        vector<vector<string>> ans;
        nQueens(board, 0, n, ans);
        return ans;
    }
};

int main() {
    int n;
    cout << "Enter value of N: ";
    cin >> n;

    Solution solver;
    vector<vector<string>> solutions = solver.solveNQueens(n);

    cout << "Number of solutions: " << solutions.size() << "\n\n";
    for (int k = 0; k < solutions.size(); k++) {
        cout << "Solution " << k + 1 << ":\n";
        for (string row : solutions[k]) {
            cout << row << "\n";
        }
        cout << "\n";
    }

    return 0;
}
