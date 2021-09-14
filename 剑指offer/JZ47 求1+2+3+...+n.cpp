//巧用 逻辑运算符短路
class Solution {
public:
    int Sum_Solution(int n) {
        int ans = n;
        ans && (ans += Sum_Solution(n-1));
        return ans;
    }
};