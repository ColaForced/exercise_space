const long int MAX_LONG_INT = 0x7FFFFFFF;
const long int MIN_LONG_INT = -MAX_LONG_INT - 1;

class Solution {
public:
    int FindGreatestSumOfSubArray(vector<int> array) {
        int sum = 0, ans = MIN_LONG_INT;
        for(int i=0; i<array.size(); i++)
        {
            if(sum > 0) sum += array[i];
            else sum = array[i];
            ans = max(ans, sum);
        }
        return ans;
    }
};