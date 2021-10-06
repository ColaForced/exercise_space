class Solution {
public:
    string multiply(string num1, string num2) {
        int len1 = num1.size(), len2 = num2.size();
        vector<int> fvec(len1 + len2 -1 , 0); //len1 + len2 -1 易错

        for(int i=0; i<len1; i++)
        {
            for(int j=0; j<len2; j++)
            {
                fvec[i+j] += (num1[len1-i-1] - '0') * (num2[len2-j-1] - '0');
            }
        }

        int over = 0;
        for(int k=0; k<fvec.size(); k++)
        {
            fvec[k] += over;
            over = fvec[k] / 10;
            fvec[k] %= 10;
        }

        if (over != 0) fvec.push_back(over);


        //去除首0易错
        int k = fvec.size()-1;
        while (k>0 && fvec[k] == 0) k--;
        string res;
        while(k>=0) res += (fvec[k--] + '0');
        return res;
    }
};