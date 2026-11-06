
class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        
        int m = queries.size();
        int l = logs.size();

        // Sort logs by time
        sort(logs.begin(), logs.end(), [](const auto& a, const auto& b) {
            return a[1] < b[1];
        });

        // Store queries with their original indices
        vector<pair<int, int>> q;
        for (int i = 0; i < m; i++) {
            q.push_back({queries[i], i});
        }

        // Sort queries by time
        sort(q.begin(), q.end());

        vector<int> ans(m);
        vector<int> freq(n + 1, 0);

        int left = 0, right = 0;
        int activeServers = 0;

        for (auto& [time, idx] : q) {

            int start = time - x;

            // Add logs inside the current window
            while (right < l && logs[right][1] <= time) {
                int server = logs[right][0];

                if (freq[server] == 0) {
                    activeServers++;
                }

                freq[server]++;
                right++;
            }

            // Remove logs before the window
            while (left < right && logs[left][1] < start) {
                int server = logs[left][0];

                freq[server]--;

                if (freq[server] == 0) {
                    activeServers--;
                }

                left++;
            }

            // Servers with no requests
            ans[idx] = n - activeServers;
        }

        return ans;
    }
};
