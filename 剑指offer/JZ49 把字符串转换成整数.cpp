class Solution {
public:
    int help(string str, int start)
    {
        int res = 0;
        for(int i=start; i<str.size(); i++)
        {
            if(('0' <= str[i]) && (str[i] <= '9'))
            {
                res = res*10 + str[i] - '0';
            }
            else
                return 0;
        }
        return res;
    }

    int StrToInt(string str) {
        if(str.size() == 0) return 0;
        if(str[0] == '-') return -help(str, 1);
        if(str[0] == '+') return help(str, 1);
        return help(str, 0);

    }
};