#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int src, dest, weight;
};

void bellmanFord(int V, int E, const vector<Edge>& edges, int source) {
    vector<int> distances(V, INT_MAX);
    distances[source] = 0;

    for (int i = 1; i <= V - 1; ++i) {
        for (const auto& edge : edges) {
            int u = edge.src;
            int v = edge.dest;
            int w = edge.weight;

            if (distances[u] != INT_MAX && distances[u] + w < distances[v]) {
                distances[v] = distances[u] + w;
            }
        }
    }

    // Check for negative-weight cycles
    for (const auto& edge : edges) {
        int u = edge.src;
        int v = edge.dest;
        int w = edge.weight;

        if (distances[u] != INT_MAX && distances[u] + w < distances[v]) {
            cout << "Graph contains negative-weight cycle\n";
            return;
        }
    }

    // Print the distances
    cout << "Vertex   |   Distance from Source\n";
    for (int i = 0; i < V; ++i) {
        cout << i << "\t\t" << distances[i] << "\n";
    }
}

int main() {
    int V, E;

    cout << "Enter the number of vertices: ";
    cin >> V;

    cout << "Enter the number of edges: ";
    cin >> E;

    vector<Edge> edges;

    cout << "Enter the edges in the format (source destination weight):\n";
    for (int i = 0; i < E; ++i) {
        Edge edge;
        cin >> edge.src >> edge.dest >> edge.weight;
        edges.push_back(edge);
    }

    int sourceVertex;
    cout << "Enter the source vertex: ";
    cin >> sourceVertex;

    bellmanFord(V, E, edges, sourceVertex);

    return 0;
}
