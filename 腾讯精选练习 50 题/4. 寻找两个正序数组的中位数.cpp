//
// Created by peng on 2021/9/15.
//
#include <vector>
#include <iostream>
using namespace  std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int cnt = 0;
        int m = nums1.size(), n = nums2.size();

        int l = 0, r= 0;
        int flag = -1;
        if(m%2 + n%2 == 1)
        {
            for(int i=0; i<=(m+n)/2; ++i)
            {
                if(l >= m) { r++; flag = 1; continue;}
                if(r >= n) { l++; flag = 0;continue;}
                else if(nums1[l] >= nums2[r]) {l++; flag = 0;}
                else {r++; flag = 1;}
            }
            if (flag == 0) return nums1[l-1];
            else if (flag == 1) return nums2[r-1];
        }
        else if(m%2 + n%2 != 1)
        {
            int lval,rval;
            for(int i=0; i<=(m+n)/2-1; ++i)
            {
                if(l >= m) { r++; flag = 1; continue;}
                if(r >= n) { l++; flag = 0;continue;}
                else if(nums1[l] >= nums2[r]) {l++; flag = 0;}
                else {r++; flag = 1;}
            }
            if (flag == 0) lval =  nums1[l-1];
            else if (flag == 1) lval = nums2[r-1];

            if(l<m && r<n) rval = min(nums1[l], nums2[r]);
            else if (l >= m) rval = nums2[r];
            else if (r >= n) rval = nums1[l];
            return (lval + rval) / 2;
        }
        return 0;
    }
};


int main()
{
    Solution sol;
    vector<int> nums1 = {1,3};
    vector<int> nums2 = {2};
    int ans = sol.findMedianSortedArrays(nums1,nums2);
    cout<<ans<<endl;
    return 0;
}