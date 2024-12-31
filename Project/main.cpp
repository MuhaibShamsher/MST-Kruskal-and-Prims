#include<iostream>
#include "prims.h"
#include "kruskal.h"
using namespace std;

int main() {
    vector<vector<int>> points = {{0, 0}, {2, 2}, {3, 10}, {5, 2}, {7, 0}};

    int vertices = points.size();
    
    // By Kruskal implementation
    auto graph1 = kruskalGraph(points, vertices);
    kruskalMST(graph1, vertices);

    // By Prims implementation
    auto graph2 = primsGraph(points, vertices);
    primsMST(graph2, vertices);


    return 0;
}