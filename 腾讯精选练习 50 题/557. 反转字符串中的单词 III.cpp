#include <iostream>
using namespace std;

class Solution {
public:
    void revRange(string &s, int l, int r)
    {
        while(l<=r)
        {
            char t = s[l];
            s[l] = s[r];
            s[r] = t;
            l++;
            r--;
        }
    }

    string reverseWords(string s) {
        if (s.size() <= 1) return s;
        int l = 0, r = 1;
        while(r < s.size())
        {
            while(r < s.size() && s[r] != ' ')
            {
                r++;
            }
            revRange(s, l, r-1);
            r++;
            l = r;
        }

        return s;
    }
};

int main()
{
    Solution sol;
    string s = sol.reverseWords("Let's take LeetCode contest");
//    string s = "hello";
//    sol.revRange(s, 0, 3);

    cout << s <<endl;

}