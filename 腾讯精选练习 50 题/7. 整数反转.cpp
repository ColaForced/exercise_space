const int INTMIN = -0x7FFFFFFF - 1;
const int INTMAX = 0x7FFFFFFF;
class Solution {
public:
    int reverse(long int x) {
        long res = 0;
        while(x!=0)
        {
            res = res*10 + x%10;
            if(res < INTMIN || res > INTMAX) return 0;
            x /= 10;
        }
        return res;
    }
};