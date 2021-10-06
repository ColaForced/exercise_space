//简化为 双指针两数之和问题
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;

        for(int i=0; i<nums.size(); i++)
        {
            if (nums[i]>0) return res;
            if (i > 0 && nums[i] == nums[i-1]) continue;

            int left = i+1, right = nums.size() - 1;

            while(left < right)
            {
                if((nums[i] + nums[left] + nums[right]) > 0) right--;
                else if((nums[i] + nums[left] + nums[right]) < 0) left ++;
                else
                {
                    res.push_back(vector<int>{nums[i] , nums[left] , nums[right]});
                    while(right > left && nums[right] == nums[right-1]) right--;
                    while(right > left && nums[left] == nums[left+1]) left++;
                    right--; left++;
                }

            }
        }
        return res;
    }
};