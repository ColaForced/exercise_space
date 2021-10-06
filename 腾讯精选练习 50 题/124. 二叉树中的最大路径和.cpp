class Solution {
private:
    int ans = -0x7FFFFFFF - 1;

public:
    int maxPathSum(TreeNode* root)
    {
        maxGain(root);
        return ans;
    }

    int maxGain(TreeNode *node)
    {
        if(node == nullptr) return 0;

        int leftGain = max(maxGain(node->left), 0);
        int rightGain = max(maxGain(node->right), 0);

        int t = node->val + leftGain + rightGain;
        ans = max(ans, t);
        return node->val + max(leftGain, rightGain);
    }
};