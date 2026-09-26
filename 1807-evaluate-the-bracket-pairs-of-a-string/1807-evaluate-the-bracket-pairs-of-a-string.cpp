#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        
        // Step 1: Store knowledge in hashmap
        unordered_map<string, string> mp;

        for (auto &k : knowledge) {
            mp[k[0]] = k[1];
        }

        string ans;

        // Step 2: Traverse the string
        for (int i = 0; i < s.size(); i++) {

            // Normal character
            if (s[i] != '(') {
                ans += s[i];
            }
            else {
                // Step 3: Find the key inside brackets
                i++; // skip '('

                string key;

                while (s[i] != ')') {
                    key += s[i];
                    i++;
                }

                // Step 4: Check whether key exists
                if (mp.find(key) != mp.end()) {
                    ans += mp[key];
                }
                else {
                    ans += '?';
                }
            }
        }

        return ans;
    }
};