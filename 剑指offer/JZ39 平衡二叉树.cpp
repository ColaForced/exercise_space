// 递归
class Solution {
public:
//     int MaxTreeDepth(TreeNode* pRoot) {
//         if( pRoot == nullptr) return 0;
//         int cnt = max(MaxTreeDepth(pRoot->left), MaxTreeDepth(pRoot->right)) + 1;
//         return cnt;
//     }

    int GetDepth(TreeNode * root)
    {
        if(root == nullptr) return 0;
        int left = GetDepth(root->left);
        if(left == -1) return -1;
        int right = GetDepth(root->right);
        if(right == -1) return -1;
        return abs(left-right) > 1 ? -1 : 1+max(left,right);
    }

    bool IsBalanced_Solution(TreeNode* pRoot) {
        return GetDepth(pRoot) != -1;
    }
};