#include <iostream>

int n,m;
std::vector<int>* g;
std::vector<int>* children;
std::vector<int>* forward_edges;
int* p;

bool* vis;
int* depth;
int* low;
std::vector<int> articulation_points;
std::vector<std::pair<int,int>> bridges;

void dfs_precompute(int v) {
    vis[v] = 1;
    for(int u : g[v]) {
        if(u == p[v]) continue;
        if(p[u]) {
            if(vis[u]) forward_edges[v].push_back(u);
            continue;
        }
        children[v].push_back(u);
        p[u] = v;
        depth[u] = depth[v]+1;
        dfs_precompute(u);
    }
    vis[v] = 0;
}

void dfs_low(int v) {
    low[v] = depth[v];
    for(int u : forward_edges[v]) {
        low[v] = std::min(low[v],depth[u]);
    }
    for(int u : children[v]) {
        dfs_low(u);
        low[v] = std::min(low[v],low[u]);
    }

    bool is_articulation = false;
    for(int u : children[v]) {
        if(low[u] > depth[v]) {
            bridges.push_back({v,u});
        }
        if(low[u] >= depth[v]) is_articulation = true;
    }
    if(p[v] == v ? children[v].size() > 1 : is_articulation) {
        articulation_points.push_back(v);
    }
}

int main() {
    std::cin>>n>>m;
    g = new std::vector<int>[n+1];
    while(m--) {
        int a,b;
        std::cin>>a>>b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    p = new int[n+1];
    vis = new bool[n+1];
    depth = new int[n+1];
    low = new int[n+1];
    children = new std::vector<int>[n+1];
    forward_edges = new std::vector<int>[n+1];
    for(int i=1;i<=n;i++) p[i] = vis[i] = 0;
    for(int i=1;i<=n;i++) {
        if(p[i]) continue;
        p[i] = i;
        depth[i] = 0;
        dfs_precompute(i);
    }

    for(int i=1;i<=n;i++) {
        if(p[i] == i) dfs_low(i);
    }

    std::cout<<"Articulation points: ";
    for(int v : articulation_points) std::cout<<v<<" ";
    std::cout<<"\nBridges: ";
    for(auto [a,b] : bridges) std::cout<<"("<<a<<","<<b<<") ";
}