class Solution {
public:

    static bool cmp(string a, string b)
    {
        string x = a + b;
        string y = b + a;

        if(x > y)
            return true;
        else
            return false;
    }

    string largestNumber(vector<int>& nums) {

        vector<string> temp;

        for(int i = 0; i < nums.size(); i++)
        {
            string s = to_string(nums[i]);
            temp.push_back(s);
        }

        sort(temp.begin(), temp.end(), cmp);

        if(temp[0] == "0")
        {
            return "0";
        }

        string ans = "";

        for(int i = 0; i < temp.size(); i++)
        {
            ans = ans + temp[i];
        }

        return ans;
    }
};