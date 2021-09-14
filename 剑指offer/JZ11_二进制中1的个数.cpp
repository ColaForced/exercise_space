//首先判断n是不是负数，当n为负数的时候，直接用后面的while循环会导致死循环，因为负数
//向左移位的话最高位补1 ！ 因此需要一点点特殊操作，可以将最高位的符号位1变成0，也就
//是n & 0x7FFFFFFF，这样就把负数转化成正数了，唯一差别就是最高位由1变成0，因为少了
//一个1，所以ans加1。之后再按照while循环里处理正数的方法来操作就可以啦！
class Solution {
public:
    int  NumberOf1(int n) {
        int ans = 0;
        if (n < 0)
        {
            n &= 0x7FFFFFFF;
            ans ++;
        }

        while(n != 0)
        {
            if( n & 1 == 1 )
            {
                ans ++;
            }
            n >>= 1;
        }
        return ans;
    }
};