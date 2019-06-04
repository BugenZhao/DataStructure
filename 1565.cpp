//
// Created by BugenZhao on 2019/5/17.
//

#include <iostream>
#include <string>

using std::ios, std::cin, std::cout, std::endl, std::string;

constexpr int INF = 0x7fffffff;

int height[1001][1001];
int cost[1001][1001];

int minDist, minCost;

void dijkstra(int V, int start, int end) {
    int *distTo = new int[V + 1];
    int *costTo = new int[V + 1];
    bool *marked = new bool[V + 1]{};
    for (int i = 1; i <= V; ++i) {
        distTo[i] = height[start][i];
        costTo[i] = cost[start][i];
    }
    marked[start] = true;
    for (int i = 1; i <= V && !marked[end]; ++i) {
        int minDist = INF, v;
        for (int j = 1; j <= V; ++j) {
            if (marked[j] || minDist < distTo[j]) continue;
            minDist = distTo[j];
            v = j;
        }
        marked[v] = true;

        relax:
        for (int j = 1; j <= V; ++j) {
            if (marked[j] || height[v][j] == INF) continue;
            int newDist = distTo[v] + height[v][j];
            int newCost = costTo[v] + cost[v][j];
            if (distTo[j] > newDist) {
                distTo[j] = newDist;
                costTo[j] = newCost;
            } else if (distTo[j] == newDist) {
                if (costTo[j] > newCost)
                    costTo[j] = newCost;
            }
        }
    }
    minDist = distTo[end];
    minCost = costTo[end];
    delete[] distTo, costTo, marked;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int V, E;
    cin >> V >> E;
    for (int i = 1; i <= V; ++i) {
        for (int j = 1; j <= V; ++j) {
            if (i != j)
                height[i][j] = cost[i][j] = INF;
        }
    }

    int t1, t2, t3, t4;
    for (int i = 0; i < E; ++i) {
        cin >> t1 >> t2 >> t3 >> t4;
        if (height[t1][t2] > t3) {
            height[t1][t2] = height[t2][t1] = t3;
            cost[t1][t2] = cost[t2][t1] = t4;
        } else if (height[t1][t2] == t3 && cost[t1][t2] > t4) {
            cost[t1][t2] = cost[t2][t1] = t4;
        }
    }

    int s, t;
    cin >> s >> t;
    dijkstra(V, s, t);
    cout << minDist << ' ' << minCost << endl;
    return 0;
}