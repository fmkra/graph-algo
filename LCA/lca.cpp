#include <iostream>

int n;
int* parent;
std::vector<int>* children;
int log_size = 0;
int** jump_ptr;
int* depth;

void precompute_depth(int v, int d = 0) {
    depth[v] = d;
    for (int u : children[v]) {
        precompute_depth(u, d+1);
    }
}

void precompute_lca() {
    jump_ptr = new int*[log_size];
    for (int i = 0; i < log_size; i++) {
        jump_ptr[i] = new int[n+1];
    }

    for (int i = 1; i <= n; i++) {
        jump_ptr[0][i] = parent[i];
    }

    for (int i = 1; i < log_size; i++) {
        for (int j = 1; j <= n; j++) {
            jump_ptr[i][j] = jump_ptr[i-1][jump_ptr[i-1][j]];
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) std::swap(u, v);

    for (int i = log_size-1; i >= 0; i--) {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = jump_ptr[i][u];
        }
    }

    if (u == v) return u;

    for (int i = log_size-1; i >= 0; i--) {
        if (jump_ptr[i][u] != jump_ptr[i][v]) {
            u = jump_ptr[i][u];
            v = jump_ptr[i][v];
        }
    }

    return jump_ptr[0][u];
}

int main() {
    std::cin >> n;
    parent = new int[n+1];
    children = new std::vector<int>[n+1];

    parent[1] = 1;
    for (int i = 2; i <= n; i++) {
        std::cin >> parent[i];
        children[parent[i]].push_back(i);
    }

    for(int i = 1; i < n; i *= 2) log_size++;

    depth = new int[n+1];
    precompute_depth(1);
    precompute_lca();

    while(true) {
        int u, v;
        std::cin >> u >> v;
        if(!u && !v) break;
        std::cout<< "LCA of " << u << " and " << v << " is: ";
        std::cout << lca(u, v) << std::endl;
    }
}