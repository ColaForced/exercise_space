class Solution {
public:
    int jumpFloorII(int n) {
        vector<int> dp(n, 0);
        dp[0] = 1;
        dp[1] = 2;
        for(int i=2; i <= n-1; i++)
        {
            for(int j=0; j<i; j++)
            {
                dp[i] += dp[j];
            }
            dp[i] += 1;
        }
        return dp[n-1];

    }
};