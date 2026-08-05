class TrieNode {
public:
    TrieNode* child[26];
    string word;

    TrieNode() {
        word = "";
        for (int i = 0; i < 26; i++)
            child[i] = nullptr;
    }
};

class Solution {
public:
    TrieNode* root = new TrieNode();
    vector<string> ans;

    void insert(string& word) {
        TrieNode* node = root;

        for (char c : word) {
            int idx = c - 'a';
            if (!node->child[idx])
                node->child[idx] = new TrieNode();
            node = node->child[idx];
        }

        node->word = word;
    }

    void dfs(vector<vector<char>>& board, int i, int j, TrieNode* node) {
        char ch = board[i][j];

        if (ch == '#' || !node->child[ch - 'a'])
            return;

        node = node->child[ch - 'a'];

        if (!node->word.empty()) {
            ans.push_back(node->word);
            node->word = "";          // avoid duplicates
        }

        board[i][j] = '#';

        if (i > 0)
            dfs(board, i - 1, j, node);
        if (i + 1 < board.size())
            dfs(board, i + 1, j, node);
        if (j > 0)
            dfs(board, i, j - 1, node);
        if (j + 1 < board[0].size())
            dfs(board, i, j + 1, node);

        board[i][j] = ch;
    }

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        for (string& word : words)
            insert(word);

        int m = board.size();
        int n = board[0].size();

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                dfs(board, i, j, root);
            }
        }

        return ans;
    }
};