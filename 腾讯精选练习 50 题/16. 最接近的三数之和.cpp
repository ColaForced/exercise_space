class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int size = nums.size();
        long int best = 0x7FFFFFFF;

        auto update = [&](int cur)
        {
            if(abs(cur - target) < abs(best - target)) best = cur;
        };

        for(int i=0; i<size; i++)
        {
            if(i>0 && nums[i] == nums[i-1]) continue;

            int j = i+1, k = size-1;
            while(j<k)
            {
                int sum = nums[i] + nums[j] + nums[k];
                if(sum == target) return target;

                update(sum);

                if(sum > target)
                {
                    int k0 = k-1;
                    while(j<k0 && nums[k0] == nums[k]) { --k0;}
                    k = k0;
                }
                else
                {
                    int j0 = j+1;
                    while(j0<k && nums[j0] == nums[j]) {++j0;}
                    j = j0;
                }
            }
        }
        return best;


    }
};