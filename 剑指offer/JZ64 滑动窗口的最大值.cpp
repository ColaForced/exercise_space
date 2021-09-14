

class Solution {
public:
    vector<int> maxInWindows(const vector<int>& num, unsigned int size) {
        if(size == 0) return vector<int>();
        deque<pair<int, int> > nDeque;
        vector<int> res;

        for(int i=0; i<size-1; i++)
        {
            while(!nDeque.empty() && num[i] > nDeque.front().first)
            {
                nDeque.pop_front();
            }
            nDeque.push_front(make_pair(num[i],i));
        }

        for(int i = size-1; i<num.size(); i++)
        {
            while(!nDeque.empty() && num[i] > nDeque.front().first)
            {
                nDeque.pop_front();
            }
            nDeque.push_front(make_pair(num[i],i));

            if(i - nDeque.back().second >= size)
            {nDeque.pop_back();}

            res.push_back(nDeque.back().first);
        }
        return res;
    }
};