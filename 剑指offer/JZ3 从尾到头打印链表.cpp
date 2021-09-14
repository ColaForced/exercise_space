//思路：函数栈， 打印主体放在递归之后，先递归，后打印
/**
*  struct ListNode {
*        int val;
*        struct ListNode *next;
*        ListNode(int x) :
*              val(x), next(NULL) {
*        }
*  };
*/
class Solution {
public:
    vector<int> ans;
    vector<int> printListFromTailToHead(ListNode* head)
    {
        ListNode *p = head;
        if(p != nullptr)
        {
            if(p->next != nullptr)
            {
                printListFromTailToHead(p->next);
            }
            ans.push_back(p->val);
        }
        return ans;
    }
};