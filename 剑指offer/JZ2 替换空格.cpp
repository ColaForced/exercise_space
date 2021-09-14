//思路：新建字符串，遍历替换
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param s string字符串 
     * @return string字符串
     */
    string replaceSpace(string strs) {
        string res;
        for(char s : strs)
        {
            if (s == ' ')
            {
                res += "%20";
            }
            else
            {
                res += s;
            }
        }
        return res;
    }
};