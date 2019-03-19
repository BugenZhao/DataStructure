//
// Created by BugenZhao on 2019/3/3.
//

#include <iostream>
#include <fstream>

using namespace std;

int main() {
    int V, E;

    cin >> V;
    int *sizeOfNode = new int[V];
    int **weightBetweenNode = new int *[V];
    for (int i = 0; i < V; ++i) {
        *(weightBetweenNode + i) = new int[V];
    }
    for (int i = 0; i < V; ++i) {
        cin >> sizeOfNode[i];
    }

    cin >> E;

    for (int j = 0; j < E; ++j) {
        int a, b, w;
        cin >> a >> b >> w;
        weightBetweenNode[a - 1][b - 1] = w;
        weightBetweenNode[b - 1][a - 1] = w;
    }

    /*
     * show the graph...
     */

    delete[] sizeOfNode;
    for (int i = 0; i < V; ++i) {
        delete[] (weightBetweenNode + i);
    }
    delete[] weightBetweenNode;

    return 0;
}
