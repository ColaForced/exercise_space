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
    int TreeDepth(TreeNode* pRoot) {
        if( pRoot == nullptr) return 0;
        int cnt = max(TreeDepth(pRoot->left), TreeDepth(pRoot->right)) + 1;
        return cnt;
    }
};
