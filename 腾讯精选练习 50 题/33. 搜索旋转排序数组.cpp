class Solution {
public:
    int search(vector<int>& nums, int target) {
        int len = nums.size();
        int left = 0, right = len-1;
        while(left <= right){
            int mid = (left + right) / 2;
            if(nums[mid] == target)
                return mid;
            else if(nums[mid] < nums[right])//右半部分有序
            {
                if(nums[mid] < target && target <= nums[right])//在有序范围内
                    left = mid+1;
                else//在无序范围内
                    right = mid-1;
            }
            else//左半部分有序
            {
                if(nums[left] <= target && target < nums[mid])//在有序范围内
                    right = mid-1;
                else//在无序范围内
                    left = mid+1;
            }
        }
        return -1;
    }
};