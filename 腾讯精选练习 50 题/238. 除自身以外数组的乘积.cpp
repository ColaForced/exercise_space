#include <iostream>
#include <vector>
using namespace std;



class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> left(1,1);
        vector<int> right(1,1);
        vector<int> ans;
        int p=1,q=1;
        for(int i= 1; i<nums.size();i++)
        {
            p *= nums[i-1];
            left.push_back(p);
        }

        for(int i = nums.size()-2; i>=0; i--)
        {
            q *= nums[i+1];
            right.push_back(q);
        }

        for(int i=0; i<nums.size(); i++)
        {
            ans.push_back(left[i]*right[nums.size()-i-1]);
        }
        return ans;
    }
};



int main()
{
    Solution sol;
    vector<int> nums = {1,2,3,4};
    vector<int> ans = sol.productExceptSelf(nums);
    for(auto x:ans) cout<<x<<" "<<endl;

}