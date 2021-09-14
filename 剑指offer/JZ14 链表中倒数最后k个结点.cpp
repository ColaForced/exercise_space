//思路： 前后k间隔的双指针指针 一起移动
/**
 * struct ListNode {
 *	int val;
 *	struct ListNode *next;
 *	ListNode(int x) : val(x), next(nullptr) {}
 * };
 */
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param pHead ListNode类
     * @param k int整型
     * @return ListNode类
     */
    ListNode* FindKthToTail(ListNode* pHead, int k) {
        // write code here
        ListNode *pre = pHead;
        if (pre == nullptr) return nullptr;
        while(--k)
        {
            if (pre->next == nullptr)
            {
                return nullptr;
            }
            pre = pre->next;
        }

        while(pre->next != nullptr)
        {
            pre = pre->next;
            pHead = pHead->next;
        }

        return pHead;
    }
};