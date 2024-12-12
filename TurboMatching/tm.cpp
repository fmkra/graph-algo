#include <iostream>

int n,k,m;
std::vector<int>* edges;
int* pair;
int* vis;
int vis_index = 0;

bool match(int v) {
    vis[v] = vis_index;
    for(int u : edges[v]) {
        if(!pair[u]) {
            pair[u] = v;
            return true;
        }
    }
    for(int u : edges[v]) {
        if(vis[pair[u]] != vis_index && match(pair[u])) {
            pair[u] = v;
            return true;
        }
    }
    return false;
}

int main() {
    std::cin>>n>>m;
    edges = new std::vector<int>[n+1];
    while(m--) {
        int a,b;
        std::cin>>a>>b;
        edges[a].push_back(b);
        if(b > k) k = b;
    }

    pair = new int[k+1];
    vis = new int[k+1];
    for(int i=1;i<=k;i++) pair[i] = vis[i] = 0;

    int match_count = 0;
    for(int i=1;i<=k;i++) {
        vis_index++;
        if(match(i)) match_count++;
    }

    std::cout<<match_count<<"\n";

    for(int i=1;i<=k;i++) {
        if(pair[i]) {
            std::cout<<pair[i]<<" "<<i<<"\n";
        }
    }
}