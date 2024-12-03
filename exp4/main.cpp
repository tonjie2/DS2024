#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

// 定义图的数据结构
class Graph {
private:
    int vertices; // 顶点数量
    vector<vector<pair<int, int>>> adjList; // 邻接表，存储<邻居, 权重>

public:
    Graph(int v) : vertices(v), adjList(v) {}

    void addEdge(int u, int v, int weight = 1) {
        adjList[u].push_back({ v, weight });
        adjList[v].push_back({ u, weight }); // 对于无向图
    }

    // BFS
    void BFS(int start) {
        vector<bool> visited(vertices, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);

        cout << "BFS: ";
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            cout << curr << " ";

            for (auto neighbor : adjList[curr]) {
                int next = neighbor.first;
                if (!visited[next]) {
                    visited[next] = true;
                    q.push(next);
                }
            }
        }
        cout << endl;
    }

    // DFS
    void DFSUtil(int node, vector<bool>& visited) {
        visited[node] = true;
        cout << node << " ";

        for (auto neighbor : adjList[node]) {
            int next = neighbor.first;
            if (!visited[next]) {
                DFSUtil(next, visited);
            }
        }
    }

    void DFS(int start) {
        vector<bool> visited(vertices, false);
        cout << "DFS: ";
        DFSUtil(start, visited);
        cout << endl;
    }

    // Dijkstra算法
    void dijkstra(int start) {
        vector<int> dist(vertices, INT_MAX);
        dist[start] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({ 0, start });

        while (!pq.empty()) {
            int currDist = pq.top().first;
            int curr = pq.top().second;
            pq.pop();

            for (auto neighbor : adjList[curr]) {
                int next = neighbor.first;
                int weight = neighbor.second;

                if (currDist + weight < dist[next]) {
                    dist[next] = currDist + weight;
                    pq.push({ dist[next], next });
                }
            }
        }

        cout << "Dijkstra算法 " << start << ": ";
        for (int i = 0; i < vertices; ++i) {
            cout << (dist[i] == INT_MAX ? -1 : dist[i]) << " ";
        }
        cout << endl;
    }

    // Prim算法
    void prim() {
        vector<int> key(vertices, INT_MAX);
        vector<bool> inMST(vertices, false);
        vector<int> parent(vertices, -1);
        key[0] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({ 0, 0 });

        while (!pq.empty()) {
            int curr = pq.top().second;
            pq.pop();
            inMST[curr] = true;

            for (auto neighbor : adjList[curr]) {
                int next = neighbor.first;
                int weight = neighbor.second;

                if (!inMST[next] && weight < key[next]) {
                    key[next] = weight;
                    pq.push({ key[next], next });
                    parent[next] = curr;
                }
            }
        }

        cout << "Prim算法:" << endl;
        for (int i = 1; i < vertices; ++i) {
            if (parent[i] != -1)
                cout << parent[i] << " - " << i << endl;
        }
    }
};


int main() {
    Graph g(8);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 4);
    g.addEdge(0, 4, 1);
    g.addEdge(1, 3, 7);
    g.addEdge(1, 4, 3);
    g.addEdge(3, 5, 1);
    g.addEdge(4, 5, 8);
    g.addEdge(2, 6, 6);
    g.addEdge(6, 7, 5);
    g.addEdge(5, 7, 4);

    // 测试 BFS 和 DFS
    g.BFS(0);
    g.DFS(0);

    // 测试最短路径
    g.dijkstra(0);

    // 测试最小生成树
    g.prim();

    return 0;
}
