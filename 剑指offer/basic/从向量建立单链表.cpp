#include <vector>
using namespace  std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(val):val(val),next(nullptr){}
};


ListNode *buildLink(const vector<int> &nums)
{
    if(nums.size() == 0) return nullptr;
    ListNode *node = new ListNode(nums[0]);
    ListNode *root = node;
    for(int i=1; i<nums.size(); i++)
    {
        node->next = new ListNode(nums[i]);
        node = node->next;
    }
    return root;
}


int main()
{
    vector<int> nums = {1,2,3,4,5 };
    ListNode *root = buildLink(nums);
    while (root != nullptr)
    {
        cout << root->val<<" ";
        root = root->next;
    }

}

