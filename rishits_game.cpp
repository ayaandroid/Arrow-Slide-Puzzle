#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int main() {
    int n, m, k; cin >> n >> m >> k; // size of grid = n x m, number of arrows = k
    vector<vector<int>> grid(n, vector<int> (m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j]; // 0 <= grid[i][j] <= k - 1
        }
    }
    vector<pair<vector<int>, char>> arrow_heads(k);
    for (int l = 0; l < k; l++) { 
        int i, j; cin >> i >> j; // location of head of lth arrow. grid[i][j] == l
        char dir; cin >> dir; // dir = 'U', 'D', 'L', or 'R'
        arrow_heads[l] = {{i, j}, dir};
    }
    vector<vector<int>> adj(k);
    vector<int> indeg(k);
    for (int l = 0; l < k; l++) {
        int i = arrow_heads[l].first[0], j = arrow_heads[l].first[1];
        char dir = arrow_heads[l].second;
        unordered_set<int> blocking_arrows;
        switch (dir) {
            case 'U':
                for (int h = 1; i - h >= 0; h++) {
                    if (grid[i - h][j] != l) { // some other arrow
                        blocking_arrows.insert(grid[i - h][j]);
                    }
                }
                break;
            case 'D':
                for (int h = 1; i + h < n; h++) {
                        if (grid[i + h][j] != l) {
                            blocking_arrows.insert(grid[i + h][j]);
                        }
                    }
                break;
            case 'L':
                for (int h = 1; j - h >= 0; h++) {
                        if (grid[i][j - h] != l) {
                            blocking_arrows.insert(grid[i][j - h]);
                        }
                    }
                break;
            case 'R':
                for (int h = 1; j + h < m; h++) {
                        if (grid[i][j + h] != l) {
                            blocking_arrows.insert(grid[i][j + h]);
                        }
                    }
                break;
        }
        for (auto b: blocking_arrows) {
            adj[b].push_back(l);
            indeg[l]++;
        }
    }
    // topological sort
    queue<int> q;
    for (int l = 0; l < k; l++) {
        if (indeg[l] == 0) {
            q.push(l);
        }
    }
    vector<int> release_order;
    while (!q.empty()) {
        int l = q.front();
        release_order.push_back(l);
        q.pop();
        for (auto a: adj[l]) {
            indeg[a]--;
            if (indeg[a] == 0) {
                q.push(a);
            }
        }
    }
    for (auto l: release_order) {
        cout << l << " ";
    }
    return 0;
}