class Solution {
public:
    void dfs(int node, vector<vector<int>>& graph, vector<bool>& suspicious) {
        if (suspicious[node]) return;

        suspicious[node] = true;
        for (int next : graph[node]) {
            dfs(next, graph, suspicious);
        }
    }

    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> graph(n);

        // Build graph
        for (auto &edge : invocations) {
            graph[edge[0]].push_back(edge[1]);
        }

        // Mark suspicious methods
        vector<bool> suspicious(n, false);
        dfs(k, graph, suspicious);

        // Check if any non-suspicious method invokes a suspicious one
        for (auto &edge : invocations) {
            int from = edge[0];
            int to = edge[1];

            if (!suspicious[from] && suspicious[to]) {
                vector<int> ans;
                for (int i = 0; i < n; i++)
                    ans.push_back(i);
                return ans;
            }
        }

        // Return remaining methods
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (!suspicious[i])
                ans.push_back(i);
        }

        return ans;
    }
};