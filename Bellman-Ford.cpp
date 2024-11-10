#include<bits/stdc++.h>
using namespace std;

void BellmanFord(int V, int E, vector<vector<int>>& edges, int src) {
   
    vector<int> dist(V, INT_MAX);
    dist[src] = 0; 

    // Step 2: Relax all edges (V - 1) times
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j][0];  // Source vertex
            int v = edges[j][1];  // Destination vertex
            int weight = edges[j][2];  // Weight of the edge

            // If the current distance to vertex u is not INF, and if the path
            // through u offers a shorter path to v, update the distance to v.
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    // Step 3: Check for negative weight cycles
    for (int i = 0; i < E; i++) {
        int u = edges[i][0];  // Source vertex
        int v = edges[i][1];  // Destination vertex
        int weight = edges[i][2];  // Weight of the edge
        
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            cout << "Graph contains negative weight cycle!" << endl;
            return;
        }
    }

    // Step 4: Print the distance array
    cout << "Vertex Distance from Source" << endl;
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX) {
            cout << "INF ";
        } else {
            cout << dist[i] << " ";
        }
    }
    cout << endl;
}

int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    vector<vector<int>> edges(E, vector<int>(3));

    cout << "Enter the edges (u, v, weight):" << endl;
    for (int i = 0; i < E; i++) {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2]; 
    }

    int src;
    cout << "Enter the source vertex: ";
    cin >> src;

    BellmanFord(V, E, edges, src);
    return 0;
}