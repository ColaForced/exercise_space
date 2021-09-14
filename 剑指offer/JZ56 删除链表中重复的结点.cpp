/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};
*/
class Solution {
public:
    ListNode* deleteDuplication(ListNode* pHead) {
        ListNode *dummy = new ListNode(0);
        dummy->next = pHead;
        ListNode *A = dummy, *B = dummy->next;
        while(B != nullptr)
        {
            if(B->next != nullptr && B->val == B->next->val)
            {
                while(B->next != nullptr && B->val == B->next->val)
                {B = B->next;}
                A->next = B->next;
                B = B->next;
            }
            else
            {
                A = A->next;
                B = B->next;
            }
        }

        return dummy->next;
    }
};