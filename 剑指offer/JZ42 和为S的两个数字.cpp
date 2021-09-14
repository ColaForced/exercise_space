class Solution {
public:
    bool compare(vector<int> &a, vector<int>&b)
    {
        return abs(a[0] - a[1]) < abs(b[0] - b[1]);
    }

    vector<int> FindNumbersWithSum(vector<int> array,int sum) {
        unordered_map<int,int> recordMap;
        vector<vector<int> > tempVvec;
        vector<int> res;
        for(int i=0; i<array.size(); i++)
        {
            if(!recordMap.count(array[i]))
            {
                recordMap.insert(make_pair(array[i], i));
            }

            if(recordMap.count(sum - array[i]))
            {
                if(recordMap[sum - array[i]] == i) continue; //避免重复选同一个元素
                vector<int> tempVec;
                tempVec.push_back(sum-array[i]);
                tempVec.push_back(array[i]);
                tempVvec.push_back(tempVec);
            }
        }
//         for(auto x:tempVvec)
//         {
//             for(auto y:x)
//                 cout<<y<<" ";
//             cout<<endl;
//         }
        if(tempVvec.size() == 0) return vector<int>();
        sort(tempVvec.begin(),tempVvec.end());
        return tempVvec[0];
    }
};