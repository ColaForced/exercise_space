//回溯

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
    vector<int> path;
    vector<vector<int> > ans;

    void backingTrace(TreeNode *node, int target)
    {
        if (node == nullptr) return;

        if(node->val == target)
        {
            path.push_back(node->val);
            if(node->left == nullptr && node->right == nullptr)
            {ans.push_back(path);}
            path.pop_back();
            return;
        }

        if(node->val > target) return;
        path.push_back(node->val);
        backingTrace(node->left, target - node->val);
        backingTrace(node->right, target - node->val);
        path.pop_back();
    }

    vector<vector<int> > FindPath(TreeNode* root,int target) {
        ans.clear();
        path.clear();
        backingTrace(root, target);
        return ans;
    }
};