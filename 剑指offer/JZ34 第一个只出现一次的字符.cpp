//手动 map到数组上

class Solution {
public:

    int FirstNotRepeatingChar(string str) {
        char indexArr[52] = {0};
        for(int i=0; i < str.size(); ++i)
        {
            if(('A' <= str[i]) && (str[i]<= 'Z'))
            {
                indexArr[str[i] - 'A'] ++;
            }
            else if(('a' <= str[i]) && (str[i] <= 'z'))
            {
                indexArr[str[i] - 'a' + 26] ++;
            }
        }

        for(int i=0; i < str.size(); ++i)
        {
            if(('A' <= str[i]) && (str[i]<= 'Z'))
            {
                if(indexArr[str[i] - 'A'] == 1) return i;
            }
            else if(('a' <= str[i]) && (str[i] <= 'z'))
            {
                if (indexArr[str[i] - 'a' + 26] == 1) return i;
            }
        }

        return -1;
    }
};