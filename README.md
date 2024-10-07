# project-w7-graph-theory
Group 6 Project Graph Theory Demonstration - Graph Theory IUP 2024

|    NRP     |      Name      |
| :--------: | :------------: |
| 5025221065 | Samuel Josefano Kaloh |
| 5025221092 | Rayhan Fathurrahman Zata Amani |
| 5025221097 | Radian Try Darmawan |

# Code Explanation

## C. Knight's Tour

### Solution Overview

This solution aims to solve the Knight's Tour problem using Warnsdorff's heuristic. This algorithm tries to visit every square on an 
𝑁 × 𝑀 chessboard exactly once, starting from a given position. The code uses backtracking, but it follows Warnsdorff's rule to improve efficiency by reducing the search space.

### 1. Constant and Variables 
```
const int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
const int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
```
The arrays above represent the 8 possible moves of the knight in chess. The knight moves in an "L" shape: two squares in one direction and one square in a perpendicular direction.

### 2. Structure Definition
```
struct Move {
    int x, y, degree;
};
```
The Move struct stores a possible move for the knight:
* x, y: Coordinates of the move.
* degree: Number of valid onward moves from this position, used to implement Warnsdorff's rule (move to the square with the fewest onward moves).

### 3. IsSafe Function
```
bool isSafe(int x, int y, vector<vector<int>>& board, int N, int M) {
    return (x >= 0 && x < N && y >= 0 && y < M && board[x][y] == -1);
}
```
This function checks if a given position (x, y) is a valid move:
* It ensures that the knight is within the bounds of the chessboard (i.e., 0 <= x < N and 0 <= y < M).
* It also checks if the square has not been visited yet (indicated by board[x][y] == -1).

### 4. GetDegree Function
```
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
```
The getDegree function counts the number of valid onward moves (i.e., the degree) from position (x, y). For each possible knight move, it checks if the new position (nx, ny) is safe using the isSafe function.

### 5. KnightTour Function
```
bool knightTour(int x, int y, int movei, vector<vector<int>>& board, vector<pair<int, int>>& path, int N, int M) {
    if (movei == N * M)
        return true; // All squares are visited
```
This is the main recursive function that attempts to solve the Knight's Tour problem:
* Base Case: If movei (the number of moves made so far) is equal to the total number of squares (N * M), the function returns true, indicating that the tour is complete.

### 5.1 Generating Possible Moves
```
 vector<Move> moves;
    for (int i = 0; i < 8; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (isSafe(nx, ny, board, N, M)) {
            int degree = getDegree(nx, ny, board, N, M);
            moves.push_back({nx, ny, degree});
        }
    }
```
Here, the function generates all valid moves from the current position (x, y). For each possible move, it checks if the move is safe and calculates the number of onward moves from that new position (using getDegree).

### 5.2 Sorting Moves Using Warnsdorff's Rule
```
    sort(moves.begin(), moves.end(), [](const Move& a, const Move& b) {
        return a.degree < b.degree;
    });
```
The valid moves are sorted by their degree (onward moves), following Warnsdorff's rule. This ensures that the knight moves to the square with the fewest onward moves, minimizing the chance of getting stuck.

### 5.3 Trying Each Move
```
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
```
The function tries each move recursively:
* It marks the board at position (m.x, m.y) with the move index (movei).
* It pushes this move to the path and makes the recursive call to knightTour for the next move.
* If this recursive call leads to a solution, the function returns true.
* If a move does not lead to a solution, the function backtracks by marking the square as unvisited (-1) and removing the move from the path.

### 6. Main Function
```
int main() {
    int N, M;
    cin >> N >> M;  // Input board size (N x M)
```
The main function reads the chessboard size 
𝑁 × 𝑀 and the starting position (sx, sy) from the user.

### 6.1 Initializing the Board and Starting Position
```
    vector<vector<int>> board(N, vector<int>(M, -1));
    board[sx][sy] = 0;  // Mark starting position
```
The board is initialized with -1 to indicate unvisited squares, and the starting position is marked as visited (0).

### 6.2 Solving the Knight's Tour
```
    vector<pair<int, int>> path;
    path.push_back({sx, sy});

    if (knightTour(sx, sy, 1, board, path, N, M)) {
        for (const auto& p : path) {
            cout << p.first << " " << p.second << endl;
        }
    } else {
        cout << "No solution found" << endl;
    }
```
* The path vector stores the sequence of moves made by the knight.
* If knightTour finds a solution then path is printed.
* If no solution is found, the program will print "No solution found."

### 7. Summary
* Warnsdorff’s rule is used to guide the knight to squares with the fewest onward moves.
* Backtracking is applied when the algorithm reaches a dead end, undoing moves and trying alternative paths.
* The board is dynamically sized, allowing this solution to work on any 𝑁 × 𝑀 board, not just the standard 8 × 8 chessboard.
