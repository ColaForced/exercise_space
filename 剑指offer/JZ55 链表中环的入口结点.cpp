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
    ListNode* EntryNodeOfLoop(ListNode* pHead) {
        ListNode *fast = pHead, *slow = pHead;
        while(fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            if(fast == slow) break;
        }
        if(!fast || !fast->next) return nullptr;

        slow = pHead;
        while(fast != slow)
        {
            fast = fast->next;
            slow = slow->next;
        }
        return slow;
    }
};