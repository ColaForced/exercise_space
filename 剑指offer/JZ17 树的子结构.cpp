/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};*/
class Solution {
public:
    /* 负责判断自当前节点开始的树是否匹配一致 */
    bool recur(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        if(pRoot2 == nullptr) return true;
        if(pRoot1 == nullptr) return false;
        if (pRoot1->val != pRoot2->val) return false;
        return recur(pRoot1->left, pRoot2->left) && recur(pRoot1->right, pRoot2->right);
    }

    /* 不断遍历第一颗树的左右节点，直至发生匹配或到遍历结束 */
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        if(pRoot1 == nullptr) return false;
        if(pRoot2 == nullptr) return false;
        if (recur(pRoot1, pRoot2) == true) return true;
        return HasSubtree(pRoot1->left, pRoot2) | HasSubtree(pRoot1->right, pRoot2);
    }
};