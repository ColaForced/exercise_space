class Solution {
public:
    int GetNumberOfK(vector<int> data ,int k) {
        int l = 0, r = data.size()-1;
        int cnt = 0;
        while(l<=r)
        {
            int mid = l + (r-l)/2;
            if(data[mid] == k)
            {
                cout<<mid<<endl;
                int rm = mid, lm = mid;
                while(rm++ <= r)
                {
                    if(data[rm] > k) break;
                    if(data[rm] == k) cnt++;
                }
                while(lm-- >= l)
                {
                    if(data[lm] < k) break;
                    if(data[lm] == k) cnt++;
                }
                return cnt+1;
            }

            else if(data[mid] > k)
            {
                r = mid - 1;
            }

            else if(data[mid] < k)
            {
                l = mid + 1;
            }
        }
        return cnt;
    }
};