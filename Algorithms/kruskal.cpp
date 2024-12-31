#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;  // Sorting edges by weight
    }
};

// Disjoint Set Union (DSU) or Union-Find structure for Kruskal's algorithm
class DSU {
    vector<int> parent, rank;

public:
    DSU(int n) {
        parent.resize(n, -1);
        rank.resize(n, 0);
    }

    int find(int u) {
        if (parent[u] == -1) {
            return u;
        }
        
        return parent[u] = find(parent[u]);
    }

    void unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);

        if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
};

void printMST(vector<Edge> mst) {
    int totalWeight = 0;

    cout << "Edge \tWeight\n";
    for (const Edge& edge : mst)
    {
        cout << edge.u << " - " << edge.v << "\t" << edge.weight << "\n";
        totalWeight += edge.weight;
    }

    cout << "Total Weight of MST: " << totalWeight << endl;
}

void kruskalMST(vector<Edge> edges, int V) {
    DSU dsu(V);
    vector<Edge> mst;

    sort(edges.begin(), edges.end());

    // Iterate over sorted edges and pick edges that don't form a cycle
    for (const Edge& edge : edges)
    {
        if (dsu.find(edge.u) != dsu.find(edge.v)) {
            dsu.unite(edge.u, edge.v);
            mst.push_back(edge);
        }
    }

    printMST(mst);
    return;
}

vector<Edge> loadGraph(const string& filename, int& vertices) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Unable to open file\n";
        return {};
    }

    file >> vertices;
    vector<Edge> edges;
    int u, v, weight;

    while (file >> u >> v >> weight) {
        edges.push_back({u, v, weight});
    }

    file.close();
    return edges;
}

int main() {
    int vertices;
    auto edges = loadGraph("graph.txt", vertices);

    if (edges.empty()) {
        cerr << "Graph is empty or not loaded correctly.\n";
        return 1;
    }

    auto start = high_resolution_clock::now();
    kruskalMST(edges, vertices);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    cout << "Time taken by Kruskal's MST: " << duration.count() << " microseconds" << endl;

    return 0;
}