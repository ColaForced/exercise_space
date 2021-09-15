//先map记录一些结果
class Solution {
public:
    map<pair<int, int>, int> multiMap;

    void cntMap(const vector<int> &A)
    {
        multiMap.insert(make_pair(make_pair(0, 0), A[0]));
        for(int i=1; i<A.size(); i++)
            multiMap.insert(make_pair(make_pair(0, i), multiMap[make_pair(0, i-1)]* A[i]));

        multiMap.insert(make_pair(make_pair(A.size()-1, A.size()-1), A[A.size()-1]));
        for(int i=A.size()-2; i>=0; i--)
            multiMap.insert(make_pair(make_pair(i, A.size()-1), multiMap[make_pair(i+1, A.size()-1)]* A[i]));
    }

    vector<int> multiply(const vector<int>& A) {
        multiMap.clear(); cntMap(A);
        vector<int> B;
        for(int i=0; i<A.size(); i++)
        {
            int val;
            if(i == 0)
                val = multiMap[make_pair(1,A.size()-1)];
            else if(i == A.size()-1)
                val = multiMap[make_pair(0,A.size()-2)];
            else
                val = multiMap[make_pair(0,i-1)] * multiMap[make_pair(i+1,A.size()-1)];
            B.push_back(val);
        }
        return B;
    }
};