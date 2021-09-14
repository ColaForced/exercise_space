#include <iostream>
#include <vector>
using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Solution {
public:
    TreeNode *help(vector<int> &pre, vector<int> &vin, int pre_left, int pre_right, int vin_left, int vin_right)
    {
        cout << pre_left<<" "<<pre_right<<" "<<vin_left<< " "<<vin_right<<endl;
        if(pre_left > pre_right) return nullptr;
        TreeNode *root = new TreeNode(pre[pre_left]);
        int i=0;
        for(i = vin_left; i <= vin_right; i++)
        {
            if (vin[i] == pre[pre_left])
            {
                root->left = help(pre, vin, pre_left + 1, pre_left + (i-vin_left), vin_left, i-1);
                root->right = help(pre, vin, pre_left + (i-vin_left) + 1, pre_right, i+1, vin_right);
            }
        }
        return root;

    }
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
        int pre_left = 0, pre_right = pre.size()-1;
        int vin_left = 0, vin_right = vin.size()-1;
        return help(pre, vin, pre_left, pre_right, vin_left, vin_right);
    }
};


int main()
{
    Solution sol;
    vector<int> pre = {1,2,4,7,3,5,6,8}, vin = {4,7,2,1,5,3,8,6};

    TreeNode *root = sol.reConstructBinaryTree(pre, vin);

}




