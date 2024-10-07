# project-w7-graph-theory
Group 6 Project Graph Theory Demonstration - Graph Theory IUP 2024

|    NRP     |      Name      |
| :--------: | :------------: |
| 5025221065 | Samuel Josefano Kaloh |
| 5025221092 | Rayhan Fathurrahman Zata Amani |
| 5025221097 | Radian Try Darmawan |

# Code Explanation

## A. Travelling Salesman Problem

### Solution Overview
This solution aims to solve the Travelling Salesman Problem (TSP) using backtracking with pruning. TSP is a well-known optimization problem where a salesman must visit every city exactly once and return to the starting city, while minimizing the total travel cost.

### 1. Struct Definition
```cpp
struct Edge {
    int name;
    int u, v;
    int cost;
};
```
The Edge struct represents an edge (road) between two cities:
* name: The identifier of the edge (used for tracking the path).
* u, v: The two cities connected by the edge.
* cost: The cost to travel between cities u and v.

### 2. Global Variables
```cpp
int n, e;
vector<Edge> edges;
vector<vector<Edge>> adj;
int start_node;
long long minimal_total_cost = LLONG_MAX;
vector<int> best_path;
```
* n: Number of cities (nodes).
* e: Number of edges (roads).
* edges: A list of all the edges.
* adj: Adjacency list where adj[i] stores all the edges connected to city i.
* start_node: The city from which the salesman starts and to which he must return.
* minimal_total_cost: Tracks the minimum total travel cost found so far. It’s initialized to LLONG_MAX to ensure that any valid solution will be smaller.
* best_path: Stores the sequence of edge names for the best solution (least total cost).

### 3. TSP Recursive Function
```cpp
void tsp(int curr_node, long long total_cost, vector<int>& path, vector<bool>& visited, int visited_count)
```
This is the main function that performs the backtracking traversal to solve the TSP:
* Parameters:
    * curr_node: The current city (node) the salesman is visiting.
    * total_cost: The total travel cost accumulated so far.
    * path: A vector storing the sequence of edge names used so far.
    * visited: A boolean array marking whether each city has been visited.
    * visited_count: The number of cities visited so far.

### 3.1 Base Case: All Cities Visited
```cpp
if (visited_count == n) {
    for (const Edge& e : adj[curr_node]) {
        int neighbor = (e.u == curr_node) ? e.v : e.u;
        if (neighbor == start_node) {
            total_cost += e.cost;
            path.push_back(e.name);
            if (total_cost < minimal_total_cost) {
                minimal_total_cost = total_cost;
                best_path = path;
            }
            path.pop_back();
            total_cost -= e.cost;
        }
    }
    return;
}
```
Once all cities are visited (visited_count == n), the function attempts to return to the start city:
* It checks each edge connected to the current city (curr_node) to see if it connects back to the start_node.
* If it finds a valid edge, it updates the total cost and compares it with minimal_total_cost.
* If the total cost is lower, it updates minimal_total_cost and stores the current path as the best path.

### 3.2 Recursive Backtracking and Pruning
```cpp
for (const Edge& e : adj[curr_node]) {
    int neighbor = (e.u == curr_node) ? e.v : e.u;
    if (!visited[neighbor]) {
        visited[neighbor] = true;
        total_cost += e.cost;
        path.push_back(e.name);

        if (total_cost >= minimal_total_cost) {
            path.pop_back();
            total_cost -= e.cost;
            visited[neighbor] = false;
            continue;
        }

        tsp(neighbor, total_cost, path, visited, visited_count + 1);

        path.pop_back();
        total_cost -= e.cost;
        visited[neighbor] = false;
    }
}
```
The function recursively explores each unvisited neighboring city (connected by an edge) by:
* Marking the neighbor as visited.
* Adding the edge cost to the total_cost.
* Appending the edge name to the path.
Pruning: If the current total_cost exceeds or equals the minimal_total_cost, the function stops exploring this path (prunes it) to save computation time.
After returning from the recursive call (i.e., after trying a path), the function backtracks by:
* Removing the last edge from the path.
* Subtracting the edge cost from the total cost.
* Marking the neighbor as unvisited.

### 4. Main Function :
```cpp
int main() {
    cin >> n;
    cin >> e;
    edges.resize(e);
    adj.resize(n + 1); // Nodes are numbered from 1 to n

    for (int i = 0; i < e; ++i) {
        int name, u, v, cost;
        cin >> name >> u >> v >> cost;
        edges[i] = {name, u, v, cost};
        adj[u].push_back(edges[i]);
        adj[v].push_back(edges[i]); // Since the graph is undirected
    }

    cin >> start_node;
```
* Input Reading: The number of cities (n), number of edges (e), and each edge with its name, endpoints (u, v), and travel cost (cost) are read from the input. Edges are added to the adjacency list for both cities (adj[u] and adj[v]), since the graph is undirected.
* Finally, the start city (start_node) is read.

### 4.1 Initializing and Solving TSP
```cpp
    vector<bool> visited(n + 1, false);
    visited[start_node] = true;
    vector<int> path;

    tsp(start_node, 0, path, visited, 1);

    cout << "Cost: " << minimal_total_cost << endl;
    cout << "Route: ";
    for (size_t i = 0; i < best_path.size(); ++i) {
        if (i != 0) cout << ", ";
        cout << best_path[i];
    }
    cout << endl;
```
Initialization:

* A visited array is created to track whether a city has been visited. The start_node is marked as visited.
* An empty path vector is initialized to track the edge sequence.
Calling tsp: The function starts the TSP search from start_node with an initial total cost of 0 and 1 city visited.
Output:
* After the search, the minimal cost is printed along with the best path (sequence of edge names) that achieves this minimal cost.

### 5. Summary
* The code solves TSP by recursively visiting cities and using pruning to skip paths that would exceed the minimal cost found so far.
* The backtracking approach ensures that all possible city permutations are considered, but only valid paths that visit each city once and return to the start city are evaluated.



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
