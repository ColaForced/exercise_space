class Solution {
public:
    ListNode* ReverseList(ListNode* pHead) {
        ListNode *pre = nullptr;
        ListNode *nxt = nullptr;
        ListNode *cur = pHead;
        while(cur)
        {
            nxt = cur->next;
            cur->next = pre;
            pre = cur;
            cur = nxt;
        }
        return pre;
    }
};


int main() {
    ListNode *node1 = new ListNode(1);
    ListNode *node2 = new ListNode(2);
    ListNode *node3 = new ListNode(3);
    node1->next = node2;
    node2->next = node3;
    ListNode *rnode = ReverseList(node1);
    while(rnode)
    {
        cout << rnode->val<<" "<<endl;
        rnode = rnode->next;
    }

}