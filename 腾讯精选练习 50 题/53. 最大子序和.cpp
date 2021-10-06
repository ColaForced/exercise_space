class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int result =  -0x7FFFFFFF - 1;
        int cnt = 0;
        for(int i=0; i<nums.size(); i++)
        {
            cnt += nums[i];
            result = result > cnt? result:cnt;
            if(cnt <= 0) cnt = 0;
        }
        return result;
    }
};

