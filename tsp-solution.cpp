#include <iostream>
#include <vector>
#include <limits.h>
#include <unordered_set>

using namespace std;

struct Edge {
    int name;
    int u, v;
    int cost;
};

int n, e;
vector<Edge> edges;
vector<vector<Edge>> adj;
int start_node;
long long minimal_total_cost = LLONG_MAX;
vector<int> best_path;

void tsp(int curr_node, long long total_cost, vector<int>& path, vector<bool>& visited, int visited_count) {
    if (visited_count == n) {
        // Try to return to start node
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

    for (const Edge& e : adj[curr_node]) {
        int neighbor = (e.u == curr_node) ? e.v : e.u;
        if (!visited[neighbor]) {
            visited[neighbor] = true;
            total_cost += e.cost;
            path.push_back(e.name);

            if (total_cost >= minimal_total_cost) {
                // Prune
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
}

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

    return 0;
}
