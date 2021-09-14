class Solution {
public:
    vector<int> res;
    unordered_map<int, int> dupMap;
    int duplicate(vector<int>& numbers) {
        for(int i = 0; i<numbers.size(); i++)
        {
            if(!dupMap.count(numbers[i]))
                dupMap.insert(make_pair(numbers[i], 1));
            else
                return numbers[i];
        }

        return -1;
//         for(auto iter=dupMap.begin(); iter != dupMap.end(); ++iter)
//         {
//             if(iter->second > 1) res.push_back(iter->first);
//         }

//         if(res.size()==0) return -1;
//         else {sort(res.begin(),res.end()); return res;}
    }
};