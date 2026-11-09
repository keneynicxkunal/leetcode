
class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {

        // Available servers
        set<int> available;

        for (int i = 0; i < k; i++) {
            available.insert(i);
        }

        // {finish_time, server_id}
        priority_queue<
            pair<long long, int>,
            vector<pair<long long, int>>,
            greater<pair<long long, int>>
        > busy;

        vector<int> count(k, 0);

        for (int i = 0; i < arrival.size(); i++) {

            // Free servers whose requests have completed
            while (!busy.empty() && busy.top().first <= arrival[i]) {
                int server = busy.top().second;
                busy.pop();

                available.insert(server);
            }

            // If all servers are busy, drop request
            if (available.empty()) {
                continue;
            }

            // Find server starting from i % k
            int target = i % k;

            auto it = available.lower_bound(target);

            // Wrap around if necessary
            if (it == available.end()) {
                it = available.begin();
            }

            int server = *it;

            // Assign request
            available.erase(it);

            count[server]++;

            // Calculate finishing time
            long long finishTime = (long long)arrival[i] + load[i];

            busy.push({finishTime, server});
        }

        // Find maximum handled requests
        int maxi = *max_element(count.begin(), count.end());

        vector<int> ans;

        for (int i = 0; i < k; i++) {
            if (count[i] == maxi) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};
