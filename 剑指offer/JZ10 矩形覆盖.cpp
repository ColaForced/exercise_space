class Solution {
public:
    int rectCover(int n) {
        if(n <= 2) return n;
        int p = 1, q = 2, tmp = q;
        for(int i = 3; i <= n; ++i)
        {
            tmp = q;
            q = p + q;
            p = tmp;
        }
        return q;
    }
};