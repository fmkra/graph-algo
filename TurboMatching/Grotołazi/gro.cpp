// https://szkopul.edu.pl/problemset/problem/eZiOMPFA4Cq9YsIFAjhCZlo9/site/?key=statement

#include <iostream>
#include <vector>

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

int N;
std::vector<int>* g;
std::vector<int> ends;
bool* is_end;
int* vis2;
int vis_index2 = 0;

int curr_start;
void dfs(int v) {
    if(vis2[v] == vis_index2) return;
    vis2[v] = vis_index2;
    if(is_end[v]) {
        edges[curr_start].push_back(v);
        if(v > k) k = v;
    }
    for(int u : g[v]) {
        dfs(u);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::cin>>N;
    g = new std::vector<int>[N+1];
    is_end = new bool[N+1];
    for(int i=1;i<=N;i++) is_end[i] = false;
    for(int i=1;i<N;i++) {
        int M;
        std::cin>>M;
        while(M--) {
            int x;
            std::cin>>x;
            g[i].push_back(x);
            if(x==N) {
                ends.push_back(i);
                is_end[i] = true;
            }
        }
    }

    n = N;
    edges = new std::vector<int>[n+1];
    vis2 = new int[n+1];
    for(int i=1;i<=n;i++) vis2[i] = 0;

    for(int v : g[1]) {
        curr_start = v;
        vis_index2++;
        dfs(v);
    }

    pair = new int[k+1];
    vis = new int[k+1];
    for(int i=1;i<=k;i++) pair[i] = vis[i] = 0;

    int match_count = 0;
    for(int i=1;i<=k;i++) {
        vis_index++;
        if(match(i)) match_count++;
    }

    if(is_end[1]) match_count++;

    std::cout<<match_count<<"\n";
}