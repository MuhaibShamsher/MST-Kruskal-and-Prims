#include<iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

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
        cout << edge.u << "-" << edge.v << "\t" << edge.weight << "\n";
        totalWeight += edge.weight;
    }

    cout << "Total Weight of MST using Kruskal implementation: " << totalWeight << endl << endl;
}

void kruskalMST(vector<Edge> edges, int V) {
    DSU dsu(V);
    vector<Edge> mst;

    sort(edges.begin(), edges.end());

    for (const Edge& edge : edges)
    {
        if (dsu.find(edge.u) != dsu.find(edge.v)) {
            dsu.unite(edge.u, edge.v);
            mst.push_back(edge);
        }
    }

    printMST(mst);
}

int findEdge(vector<int> point1, vector<int> point2) {
    return abs(point1[0] - point2[0]) + abs(point1[1] - point2[1]);
}

vector<Edge> kruskalGraph(vector<vector<int>>& points, int& vertices) {
    vertices = points.size();
    vector<Edge> edges;

    for (int i=0; i<vertices; i++)
    {
        for (int j=i+1; j<vertices; j++)
        {
            int dist = findEdge(points[i], points[j]);
            edges.push_back({i, j, dist});
        }
    }

    return edges;
}