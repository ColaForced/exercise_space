//逃课 。。。

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param array int整型vector
     * @return int整型vector
     */
    vector<int> reOrderArray(vector<int>& array) {
        // write code here
        if (array.size() <= 1) return array;
        vector<int> oddArray, evenArray;
        for(auto x:array)
        {
            if (x%2 != 0)
            {
                oddArray.push_back(x);
            }
            else
            {
                evenArray.push_back(x);
            }
        }

        array.clear();
        for(auto x:oddArray)
        {
            array.push_back(x);
        }

        for(auto x:evenArray)
        {
            array.push_back(x);
        }

        return array;
    }
};