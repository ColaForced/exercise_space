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
    TreeNode *pre;

    //先想中序遍历，意味着节点遍历顺序有序，在记录上一个节点，pre->right = cur, cur->left = pre, pre = cur
    void dfs(TreeNode *cur)
    {
        if(cur == nullptr) return;
        dfs(cur->left);
        if(pre != nullptr) pre->right = cur;
        cur->left = pre;
        pre = cur;
        dfs(cur->right);
    }

    TreeNode* Convert(TreeNode* pRootOfTree) {
        if(pRootOfTree == nullptr) return nullptr;
        dfs(pRootOfTree);
        while(pre->left) pre = pre->left;
        return pre;

    }
};