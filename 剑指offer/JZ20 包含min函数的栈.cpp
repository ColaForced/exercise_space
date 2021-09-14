//双栈法  一个记录所有信息  一个只记录最小值

class Solution {
public:
    void push(int value) {
        mstack1.push(value);
        if(mstack2.empty()) mstack2.push(value);
        else if(value <= mstack2.top()) mstack2.push(value);
    }

    void pop() {
        if (mstack1.top() == mstack2.top()) mstack2.pop();
        mstack1.pop();

    }
    int top() {
        return mstack1.top();
    }
    int min() {
        return mstack2.top();
    }

private:
    stack<int> mstack1, mstack2;
};