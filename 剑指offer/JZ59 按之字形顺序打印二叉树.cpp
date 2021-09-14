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
    vector<vector<int> > Print(TreeNode* pRoot) {
        vector<vector<int> > res;
        if(!pRoot) return res;
        deque<TreeNode*> nodeQueue;
        nodeQueue.push_back(pRoot);
        int flag = 1;
        while(!nodeQueue.empty())
        {
            vector<int> temp;
            for(auto iter = nodeQueue.begin(); iter != nodeQueue.end(); ++iter)
            {
                temp.push_back((*iter)->val);
            }
            if(flag % 2 == 0) reverse(temp.begin(),temp.end());
            res.push_back(temp);
            flag ++;

            int n = nodeQueue.size();
            for(int i=0; i<n; i++)
            {
                TreeNode* temp = nodeQueue.front();
                nodeQueue.pop_front();
                if(temp->left) nodeQueue.push_back(temp->left);
                if(temp->right) nodeQueue.push_back(temp->right);
            }
        }
        return res;

    }

};