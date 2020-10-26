/*
 * Author: Sandro Jologua
 */

#include <bits/stdc++.h>
using namespace std;
using edge = array<int, 4>;


struct dsu {
        vector<int> par, rk;
        dsu(int n) {
                par.resize(n + 1), rk.resize(n + 1);
                for (int i = 1; i <= n; i++) {
                        par[i] = i, rk[i] = 1;
                }
        }

        int find(int x) {
                while (x != par[x]) x = par[x];
                return x;
        }

        void unite(int a, int b) {
                a = find(a), b = find(b);
                if (a != b) {
                        if (rk[a] < rk[b]) swap(a, b);
                        par[b] = a, rk[a] += rk[b];
                }
        }
};

int n;
vector<edge> edges, good;

const int di[]{1,0},dj[]{0,1};
const int di1[]{1,0,-1,0},dj1[]{0,1,0,-1};


bool have(edge e) {
        return binary_search(good.begin(), good.end(), e);
}


int id(int x, int y) {
        return x * n + y;
}


char dir(int x, int y, int a, int b) {
        if (a == x && b - 1 == y) return '<';
        if (a == x && b + 1 == y) return '>';
        if (a - 1 == x && b == y) return '^';
        return 'v';
}




int main() {
        srand(time(NULL));
        cin >> n;
        for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                        for (int d = 0; d < 2; d++) {
                                int a = di[d] + i, b = dj[d] + j;
                                if (a >= 0 && a < n && b >= 0 && b < n) {
                                        edges.push_back(edge({i, j, a, b}));
                                }
                        }
                }
        }

        random_shuffle(edges.begin(), edges.end());
        dsu d(n * n);
        for (edge e: edges) {
                int x = id(e[0], e[1]);
                int y = id(e[2], e[3]);
                if (d.find(x) == d.find(y)) continue;
                d.unite(x, y);
                good.push_back(e);
        }


        int x = rand() % n, y = rand() % n;
        sort(good.begin(), good.end());
        cout << ' ';
        for (int i = 0; i < n; i++) cout << "_ ";
        cout << '\n';
        for (int i = 0; i < n; i++) {
                if (i != x) cout << '|';
                else cout << ' ';
                for (int j = 0; j < n; j++) {
                        if (!have(edge({i, j, i + 1, j})))cout << '_';
                        else cout << ' ';
                        if (j == n - 1) continue;
                        if (!have(edge({i, j, i, j + 1})) && j < n - 1)cout << '|';
                        else cout << ' ';
                }
                if (i != y) cout << '|';
                else cout << ' ';
                cout << '\n';
        }

        map<vector<int>, vector<int>> prev;
        set<vector<int>> vis;
        function<void(int, int)> dfs = [&](int x, int y) {
                vis.insert({x, y});
                for (int d = 0; d < 4; d++) {
                        int p = x + di1[d];
                        int q = y + dj1[d];
                        if ((p >= 0 && p < n && q >= 0 && q < n) && !vis.count({p, q}) && (
                                have(edge({x, y, p, q})) || have(edge({p, q, x, y})))) {
                                prev[{p, q}] = {x, y};
                                dfs(p, q);
                        }
                }
        };


        dfs(x, 0);
        vector<vector<char>> path(n, vector<char>(n, '.'));
        int i = y, j = n - 1;
        path[i][j] = '>';
        while (prev.count({i, j})) {
                auto k = prev[{i, j}];
                int p = i, q = j;
                i = k[0], j = k[1];
                path[i][j] = dir(p, q, i, j);
        }

        cout << '\n';
        for (i = 0; i < n; i++) {
                for (j = 0; j < n; j++) {
                        cout << path[i][j] << ' ';
                }
                cout << '\n';
        }

        return 0;
}
