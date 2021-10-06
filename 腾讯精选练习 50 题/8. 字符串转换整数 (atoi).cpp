class Solution {
public:
    int myAtoi(string s) {
        long int res = 0;
        int flag = 0;
        int i=0;
        while(s[i] == ' ') {i++;}
        if(s[i] == '-') {flag = 1; i++;}
        else if(s[i] == '+') {flag = 0; i++;}
        while(s[i] == '0') {i++;}

        if(s[i]<'1' | s[i]>'9') {return 0;}
        while(s[i]>='0' && s[i] <= '9')
        {
            res = res*10 + s[i] - '0';
            if((!flag) && (res > 0x7FFFFFFF)) return 0x7FFFFFFF;
            if(flag && (-res < -0x7FFFFFFF-1)) return -0x7FFFFFFF-1; //这里“-res”容易错
            i++;
        }
        if (flag == 1) {res = -res;}
        return res;
    }
};