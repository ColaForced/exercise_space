//
// Created by peng on 2021/9/14.
//

class Solution {
public:
    int minNumberInRotateArray(vector<int> rotateArray) {
        int size = rotateArray.size();
        if (size == 0) return 0;
        if (size == 1) return rotateArray[0];
        int pre = 1, back = 0;
        while(back != size)
        {
            if (rotateArray[pre] < rotateArray[back])
            {
                return rotateArray[pre];
            }
            back ++; pre ++;
        }
        return rotateArray[0];
    }
};