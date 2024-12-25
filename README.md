# Kruskal-s-algorithm
Kruskal’s algorithm With C++


Pseudocode for Kruskal’s Algorithm

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
            parent[x] = find(parent[x]); // Path compression
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX != rootY) {
            // Union by rank
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
        // Check if adding this edge forms a cycle
        if (uf.find(u) != uf.find(v)) {
            uf.unite(u, v);
            mst.push_back(edge);  // Add edge to MST
        }
    }

    return mst;
}


Part (b): Algorithm Analysis
Time Complexity:
Sorting the edges: Sorting takes 
O(ElogE), where 
E is the number of edges.
Union-Find Operations:
The find and unite operations have an amortized time complexity of 
O(α(V)), where 
α is the inverse Ackermann function, which grows extremely slowly and is considered almost constant for practical values of 

There are at most 

E find or unite operations.
Hence, the overall time complexity of Kruskal’s algorithm is 

O(ElogE+Eα(V)). Since 

α(V) is very small, the complexity is approximately 

O(ElogE).

Space Complexity:
The space used by the Union-Find structure is 

O(V) for the parent and rank arrays.
The space required to store the edges is 

O(E).
Thus, the overall space complexity is 

O(V+E).
