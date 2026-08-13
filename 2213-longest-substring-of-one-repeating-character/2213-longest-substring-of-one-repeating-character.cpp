#include <bits/stdc++.h>
using namespace std;

struct Node {
    int len;
    int pref, suff, best;
    char leftChar, rightChar;

    Node() {
        len = pref = suff = best = 0;
        leftChar = rightChar = '\0';
    }

    Node(char c) {
        len = pref = suff = best = 1;
        leftChar = rightChar = c;
    }
};

class SegmentTree {
private:
    vector<Node> tree;
    string &s;

    Node merge(Node a, Node b) {
        if (a.len == 0) return b;
        if (b.len == 0) return a;

        Node res;
        res.len = a.len + b.len;
        res.leftChar = a.leftChar;
        res.rightChar = b.rightChar;

        // Default values
        res.pref = a.pref;
        res.suff = b.suff;
        res.best = max(a.best, b.best);

        // If boundary characters are same,
        // prefix/suffix/best can be combined.
        if (a.rightChar == b.leftChar) {
            // Entire left segment can become part of prefix
            if (a.pref == a.len)
                res.pref = a.len + b.pref;

            // Entire right segment can become part of suffix
            if (b.suff == b.len)
                res.suff = b.len + a.suff;

            // Longest substring crossing the boundary
            res.best = max(res.best, a.suff + b.pref);
        }

        return res;
    }

    void build(int node, int l, int r) {
        if (l == r) {
            tree[node] = Node(s[l]);
            return;
        }

        int mid = l + (r - l) / 2;

        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int node, int l, int r, int idx, char c) {
        if (l == r) {
            tree[node] = Node(c);
            return;
        }

        int mid = l + (r - l) / 2;

        if (idx <= mid)
            update(node * 2, l, mid, idx, c);
        else
            update(node * 2 + 1, mid + 1, r, idx, c);

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

public:
    SegmentTree(string &str) : s(str) {
        int n = s.size();
        tree.resize(4 * n);
        build(1, 0, n - 1);
    }

    void update(int idx, char c) {
        update(1, 0, s.size() - 1, idx, c);
    }

    int getBest() {
        return tree[1].best;
    }
};

class Solution {
public:
    vector<int> longestRepeating(
        string s,
        string queryCharacters,
        vector<int>& queryIndices
    ) {
        SegmentTree st(s);

        vector<int> ans;

        for (int i = 0; i < queryIndices.size(); i++) {
            int idx = queryIndices[i];
            char c = queryCharacters[i];

            st.update(idx, c);

            ans.push_back(st.getBest());
        }

        return ans;
    }
};