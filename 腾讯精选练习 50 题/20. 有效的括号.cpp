class Solution {
public:
    bool isValid(string s) {
        map<char,char> smap;
        smap.insert(make_pair('{','}'));
        smap.insert(make_pair('(',')'));
        smap.insert(make_pair('[',']'));

        stack<char> sstack;
        sstack.push('?');

        for(auto x:s)
        {
            if(smap.find(x) != smap.end())
            {
                sstack.push(x);
            }
            else
            {
                if(smap[sstack.top()] != x) return false;
                else sstack.pop();
            }
        }
        return sstack.size() == 1;


    }
};