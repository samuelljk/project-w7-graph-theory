#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Possible moves a knight can make
const int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
const int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

struct Move {
    int x, y, degree;
};

// Function to check if the position is within the board and not yet visited
bool isSafe(int x, int y, vector<vector<int>>& board, int N, int M) {
    return (x >= 0 && x < N && y >= 0 && y < M && board[x][y] == -1);
}

// Function to count the number of possible onward moves from a position
int getDegree(int x, int y, vector<vector<int>>& board, int N, int M) {
    int count = 0;
    for (int i = 0; i < 8; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (isSafe(nx, ny, board, N, M))
            count++;
    }
    return count;
}

// Recursive function implementing Warnsdorff's algorithm
bool knightTour(int x, int y, int movei, vector<vector<int>>& board, vector<pair<int, int>>& path, int N, int M) {
    if (movei == N * M)
        return true; // All squares are visited

    // Generate possible moves
    vector<Move> moves;
    for (int i = 0; i < 8; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (isSafe(nx, ny, board, N, M)) {
            int degree = getDegree(nx, ny, board, N, M);
            moves.push_back({nx, ny, degree});
        }
    }

    // Sort moves according to the degree (Warnsdorff's rule)
    sort(moves.begin(), moves.end(), [](const Move& a, const Move& b) {
        return a.degree < b.degree;
    });

    // Try each move
    for (const Move& m : moves) {
        board[m.x][m.y] = movei;
        path.push_back({m.x, m.y});
        if (knightTour(m.x, m.y, movei + 1, board, path, N, M))
            return true;
        // Backtrack
        board[m.x][m.y] = -1;
        path.pop_back();
    }
    return false;
}

int main() {
    int N, M;
    // Read board size
    cin >> N >> M;

    // Read starting position
    int sx, sy;
    cin >> sx >> sy;

    // Initialize the board
    vector<vector<int>> board(N, vector<int>(M, -1));

    // Mark starting position
    board[sx][sy] = 0;

    // Store the path
    vector<pair<int, int>> path;
    path.push_back({sx, sy});

    // Start the tour
    if (knightTour(sx, sy, 1, board, path, N, M)) {
        // Output the path
        for (const auto& p : path) {
            cout << p.first << " " << p.second << endl;
        }
    } else {
        cout << "No solution found" << endl;
    }

    return 0;
}
