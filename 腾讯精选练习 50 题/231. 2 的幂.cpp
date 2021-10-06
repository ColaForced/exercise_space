class Solution {
public:
    bool isPowerOfTwo(int n) {
        // long int m = n;
        // if(m<=0) return false;
        // while(m != 1)
        // {
        //     if(m%2 == 1) return false;
        //     m/=2;
        // }
        // return true;

        return n>0 && ((n&(n-1)) == 0);
    }
};

