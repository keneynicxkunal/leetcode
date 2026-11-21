
class Solution {
public:
    vector<int> answer;
    vector<vector<int>> adj;
    vector<int> newParent;

    void dfs(int node, string &s, vector<int> &last) {
        int ch = s[node] - 'a';

        // Find the closest ancestor with the same character
        int old = last[ch];

        if (node != 0 && old != -1) {
            newParent[node] = old;
        }

        // Update the latest ancestor for this character
        last[ch] = node;

        // Visit children in the original tree
        for (int child : adj[node]) {
            dfs(child, s, last);
        }

        // Backtrack
        last[ch] = old;
    }

    int calculate(int node, vector<vector<int>> &tree) {
        int size = 1;

        for (int child : tree[node]) {
            size += calculate(child, tree);
        }

        answer[node] = size;
        return size;
    }

    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        adj.resize(n);
        newParent = parent;
        answer.resize(n);

        // Build original tree
        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }

        // Find new parents using original tree
        vector<int> last(26, -1);
        dfs(0, s, last);

        // Build final tree
        vector<vector<int>> tree(n);

        for (int i = 1; i < n; i++) {
            tree[newParent[i]].push_back(i);
        }

        // Calculate subtree sizes
        calculate(0, tree);

        return answer;
    }
};
