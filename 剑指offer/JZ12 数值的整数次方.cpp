class Solution {
public:
    double Power(double base, int exponent) {
        if(exponent == 0)
            return 1;
        else if(exponent < 0)
            return 1 / Power(base, - exponent);
        else if(exponent % 2 == 1)
            return base * Power(base, exponent - 1);
        else
            return Power(base, exponent/2) * Power(base, exponent/2);
    }
};