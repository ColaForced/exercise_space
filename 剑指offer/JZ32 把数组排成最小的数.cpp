class Solution {
public:
    static bool compare_less(int a, int b)
    {
        int buf[50];
        return to_string(a) + to_string(b) <= to_string(b) + to_string(a);
    }

    string PrintMinNumber(vector<int> numbers) {
//         for(int i=0; i<numbers.size(); ++i)
//         {
//             for(int j=0; j<numbers.size(); ++j)
//             {
//                 if(compare_less(numbers[i], numbers[j]))
//                 {
//                     int temp = numbers[i];
//                     numbers[i] = numbers[j];
//                     numbers[j] = temp;
//                 }
//             }
//         }
        sort(numbers.begin(),numbers.end(),compare_less);
        string ans = "";
        for(int k=0; k<numbers.size(); k++)
        {
            ans += to_string(numbers[k]);
        }
        return ans;
    }
};