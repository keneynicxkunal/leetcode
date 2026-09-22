class Solution {
public:
    static const int MAXK = 5;

    struct Node {
        int prod;
        int cnt[MAXK];

        Node() {
            prod = 1;
            for (int i = 0; i < MAXK; i++)
                cnt[i] = 0;
        }
    };

    int n, k;
    vector<Node> tree;

    Node mergeNode(const Node& a, const Node& b) {
        Node res;

        res.prod = (a.prod * b.prod) % k;

        // Prefixes completely inside left part
        for (int i = 0; i < k; i++) {
            res.cnt[i] = a.cnt[i];
        }

        // Prefixes containing all of left part
        // and some prefix of right part
        for (int i = 0; i < k; i++) {
            int rem = (a.prod * i) % k;
            res.cnt[rem] += b.cnt[i];
        }

        return res;
    }

    void build(int p, int l, int r, vector<int>& nums) {
        if (l == r) {
            int rem = nums[l] % k;

            tree[p].prod = rem;
            tree[p].cnt[rem] = 1;

            return;
        }

        int mid = (l + r) >> 1;

        build(p << 1, l, mid, nums);
        build(p << 1 | 1, mid + 1, r, nums);

        tree[p] = mergeNode(tree[p << 1], tree[p << 1 | 1]);
    }

    void update(int p, int l, int r, int idx, int value) {
        if (l == r) {
            int rem = value % k;

            tree[p].prod = rem;

            for (int i = 0; i < k; i++)
                tree[p].cnt[i] = 0;

            tree[p].cnt[rem] = 1;

            return;
        }

        int mid = (l + r) >> 1;

        if (idx <= mid)
            update(p << 1, l, mid, idx, value);
        else
            update(p << 1 | 1, mid + 1, r, idx, value);

        tree[p] = mergeNode(tree[p << 1], tree[p << 1 | 1]);
    }

    Node query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return tree[p];

        int mid = (l + r) >> 1;

        if (qr <= mid)
            return query(p << 1, l, mid, ql, qr);

        if (ql > mid)
            return query(p << 1 | 1, mid + 1, r, ql, qr);

        Node left = query(p << 1, l, mid, ql, qr);
        Node right = query(p << 1 | 1, mid + 1, r, ql, qr);

        return mergeNode(left, right);
    }

    vector<int> resultArray(
        vector<int>& nums,
        int K,
        vector<vector<int>>& queries
    ) {
        n = nums.size();
        k = K;

        tree.resize(4 * n + 5);

        build(1, 0, n - 1, nums);

        vector<int> ans;
        ans.reserve(queries.size());

        for (auto &q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            // Update persists
            nums[index] = value;
            update(1, 0, n - 1, index, value);

            // We need all possible non-empty prefixes
            // of nums[start ... n-1]
            Node res = query(1, 0, n - 1, start, n - 1);

            ans.push_back(res.cnt[x]);
        }

        return ans;
    }
};