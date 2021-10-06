class Solution {
public:
    bool canWinNim(int n) {
        n %= 4;
        if(n == 0) return 0;
        else return 1;

    }
};


//class Solution {
//public:
//    bool canWinNim(int n) {
//        if(n<=3) return true;
//        vector<int> dp(n,1);
//        for(int i = 3; i<n; i++)
//        {
//            dp[i] = !dp[i-1] || !dp[i-2] || !dp[i-3];
//        }
//        return dp[n-1];
//    }
//};
