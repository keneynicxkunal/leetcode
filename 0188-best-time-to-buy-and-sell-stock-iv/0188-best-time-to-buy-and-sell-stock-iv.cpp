class Solution {
public:

    int dp[1001][101][2];

    int solve(int i, int k, int buy, vector<int>& prices)
    {
        if(i == prices.size() || k == 0)
        {
            return 0;
        }

        if(dp[i][k][buy] != -1)
        {
            return dp[i][k][buy];
        }

        int ans = 0;

        if(buy == 1)
        {
            int take = -prices[i] + solve(i + 1, k, 0, prices);
            int skip = solve(i + 1, k, 1, prices);

            ans = max(take, skip);
        }
        else
        {
            int sell = prices[i] + solve(i + 1, k - 1, 1, prices);
            int skip = solve(i + 1, k, 0, prices);

            ans = max(sell, skip);
        }

        return dp[i][k][buy] = ans;
    }

    int maxProfit(int k, vector<int>& prices)
    {
        memset(dp, -1, sizeof(dp));

        return solve(0, k, 1, prices);
    }
};