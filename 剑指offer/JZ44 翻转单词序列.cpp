class Solution {
public:
    string ReverseSentence(string str) {
        if(str.size() <= 1) return str;
        vector<string> strVec;
        string tempStr;
        for(auto s:str)
        {
            if(s != ' ') tempStr += s;
            else {strVec.push_back(tempStr); tempStr.clear();}
        }
        if(tempStr.size() != 0) strVec.push_back(tempStr);

        reverse(strVec.begin(), strVec.end());

        string ans = "";
        for(int i=0; i<strVec.size()-1; i++)
        {
            ans += strVec[i];
            ans += " ";
        }
        ans += *--strVec.end();
        return ans;
    }
};