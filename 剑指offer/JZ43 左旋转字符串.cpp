class Solution {
public:
    void ReverseString(string &str, int l, int r)
    {
        while(l<r)
        {
            char s = str[l];
            str[l] = str[r];
            str[r] = s;
            l++;r--;
        }
    }

    string LeftRotateString(string str, int n) {
        if(str.size() == 0) return str;
        while(n >= str.size()) n %= str.size();
        ReverseString(str, 0, n-1);
        ReverseString(str, n, str.size()-1);
        ReverseString(str, 0, str.size()-1);
        return str;
    }
};