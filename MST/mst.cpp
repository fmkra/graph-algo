#include <iostream>

int n, m;
std::vector<std::pair<int, int>>* g; // (vertex, weight)
std::vector<std::pair<int, std::pair<int, int>>> e; // (weight, (vertex, vertex))

int* parent;
int* rank;

void init() {
    parent = new int[n+1];
    rank = new int[n+1];

    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 1;
    }
}

int find(int u) {
    if (parent[u] == u) return u;
    return parent[u] = find(parent[u]);
}

void merge(int u, int v) {
    u = find(u);
    v = find(v);

    if (u == v) return;

    if (rank[u] < rank[v]) std::swap(u, v);
    parent[v] = u;
    rank[u] += rank[v];
}

int main() {
    std::cin >> n >> m;
    g = new std::vector<std::pair<int, int>>[n+1];
    e.reserve(m);

    while (m--) {
        int u, v, w;
        std::cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
        e.push_back({w, {u, v}});
    }

    std::sort(e.begin(), e.end());

    init();

    int total_weight = 0;
    std::vector<std::pair<int, int>> mst;
    for (auto& p : e) {
        int w = p.first;
        int u = p.second.first;
        int v = p.second.second;

        if (find(u) != find(v)) {
            total_weight += w;
            mst.push_back({u, v});
            merge(u, v);
        }
    }

    std::cout << total_weight << std::endl;
    for (auto& p : mst) {
        std::cout << p.first << " " << p.second << std::endl;
    }
}