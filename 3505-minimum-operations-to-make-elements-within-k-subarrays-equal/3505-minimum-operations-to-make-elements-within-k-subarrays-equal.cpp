class Solution {
public:
    using ll = long long;

    class Fenwick {
    public:
        int n;
        vector<ll> bit;

        Fenwick(int n) {
            this->n = n;
            bit.assign(n + 1, 0);
        }

        void update(int i, ll val) {
            for (; i <= n; i += i & -i)
                bit[i] += val;
        }

        ll query(int i) {
            ll sum = 0;
            for (; i > 0; i -= i & -i)
                sum += bit[i];
            return sum;
        }

        int kth(ll k) {
            int idx = 0;
            int mask = 1;

            while ((mask << 1) <= n)
                mask <<= 1;

            for (; mask; mask >>= 1) {
                int next = idx + mask;

                if (next <= n && bit[next] < k) {
                    idx = next;
                    k -= bit[next];
                }
            }

            return idx + 1;
        }
    };

    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        vector<int> vals = nums;
        sort(vals.begin(), vals.end());

        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        int m = vals.size();

        Fenwick cnt(m), sum(m);

        auto getId = [&](int v) {
            return lower_bound(vals.begin(), vals.end(), v)
                   - vals.begin() + 1;
        };

        ll totalSum = 0;

        auto add = [&](int v, int delta) {
            int id = getId(v);

            cnt.update(id, delta);
            sum.update(id, 1LL * v * delta);

            totalSum += 1LL * v * delta;
        };

        auto getCost = [&]() -> ll {
            int mid = cnt.kth((x + 1) / 2);

            ll median = vals[mid - 1];

            int id = mid;

            ll leftCount = cnt.query(id);
            ll leftSum = sum.query(id);

            ll rightCount = x - leftCount;
            ll rightSum = totalSum - leftSum;

            return median * leftCount - leftSum
                 + rightSum - median * rightCount;
        };

        vector<ll> cost(n - x + 1);

        // Calculate minimum cost for every window of size x.
        for (int i = 0; i < n; i++) {
            add(nums[i], 1);

            if (i >= x)
                add(nums[i - x], -1);

            if (i >= x - 1)
                cost[i - x + 1] = getCost();
        }

        // DP with rolling arrays.
        const ll INF = 1e18;

        vector<ll> prev(n + 1, 0), curr(n + 1, INF);

        for (int j = 1; j <= k; j++) {
            fill(curr.begin(), curr.end(), INF);

            for (int i = 1; i <= n; i++) {
                // Do not select a subarray ending at i-1.
                curr[i] = curr[i - 1];

                // Select a subarray [i-x, i-1].
                if (i >= x && prev[i - x] != INF) {
                    curr[i] = min(
                        curr[i],
                        prev[i - x] + cost[i - x]
                    );
                }
            }

            prev.swap(curr);
        }

        return prev[n];
    }
};