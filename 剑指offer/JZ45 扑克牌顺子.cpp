class Solution {
public:
    bool IsContinuous( vector<int> numbers ) {
        int min = 14, max = -1;
        unordered_set<int> intSet;
        for(int i=0; i<numbers.size(); i++)
        {
            if(numbers[i] != 0)
            {
                if(intSet.count(numbers[i]))
                    return false;
                else intSet.insert(numbers[i]);

                if(numbers[i]<min) min = numbers[i];
                if(numbers[i]>max) max = numbers[i];
            }
        }
        if (abs(max-min) > 4) return false;
        return true;
    }
};