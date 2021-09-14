class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param array int整型vector
     * @return int整型vector
     */
    vector<int> FindNumsAppearOnce(vector<int>& array) {
        // write code here
        int ab = 0;
        for(auto x:array) ab ^= x;
        int p = 1;
        while(ab)
        {
            //& has lower precedence than !=; != will be evaluated first
            //容易犯错：未括号包裹 & 运算
            if((ab & p) != 0) //容易犯错， & 写成 &&
                break;
            else
                p <<= 1;//容易犯错， << 忘记 =
        }

        vector<int> tempArr_1, tempArr_2;
        for(auto x:array)
        {
            if((x & p) != 0) tempArr_1.push_back(x);
            else tempArr_2.push_back(x);
        }

        vector<int> ans;
        int a = 0, b = 0;
        for(auto x:tempArr_1) a ^= x;
        for(auto x:tempArr_2) b ^= x;
        ans.push_back(a);
        ans.push_back(b);
        sort(ans.begin(),ans.end());
        return ans;
    }
};