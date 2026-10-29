class Solution {
public:
    vector<vector<int>> adj;
    vector<vector<int>> up;
    vector<int> tin, tout, depth;
    vector<int> bit;
    vector<int> fenwick;

    int timer = 0;
    int LOG;

    int charMask(char c) {
        return 1 << (c - 'a');
    }

    void add(int idx, int val, int n) {
        while (idx <= n) {
            fenwick[idx] ^= val;
            idx += idx & -idx;
        }
    }

    int prefixXor(int idx) {
        int result = 0;

        while (idx > 0) {
            result ^= fenwick[idx];
            idx -= idx & -idx;
        }

        return result;
    }

    void rangeXor(int l, int r, int val, int n) {
        add(l, val, n);

        if (r + 1 <= n) {
            add(r + 1, val, n);
        }
    }

    void dfs(int u, int parent) {
        tin[u] = ++timer;
        up[u][0] = parent;

        for (int j = 1; j < LOG; j++) {
            up[u][j] = up[up[u][j - 1]][j - 1];
        }

        for (int v : adj[u]) {
            if (v == parent) continue;

            depth[v] = depth[u] + 1;
            dfs(v, u);
        }

        tout[u] = timer;
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);

        int diff = depth[u] - depth[v];

        for (int j = 0; j < LOG; j++) {
            if (diff & (1 << j)) {
                u = up[u][j];
            }
        }

        if (u == v) return u;

        for (int j = LOG - 1; j >= 0; j--) {
            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        }

        return up[u][0];
    }

    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        adj.assign(n, {});

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        tin.assign(n, 0);
        tout.assign(n, 0);
        depth.assign(n, 0);
        up.assign(n, vector<int>(LOG, 0));
        bit.assign(n, 0);
        fenwick.assign(n + 2, 0);
        timer = 0;

        // Root the tree at node 0.
        dfs(0, 0);

        // Initialize the character contribution at every node.
        for (int u = 0; u < n; u++) {
            bit[u] = charMask(s[u]);
            rangeXor(tin[u], tout[u], bit[u], n);
        }

        vector<bool> answer;

        for (string& q : queries) {
            stringstream ss(q);
            string type;
            ss >> type;

            if (type == "update") {
                int u;
                char c;
                ss >> u >> c;

                int newMask = charMask(c);
                int delta = bit[u] ^ newMask;

                if (delta != 0) {
                    rangeXor(tin[u], tout[u], delta, n);
                    bit[u] = newMask;
                }
            } else {
                int u, v;
                ss >> u >> v;

                int pu = prefixXor(tin[u]);
                int pv = prefixXor(tin[v]);

                int w = lca(u, v);

                // Root paths include the LCA twice under XOR,
                // so add its character mask back once.
                int mask = pu ^ pv ^ bit[w];

                bool possible =
                    (mask == 0 || (mask & (mask - 1)) == 0);

                answer.push_back(possible);
            }
        }

        return answer;
    }
};