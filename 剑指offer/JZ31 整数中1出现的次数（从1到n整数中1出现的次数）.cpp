//找规律  行李箱密码锁


class Solution {
public:
    int NumberOf1Between1AndN_Solution(int n) {
        vector<int> nums;
        while(n)
        {
            nums.push_back(n%10);
            n /= 10;
        }

        int res = 0;
        for(int i=nums.size()-1; i >= 0 ;i--)
        {
            int left=0, right = 0, x = 1;

            for(int j = nums.size()-1; j >i; j--)
                left = left * 10 + nums[j];

            for(int k = i-1; k >= 0; k--)
            {
                right = right *10 + nums[k];
                x *= 10;
            }

//             if(nums[i] > 1) res += (left + 1)*x + right;
//             else res += (left - 1)*x + right;
            res += left * x;
            if(nums[i] == 1) res += right + 1;
            else if(nums[i] > 1) res += x;

        }
        return res;
    }
};