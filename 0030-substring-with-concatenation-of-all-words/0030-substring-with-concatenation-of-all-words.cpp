class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> ans;

        int wordLen = words[0].size();
        int wordCount = words.size();
        int totalLen = wordLen * wordCount;

        if (totalLen > s.size())
            return ans;

        unordered_map<string, int> target;

        // Required frequency of every word
        for (string word : words) {
            target[word]++;
        }

        // Try every possible starting offset
        for (int offset = 0; offset < wordLen; offset++) {

            int left = offset;
            int count = 0;

            unordered_map<string, int> window;

            for (int right = offset;
                 right + wordLen <= s.size();
                 right += wordLen) {

                string word = s.substr(right, wordLen);

                // Word is not present in words
                if (target.find(word) == target.end()) {
                    window.clear();
                    count = 0;
                    left = right + wordLen;
                    continue;
                }

                window[word]++;
                count++;

                // Too many occurrences of this word
                while (window[word] > target[word]) {
                    string leftWord = s.substr(left, wordLen);
                    window[leftWord]--;
                    left += wordLen;
                    count--;
                }

                // All words are present exactly the required number of times
                if (count == wordCount) {
                    ans.push_back(left);

                    // Move window forward for next possible answer
                    string leftWord = s.substr(left, wordLen);
                    window[leftWord]--;
                    left += wordLen;
                    count--;
                }
            }
        }

        return ans;
    }
};