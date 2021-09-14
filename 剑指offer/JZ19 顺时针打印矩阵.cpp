// ！！！！！！！！！有错误 无法通过leetcode
class Solution {
public:
    vector<int> printMatrix(vector<vector<int> > matrix) {
        vector<int> ans;
        int m = matrix.size();
        if (m == 0) return ans;
        int n = matrix[0].size();
        if (n == 0) return ans;

        //预先处理单行单列
        if (m == 1|n == 1)
        {
            for(auto x:matrix)
            {
                for(auto y:x)
                {
                    ans.push_back(y);
                }
            }
            return ans;
        }

        //cs, ce, 列坐标起终点； rs,re,行坐标起终点
        int cs = 0, ce = n-1;
        int rs = 0, re = m-1;
        while (cs <= ce && rs <= re)
        {
            for(int i=cs; i<=ce-1; i++)
            {
                ans.push_back(matrix[rs][i]);
            }

            for(int i = rs; i<=re-1; i++)
            {
                ans.push_back(matrix[i][ce]);
            }

            //避免剩余单列造成的重复选取
            if(re != rs)
            {
                for(int i = ce; i>=cs+1; i--)
                {
                    ans.push_back(matrix[re][i]);
                }
            }

            //避免剩余单行造成的重复选取
            if (ce != cs)
            {
                for(int i = re; i>=rs+1; i--)
                {
                    ans.push_back(matrix[i][cs]);
                }
            }
            cs++; ce--; rs++; re--;//起点++，终点--
        }

        //由于每次遍历不取最后一个点，造成行列皆奇数时有一个点取不到
        if (m%2==1 && n%2 == 1)
        {
            if(m < n)
            {
                ans.push_back(matrix[m/2][n/2 + 1]);
            }
            else if(m > n)
            {
                ans.push_back(matrix[m/2 + 1][n/2]);
            }
            else if(m == n)
            {
                ans.push_back(matrix[m/2][n/2]);
            }
        }
        return ans;
    }
};