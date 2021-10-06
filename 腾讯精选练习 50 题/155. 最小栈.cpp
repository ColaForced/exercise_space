class MinStack {

private:
    stack<int> stack1_;
    stack<int> stack2_;

public:
    /** initialize your data structure here. */
    MinStack() {
        stack2_.push(INT_MAX);
    }

    void push(int val) {
        stack1_.push(val);
        stack2_.push(stack2_.top() > val? val: stack2_.top());
    }

    void pop() {
        stack1_.pop();
        stack2_.pop();
    }

    int top() {
        return stack1_.top();
    }

    int getMin() {
        return stack2_.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */