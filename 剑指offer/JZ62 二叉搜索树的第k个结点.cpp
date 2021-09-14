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
    TreeNode *res;
    int cnt;
    void midTraverse(TreeNode *node)
    {
        if(node == nullptr) return;
        midTraverse(node->left);
        cnt --;
        if(cnt == 0) {res = node; return;}
        midTraverse(node->right);
    }

    TreeNode* KthNode(TreeNode* pRoot, int k) {
        res = nullptr; cnt = k;
        midTraverse(pRoot);
        return res;
    }


};