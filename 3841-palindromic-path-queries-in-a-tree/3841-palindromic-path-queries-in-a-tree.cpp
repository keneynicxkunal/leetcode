#include <bits/stdc++.h>
using namespace std;

class Solution {
    int LOG;
    vector<vector<int>> adj, up;
    vector<int> depth, tin, tout, prefix;
    int timer;

    struct Fenwick {
        int n;
        vector<int> bit;

        Fenwick(int n) : n(n), bit(n + 1, 0) {}

        void update(int idx, int val) {
            for (; idx <= n; idx += idx & -idx) {
                bit[idx] ^= val;
            }
        }

        int query(int idx) {
            int res = 0;
            for (; idx > 0; idx -= idx & -idx) {
                res ^= bit[idx];
            }
            return res;
        }

        void rangeUpdate(int l, int r, int val) {
            update(l + 1, val);
            if (r + 2 <= n) {
                update(r + 2, val);
            }
        }

        int pointQuery(int idx) {
            return query(idx + 1);
        }
    };

    void buildTree(int n, vector<vector<int>>& edges,
                   const string& s) {
        adj.assign(n, {});

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        LOG = 1;
        while ((1 << LOG) <= n) {
            LOG++;
        }

        up.assign(LOG, vector<int>(n, 0));
        depth.assign(n, 0);
        tin.assign(n, 0);
        tout.assign(n, 0);
        prefix.assign(n, 0);
        timer = 0;

        // Iterative DFS with entry and exit states
        stack<tuple<int, int, bool>> st;
        st.push({0, 0, true});

        while (!st.empty()) {
            auto [u, p, entering] = st.top();
            st.pop();

            if (entering) {
                tin[u] = timer++;
                up[0][u] = p;

                prefix[u] = (u == 0 ? 0 : prefix[p])
                          ^ (1 << (s[u] - 'a'));

                st.push({u, p, false});

                for (int v : adj[u]) {
                    if (v == p) continue;

                    depth[v] = depth[u] + 1;
                    st.push({v, u, true});
                }
            } else {
                tout[u] = timer - 1;
            }
        }

        for (int j = 1; j < LOG; j++) {
            for (int u = 0; u < n; u++) {
                up[j][u] = up[j - 1][up[j - 1][u]];
            }
        }
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v]) {
            swap(u, v);
        }

        int diff = depth[u] - depth[v];

        for (int j = 0; j < LOG; j++) {
            if (diff & (1 << j)) {
                u = up[j][u];
            }
        }

        if (u == v) return u;

        for (int j = LOG - 1; j >= 0; j--) {
            if (up[j][u] != up[j][v]) {
                u = up[j][u];
                v = up[j][v];
            }
        }

        return up[0][u];
    }

public:
    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        buildTree(n, edges, s);

        Fenwick fw(n);
        vector<bool> answer;

        for (const string& q : queries) {
            stringstream ss(q);
            string type;
            int u, v;

            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;

                int oldBit = 1 << (s[u] - 'a');
                int newBit = 1 << (c - 'a');
                int delta = oldBit ^ newBit;

                if (delta != 0) {
                    fw.rangeUpdate(tin[u], tout[u], delta);
                    s[u] = c;
                }
            } else {
                ss >> v;

                int w = lca(u, v);

                int pu = prefix[u] ^ fw.pointQuery(tin[u]);
                int pv = prefix[v] ^ fw.pointQuery(tin[v]);

                int mask = pu ^ pv ^ (1 << (s[w] - 'a'));

                answer.push_back((mask & (mask - 1)) == 0);
            }
        }

        return answer;
    }
};