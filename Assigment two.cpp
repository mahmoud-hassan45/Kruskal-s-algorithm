#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class UnionFind {
public:
    vector<int> parent, rank;

    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);  
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY])
                parent[rootY] = rootX;
            else if (rank[rootX] < rank[rootY])
                parent[rootX] = rootY;
            else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

struct Edge {
    int u, v, weight;
    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
};


vector<Edge> kruskal(int V, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), [](Edge& e1, Edge& e2) {
        return e1.weight < e2.weight;
        });

    UnionFind uf(V);
    vector<Edge> mst;

    for (Edge& edge : edges) {
        int u = edge.u, v = edge.v, weight = edge.weight;
        if (uf.find(u) != uf.find(v)) {
            uf.unite(u, v);
            mst.push_back(edge); 
        }
    }

    return mst;
}

int main() {
    int V = 4; 
    vector<Edge> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    vector<Edge> mst = kruskal(V, edges);

    cout << "Edges in the MST: \n";
    for (Edge& e : mst) {
        cout << e.u << " - " << e.v << " : " << e.weight << endl;
    }

    return 0;
}
