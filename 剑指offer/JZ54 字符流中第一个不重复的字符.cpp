class Solution
{
public:
    deque<char> chDeq;
    unordered_map<char, int> chMap;
    //Insert one char from stringstream
    void Insert(char ch) {
        if(!chMap.count(ch))
        {
            chMap.insert(make_pair(ch,1));
            chDeq.push_back(ch);
        }
        else
        {
            chMap[ch] ++;
        }


    }
    //return the first appearence once char in current stringstream
    char FirstAppearingOnce() {
        while(chDeq.size() != 0)
        {
            char ch = chDeq.front();
            if(chMap[ch] == 1)
            {
                return ch;
            }
            else
            {
                chDeq.pop_front();
            }
        }
        return '#';
    }

};