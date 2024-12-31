#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

void printMST(const vector<int>& parent, const vector<vector<int>>& graph, int V)
{
    int totalWeight = 0;
    cout<<"Edge \tWeight\n";

    for (int i = 1; i < V; i++)
    {
        cout << parent[i] << " - " << i << "\t" << graph[parent[i]][i] << "\n";
        totalWeight += graph[parent[i]][i];
    }

    cout<<"Total Weight of MST: "<<totalWeight<<endl;
}

int selectMinVertex(vector<int>& value, vector<bool>& setMST, int V)
{
    int minimum = INT_MAX;
    int vertex;

    for (int i = 0; i < V; ++i) {
        if (!setMST[i] && value[i] < minimum) {
            minimum = value[i];
            vertex = i;
        }
    }
    return vertex;
}

void findMST(vector<vector<int>>& graph, int V)
{
    vector<int> parent(V, -1);
    vector<int> value(V, INT_MAX);
    vector<bool> setMST(V, false);

    // Start from the first vertex
    value[0] = 0;

    // Form MST with (V-1) edges
    for (int i = 0; i < V - 1; i++)
    {
        int U = selectMinVertex(value, setMST, V);
        setMST[U] = true;

        for (int j = 0; j < V; ++j)
        {
            if (graph[U][j] != 0 && setMST[j] == false && graph[U][j] < value[j]) {
                value[j] = graph[U][j];
                parent[j] = U;
            }
        }
    }

    printMST(parent, graph, V);
}

vector<vector<int>> loadGraph(const string& filename, int& vertices)
{
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open file\n";
        return {};
    }

    file >> vertices;
    vector<vector<int>> graph(vertices, vector<int>(vertices, 0));

    int u, v, weight;
    while (file >> u >> v >> weight) {
        graph[u][v] = weight;
        graph[v][u] = weight;
    }

    file.close();
    return graph;
}

int main() {
    int vertices;
    auto graph = loadGraph("graph.txt", vertices);

    if (graph.empty()) {
        cerr << "Graph is empty or not loaded correctly.\n";
        return 1;
    }

    auto start = high_resolution_clock::now();
    findMST(graph, vertices);
    auto end = high_resolution_clock::now();
    
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Time taken by Prim's MST: " << duration.count() << " microseconds" << endl;

    return 0;
}