//二叉搜索树后序遍历意味着最后值为中间值   从前往后找 小的为一组，大的为一组  递归
class Solution {
public:
    bool helper(vector<int>&arr, int left, int right)
    {
        if (left > right) return true;
        int root = arr[right];
        int index = left;
        while(arr[index] < root) index++; //得到第一个比root大的元素下表

        for(int i = index; i<=right; i++)
        { if (arr[i] < root) return false;}
        return helper(arr, left, index-1) && helper(arr, index, right-1);

    }

    bool VerifySquenceOfBST(vector<int> sequence) {
        if (sequence.size() == 0) return false;
        return helper(sequence, 0, sequence.size()-1);
    }
};