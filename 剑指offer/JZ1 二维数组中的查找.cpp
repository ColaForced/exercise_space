//思路： 从左下角往右上角查找，每个数的上面的数比他小，右边的数比他大
class Solution {
public:
    bool Find(int target, vector<vector<int> > array) {
        if (array.size() == 0) {return false;}
        if (array[0].size() == 0) {return false;}
        int x = array.size() - 1;
        int y = 0;

        while(x >= 0 && y <= array[0].size()-1)
        {
            if (array[x][y] == target)
            {
                return true;
            }
            else if(array[x][y] > target)
            {
                x --;
            }
            else if(array[x][y] < target)
            {
                y ++;
            }
        }
        return false;
    }

};