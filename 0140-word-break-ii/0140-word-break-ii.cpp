class Solution {
public:
    unordered_set<string> dict;
    unordered_map<int, vector<string>> memo;

    vector<string> dfs(string &s, int start) {

        if (memo.count(start))
            return memo[start];

        vector<string> ans;

        if (start == s.size()) {
            ans.push_back("");
            return ans;
        }

        for (string word : dict) {

            int len = word.length();

            if (start + len <= s.size() &&
                s.substr(start, len) == word) {

                vector<string> temp = dfs(s, start + len);

                for (string str : temp) {

                    if (str == "")
                        ans.push_back(word);
                    else
                        ans.push_back(word + " " + str);
                }
            }
        }

        return memo[start] = ans;
    }

    vector<string> wordBreak(string s, vector<string>& wordDict) {

        dict.insert(wordDict.begin(), wordDict.end());

        return dfs(s, 0);
    }
};