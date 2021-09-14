class Solution {
public:
    int Fibonacci(int n) {
        if (n == 0) return 0;
        if (n == 1) return 1;
        int p=0, q=1, tmp = 1;
        for(int i=2; i<=n; i++)
        {
            int tmp = q;
            q = p+q;
            p = tmp;
        }
        return q;
    }
};