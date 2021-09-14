//回溯

class Solution {
public:
    string path;
    set<string> res;

    void backingTrace(string &str, vector<bool> &used)
    {
        if(path.size() == str.size())
        {
            res.insert(path);
            return;
        }

        for(int i=0; i<str.size(); ++i)
        {
            if(!used[i])
            {
                used[i] = true;
                path += str[i];
                backingTrace(str, used);
                path.pop_back();
                used[i] = false;
            }
        }

    }

    vector<string> Permutation(string str) {
        vector<bool> used(str.size(), 0);
        for(int i=0; i<used.size(); ++i) used[i] = 0;

        path.clear();
        res.clear();
        backingTrace(str,used);
        vector<string> ans;
        for(auto x:res) ans.push_back(x);
        return ans;
    }
};