struct LinkNode
{
    int val;
    LinkNode *next;
    LinkNode(int val):val(val), next(nullptr){}
};


class Solution {
public:
    int LastRemaining_Solution(int n, int m) {
        if(n == 0) return -1;
        LinkNode *head = new LinkNode(0);
        LinkNode *cur = head;
        for(int i=1; i<n; i++)
        {
            cur->next = new LinkNode(i);
            cur = cur->next;
        }
//         while(head != nullptr) {cout<< head->val << " "; head = head->next;}

        cur->next = head;

        while(head->next != head)
        {
            for(int i=0; i<m-2; i++) //这里m-2略微麻烦，手动计算得出
            {
                head = head->next;
            }
            head->next = head->next->next;
            head = head->next;//这一行容易忘记， 删除节点后忘记自身跳转了
        }

        return head->val;
    }
};