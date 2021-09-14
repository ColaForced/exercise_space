class Solution {
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        priority_queue<int, vector<int>, greater<int> > pq;
        for(auto n:input) pq.push(n);

        vector<int> ans;
        for(int i=0; i<k; i++)
        {
            ans.push_back(pq.top());
            pq.pop();
        }
        return ans;
    }
};

// class Solution {
// public:
//     vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
//         sort(input.begin(), input.end());
//         vector<int> ans;
//         for(int i=0; i<k; i++)
//         {
//             ans.push_back(input[i]);
//         }
//         return ans;
//     }
// };