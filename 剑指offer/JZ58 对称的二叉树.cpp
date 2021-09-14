/*
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};
*/
class Solution {
public:
    bool help(TreeNode *p, TreeNode *q)
    {
        if(!p && !q) return true;
        if (p && q) return (p->val == q->val) && help(p->left, q->right) && help(p->right, q->left);
        return false;
    }

    bool isSymmetrical(TreeNode* pRoot) {
        if(! pRoot) return true;
        if(!pRoot->left && !pRoot->right) return true;
        if(pRoot->left && pRoot->right) return help(pRoot->left, pRoot->right);
        return false;
    }

};