//
// 思路：新建链表 注意进位即可
//

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *dummy = new ListNode();
        ListNode *cur = dummy;
        int flag = 0;
        while(l1 && l2)
        {
            int t = l1->val + l2->val;
            if(flag == 1)
            {
                t ++;
                flag = 0;
            }

            if(t >= 10)
            {
                flag = 1;
                t %= 10;
            }

            cur->next = new ListNode(t);
            cur = cur->next;
            l1 = l1->next;
            l2 = l2->next;
        }

        while(l1)
        {
            int t = l1->val;
            if(flag == 1)
            {
                t ++;
                flag = 0;
            }

            if(t >= 10)
            {
                flag = 1;
                t %= 10;
            }

            cur->next = new ListNode(t);
            cur = cur->next;
            l1 = l1->next;

        }

        while(l2)
        {
            int t = l2->val;
            if(flag == 1)
            {
                t ++;
                flag = 0;
            }

            if(t >= 10)
            {
                flag = 1;
                t %= 10;
            }

            cur->next = new ListNode(t);
            cur = cur->next;
            l2 = l2->next;

        }

        if (flag) {cur->next = new ListNode(1);}
        return dummy->next;
    }
};