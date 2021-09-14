class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int> numbers) {
        map<int, int> countMap;
        for(auto n:numbers)
        {
            if(countMap.count(n))
            {
                countMap[n] ++;
            }
            else
            {
                countMap[n] = 1;
            }
            if(countMap[n] > numbers.size()/2)
            {
                return n;
            }
        }
        return -1;
    }
};