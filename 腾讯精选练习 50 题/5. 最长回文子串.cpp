class Solution {
public:
    vector<int> maxsize(int l, int r, string &s)
    {
        //计算从某个核心开始的最大回文长度
        if (l<0 || r>=s.size() || s[l] != s[r])
        {
            vector<int> res;
            res.push_back((--r) - (++l) + 1);
            res.push_back(l);
            res.push_back(r);
            return res;
        }
        return maxsize(--l, ++r, s);
    }

    string longestPalindrome(string s) {
        int n = s.size();

        int max_val = -0x7FFF -1;
        int max_l=0, max_r=0;
        //单个字符必然是回文字符串
        for(int i=0; i<n; i++)
        {
            vector<int> temp;
            temp = maxsize(i-1,i,s);
            if(temp[0] > max_val)
            {
                max_val = temp[0];
                max_l = temp[1];
                max_r = temp[2];
            }

            temp = maxsize(i,i+1,s);
            if(temp[0] > max_val)
            {
                max_val = temp[0];
                max_l = temp[1];
                max_r = temp[2];
            }

            temp = maxsize(i-1,i+1,s);
            if(temp[0] > max_val)
            {
                max_val = temp[0];
                max_l = temp[1];
                max_r = temp[2];
            }

        }
        string res = s.substr(max_l, max_val);
        return res;


    }
};