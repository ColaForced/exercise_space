//滑动窗口


class Solution {
public:
    vector<vector<int> > FindContinuousSequence(int sum) {
        vector<vector<int> > res;
        int plow = 1, phigh = 2;
        while((phigh < sum) && (plow < phigh))
        {
            int val = (phigh-plow+1)*(phigh + plow)/2;
            if(sum == val)
            {
                vector<int> tempSeq;
                for(int i=plow; i<=phigh; i++) {tempSeq.push_back(i);}
                res.push_back(tempSeq);
                phigh++; plow++;
            }
            else if(sum > val)
                phigh ++;
            else if(sum < val)
                plow ++;
        }
        return res;
    }
};