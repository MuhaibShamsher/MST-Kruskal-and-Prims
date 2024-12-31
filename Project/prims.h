#include<iostream>
#include <vector>
using namespace std;

void printMST(const vector<int>& parent, const vector<vector<int>>& graph, int V) {
    int totalWeight = 0;
    cout<<"Edge \tWeight\n";

    for (int i = 1; i < V; i++)
    {
        cout << parent[i] << "-" << i << "\t" << graph[parent[i]][i] << "\n";
        totalWeight += graph[parent[i]][i];
    }

    cout<<"Total Weight of MST using Prims implementation: "<<totalWeight<<endl;
}

int selectMinVertex(vector<int>& value, vector<bool>& setMST, int V) {
    int minimum = INT_MAX;
    int vertex;

    for (int i = 0; i < V; ++i) {
        if (setMST[i] == false && value[i] < minimum) {
            minimum = value[i];
            vertex = i;
        }
    }
    return vertex;
}

void primsMST(vector<vector<int>>& graph, int V) {
    vector<int> parent(V, -1);
    vector<int> value(V, INT_MAX);
    vector<bool> setMST(V, false);

    value[0] = 0;

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

int edge(vector<int> point1, vector<int> point2) {
    return abs(point1[0] - point2[0]) + abs(point1[1] - point2[1]);
}

vector<vector<int>> primsGraph(vector<vector<int>>& points, int& vertices) {
    vertices = points.size();

    vector<vector<int>> graph(vertices, vector<int>(vertices, 0));

    for (int i=0; i<vertices; i++)
    {
        for (int j=i+1; j<vertices; j++)
        {
            int dist = edge(points[i], points[j]);
            graph[i][j] = dist;
            graph[j][i] = dist;
        }
    }

    return graph;
}