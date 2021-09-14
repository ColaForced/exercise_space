class Solution {
public:
    int jumpFloor(int n) {
        if (n==1) return 1;
        if (n==2) return 2;
        int p = 1, q = 2, tmp = 2;
        for(int i=3; i<=n; i++)
        {
            tmp = q;
            q = p+q;
            p = tmp;
        }
        return q;
    }
};
};