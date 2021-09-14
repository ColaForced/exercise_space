/*
struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};
*/
class Solution {
public:
    RandomListNode* Clone(RandomListNode* pHead) {
        if(pHead == nullptr) return nullptr;
        RandomListNode *root = pHead;
        RandomListNode *tmp;
        while(pHead != nullptr)
        {
            tmp = pHead->next;
            pHead->next = new RandomListNode(pHead->label);
            pHead->next->next = tmp;
            pHead = tmp;
        }

//         while(root != nullptr)
//         {
//             cout<<root->label<<" ";
//             root = root->next;
//         }

        pHead = root;
        while(pHead != nullptr)
        {
            //这一句容易没考虑到 随机指向为null而造成内存访问错误
            pHead->next->random = pHead->random ==
                                  nullptr ? nullptr:pHead->random->next;
            pHead = pHead->next->next;
        }

//         while(root != nullptr)
//         {
//             cout<<root->label<<" ";
//             root = root->next;
//         }

        pHead = root->next;
        while(pHead->next != nullptr)
        {
            tmp = pHead->next;
            pHead->next = pHead->next->next;
            delete tmp;
            pHead = pHead->next;
        }

        pHead = root->next;
        delete root;
        return pHead;
    }
};