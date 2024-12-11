#include <iostream>

int n, m;
std::vector<std::pair<int, int>>* g; // (vertex, weight)
int** d;

int main() {
    std::cin >> n >> m;
    g = new std::vector<std::pair<int, int>>[n+1];

    while (m--) {
        int u, v, w;
        std::cin >> u >> v >> w;
        g[u].push_back({v, w});
    }

    d = new int*[n+1];
    for (int i = 1; i <= n; i++) {
        d[i] = new int[n+1];
        for (int j = 1; j <= n; j++) {
            d[i][j] = (i == j ? 0 : INT_MAX);
        }
    }


    // Floyd-Warshall
    for (int v = 1; v <= n; v++) {
        for (auto& [u, w] : g[v]) {
            d[v][u] = w;
        }
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (d[i][k] != INT_MAX && d[k][j] != INT_MAX) {
                    d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }
    }

    int max_str_len = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int str_len = d[i][j] == INT_MAX ? 1 : std::to_string(d[i][j]).length();
            if (str_len > max_str_len) max_str_len = str_len;
        }
    }

    for(int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int str_len = d[i][j] == INT_MAX ? 1 : std::to_string(d[i][j]).length();
            for(int k = 0; k < max_str_len - str_len; k++) std::cout<<" ";
            if (d[i][j] == INT_MAX) std::cout<<"-";
            else std::cout<<d[i][j];
            std::cout<<" ";
        }
        std::cout<<"\n";
    }
}