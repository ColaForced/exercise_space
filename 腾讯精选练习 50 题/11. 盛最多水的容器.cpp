//贪心 双指针
class Solution {
public:
    int maxArea(vector<int>& height) {
        int l = 0, r = height.size()-1;
        if(r == -1) return 0;
        int maxRes = -1;
        while(l<=r)
        {
            int vol;
            if (height[r] > height[l])
            {
                vol = height[l] * (r-l);
                l++;
            }
            else
            {
                vol = height[r] * (r-l);
                r--;
            }
            maxRes = maxRes>vol? maxRes:vol;
        }
        return maxRes;
    }
};