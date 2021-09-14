//归并排序 归并时计数


const long int M = 1000000007;

class Solution {

private:
    int res;

public:
    void merge_two_array(vector<int> &arr, vector<int> &tmp, int start, int mid, int end)
    {
        int i = start, j = mid + 1;
        int m = mid, n = end;
        int k = 0;
        while(i<=m && j<=n)
        {
            if (arr[i] <= arr[j])
            {tmp[k++] = arr[i++];}
            else
            {
                tmp[k++] = arr[j++];
                res = (res + mid-i+1) % M;
            }
        }

        while (i<=m)    tmp[k++] = arr[i++];
        while (j<=n)    tmp[k++] = arr[j++];
        for(i = 0; i<k; i++)    arr[start+i] = tmp[i];
    }

    void merge_sort_helper(vector<int> &arr, vector<int> &tmp, int start, int end)
    {
        if(end <= start) return;
        int mid = start + (end -start)/2;
        merge_sort_helper(arr, tmp, start, mid);
        merge_sort_helper(arr, tmp, mid+1, end);
        merge_two_array(arr, tmp, start, mid, end);
    }

    void merging_sort(vector<int> &data)
    {
        vector<int> tmp(data.size(),0);
        merge_sort_helper(data, tmp, 0, data.size()-1);
    }

    int InversePairs(vector<int> data) {
        res = 0;
        merging_sort(data);
        return res;
    }
};