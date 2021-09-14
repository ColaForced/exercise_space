//按照栈的要求去检验  每次循环压栈  每次压栈后出栈所有能出的  到最后栈空为真，否则为假
class Solution {
public:
    bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        int size = pushV.size();
        if (size == 0) return false;
        stack<int> jStack;
        int popIndex = 0;
        for(int i=0; i<size; ++i)
        {
            jStack.push(pushV[i]);
            while(!jStack.empty() && jStack.top() == popV[popIndex])
            {
                jStack.pop();
                popIndex ++ ;
            }
        }
        return jStack.empty();
    }
};