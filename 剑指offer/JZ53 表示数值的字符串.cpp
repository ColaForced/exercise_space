class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param str string字符串 
     * @return bool布尔型
     */
    bool isInt(string &str)
    {
        if(str.size() == 0) return false;
        int i = 0;
        while(str[i] == ' ') i++;
        if(str[i] == '-'||str[i] == '+') i++;
        if(str[i] == '0')
        {
            i++;
            while(i++ < str.size())
            {if(str[i] != ' ') return false;}
            return true;

        }
        if(str[i]<'1' || str[i]>'9') return false;
        i++;
        while(str[i] != ' ' && i < str.size())
        {
            if(str[i]<'0' || str[i]>'9')
                return false;
            i++;
        }
        i ++;
        while(i<str.size())
        {
            if(str[i] != ' ') return false;
        }
        return true;
    }

    bool isDemical(string &str)
    {
        if(str.size() == 0) return false;
        int i = 0;
        while(str[i] == ' ') i++;
        if(str[i] == '-'||str[i] == '+') i++;
        int flag = 0;
        if(str[i] != '.')
        {
            if((str[i]<'1' || str[i]>'9')) return false;
            i++;

            while(str[i] != '.' && i < str.size())
            {
                if(str[i]<'0' || str[i]>'9')
                    return false;
                i++;
            }
            i ++;
        }
        else
        {
            i++;
            flag = 1;
        }

        int cnt = 0;
        while((str[i]>='0') && (str[i]<='9') && i<str.size())
        {
            i++;
            cnt++;
        }

        if(flag == 1 && cnt == 0) return false;
        while(i<str.size())
        {
            if(str[i] != ' ') return false;
        }
        return true;
    }


    bool isScience(string &str)
    {
        if(str.size() == 0) return false;
        for(int i=0; i<str.size(); i++)
        {
            if (str[i] == 'e' || str[i] == 'E')
            {
                string leftStr = str.substr(0,i);
                string rightStr = str.substr(i+1,str.size() -1 -i);
                return (isInt(leftStr)||isDemical(leftStr)) && isInt(rightStr);
            }
        }
        return isInt(str)||isDemical(str);
    }

    bool isNumeric(string str) {
        return isScience(str);
    }
};