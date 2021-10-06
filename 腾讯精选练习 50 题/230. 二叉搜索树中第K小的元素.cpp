class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> fstack;
        while (true)
        {
            while(root != nullptr)
            {
                fstack.push(root);
                root = root->left;
            }
            root = fstack.top();
            fstack.pop();
            k --;
            if( k == 0) return root->val;
            root = root->right;
        }
    }
};