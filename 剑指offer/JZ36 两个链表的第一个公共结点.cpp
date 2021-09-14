/*
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};*/
class Solution {
public:
    ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
        if(!pHead1 || !pHead2) return nullptr;
        ListNode *root1 = pHead1, *root2 = pHead2;
        while(pHead1 != pHead2)
        {
            pHead1 = pHead1->next; pHead2 = pHead2->next;
            if(!pHead1 && !pHead2) return nullptr;
            if(!pHead1 && pHead2) pHead1 = root2;
            else if(pHead1 && !pHead2) pHead2 = root1;
            if(pHead1 == pHead2) return pHead1;

        }
        return pHead1;
    }
};