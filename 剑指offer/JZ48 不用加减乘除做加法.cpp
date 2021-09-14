//异或计算 无进位假发，
//与运算+左移 得到加法进位
class Solution {
public:
    int Add(int num1, int num2)
    {
        while(num2 != 0)
        {
            int p = num1 ^ num2;
            int q = (num1 & num2) << 1;
            num1 = p;
            num2 = q;
        }
        return num1;
    }
};