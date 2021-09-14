//队列实现

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
    vector<int> ans;
    vector<int> PrintFromTopToBottom(TreeNode* root) {
        if (root == nullptr) return ans;
        deque<TreeNode*> queue;
        queue.push_back(root);

        while(!queue.empty())
        {
            int n = queue.size();
            for(int i=0; i<n; i++)
            {
                TreeNode *temp = queue.back();
                ans.push_back(temp->val);
                queue.pop_back();
                if (temp->left) queue.push_front(temp->left);
                if (temp->right) queue.push_front(temp->right);
            }
        }
        return ans;


    }
};