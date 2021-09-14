#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>


template <typename type>
void swap(type *a, type *b)
{

    type temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief: 冒泡排序；添加标志位isSort来判断是否已经有序以减少重复遍历
 * @time cpl: O(n^2)
 * @space cpl: O(1)
 **/
template <typename type>
void bubble_sort(type *arr, int size)
{
    int i,j;
    for(i=0; i<size-1; i++)
    {
        bool isSort = true;
        for (j = 0; j < size - 1 - i; j++)
        {
            if (*(arr + j) > *(arr + j + 1))
            {
                swap(arr + j, arr + j + 1);
                isSort = false;
            }

        }
        if (isSort) break;
    }
}


/**
 * @brief: 选择排序；
 * @time cpl: O(n^2)
 * @space cpl: O(1)
 **/
template<typename type>
void select_sort(type *arr, int size)
{
    int i,j,min;
    for(i=0; i<size; i++)
    {
        min = i;
        for(j=i+1; j<size; j++)
        {
            if (*(arr + j) < *(arr + i))
                min = j;
        }
        swap(arr+min, arr + i);
    }
}



/**
 * @brief: 插入排序；
 * @time cpl: O(n^2)
 * @space cpl: O(1)
 * @trouble：边界条件难处理
 **/
template<typename type>
void insert_sort(type *arr, int size)
{
    int i,j;
    type tmp;

    for(i=1; i<size; i++)
    {
        tmp = *(arr+i);
        for(j=i-1; j>=0; j--)
        {
            if (*(arr+j) > tmp)
                *(arr+j+1) = *(arr+j);
            else
                break;
        }
        *(arr+j+1) = tmp;
    }
}



/**
 * @brief: 希尔排序 = 数据分组 + 插入排序
 * @time cpl: O(n^1.3)
 * @space cpl: O(1)
 * @trouble：
 **/
template <typename type>
void shell_sort(type *arr, int size)
{
    int gap;
    for(gap = size/2; gap>0; gap/=2)
    {
        int i,j;
        type tmp;

        for(i = gap; i<size; i++)
        {
            tmp = arr[i];
            for(j = i-gap; j>=0; j-=gap)
            {
                if(arr[j] > tmp)
                    arr[j+gap] = arr[j];
                else
                    break;
            }
            arr[j+gap] = tmp;
        }
    }
}




/**
 * @brief: 归并排序: 递归，分治
 * @time cpl: O(nlog n)
 * @space cpl: O(n)
 * @trouble：
 **/
template <typename type>
void merge_helper(type *arr, type *tmp, int start, int mid, int end);

template <typename type>
void merge_sort_helper(type *arr, type *tmp, int start, int end);

//容易出错传入end = size
template <typename type>
void merging_sort(type *arr, int size)
{
    type tmp[size];
    merge_sort_helper(arr, tmp, 0, size-1);
}

template <typename type>
void merge_two_array(type *arr, type *tmp, int start, int mid, int end)
{
    int i = start, j = mid + 1;
    int m = mid, n = end;
    int k = 0;
    while(i<=m && j<=n)
    {
        if (arr[i] <= arr[j])
            tmp[k++] = arr[i++];
        else
            tmp[k++] = arr[j++];
    }

    while (i<=m)    tmp[k++] = arr[i++];
    while (j<=n)    tmp[k++] = arr[j++];
    for(i = 0; i<k; i++)    arr[start+i] = tmp[i];
}

template <typename type>
void merge_sort_helper(type *arr, type *tmp, int start, int end)
{
    if(end <= start) return;
    int mid = start + (end -start)/2;
    merge_sort_helper(arr, tmp, start, mid);
    merge_sort_helper(arr, tmp, mid+1, end);
    merge_two_array(arr, tmp, start, mid, end);
}



/**
 * @brief: 快速排序: 递归，分治
 * @time cpl: O(nlog n)
 * @space cpl: O(1)
 * @trouble：
 **/
template <typename type>
void quick_sort_helper(type *arr, int start, int end);

template <typename type>
int partition(type *arr, int start, int end);

template <typename type>
void quick_sort(type *arr, int size)
{
    quick_sort_helper(arr, 0, size-1);
}

template <typename type>
void quick_sort_helper(type *arr, int start, int end)
{
    if (start > end) return;

    int pivotIndex = partition(arr, start, end);
    quick_sort_helper(arr, start, pivotIndex - 1);
    quick_sort_helper(arr, pivotIndex + 1, end);
}

template <typename type>
int partition(type *arr, int start, int end)
{
    int l = start, r = end, pivot = arr[start];
    type tmp;

    while (true)
    {
        while (arr[l] <= pivot)
        {
            l ++;
            if(l == r) {break;}
        }

        while (arr[r] > pivot)
        {
            r--;
            if(l == r) {break;}
        }

        if(l >= r)
        {
            break;
        }
        else
        {
            tmp = arr[l];
            arr[l] = arr[r];
            arr[r] = tmp;
        }
    }

    tmp = arr[start];
    arr[start] = arr[r];
    arr[r] = tmp;
    return r;
}



/**
 * @brief: 堆排序：大根堆，不断交换堆首和数组尾部，堆尺寸-1，更新堆。
 * @time cpl: O(nlog n)
 * @space cpl: O(1)
 * @trouble：
 **/
template <typename type>
void max_heap_sink(type *arr, int i, int size);

template <typename type>
void max_heap_build(type *arr, int size);

template <typename type>
void heap_sort(type *arr, int size)
{
    max_heap_build(arr, size);
    int i;
    for(i = size-1; i>0; i--)
    {
        swap(arr, arr+i);
        max_heap_sink(arr, 0 ,i);
    }
}

template <typename type>
void max_heap_sink(type *arr, int i, int size)
{
    int l = 2*i + 1;
    int r = 2*i + 2;
    int largest = i;

    if(l<size && arr[l] > arr[largest])
    {
        largest = l;
    }

    if(r<size && arr[r] > arr[largest])
    {
        largest = r;
    }

    if (largest != i)
    {
        swap(arr+i, arr+largest);
        max_heap_sink(arr, largest, size);
    }
}

template <typename type>
void max_heap_build(type *arr, int size)
{
    int i;
    for(i = size/2 - 1; i>=0; i--)
    {
        max_heap_sink(arr, i, size);
    }
}


/**
 * @brief: 计数排序: 仅适用于正整数且取值相差不大
 * @time cpl: O(n+d)
 * @space cpl: O(n+d)
 * @trouble：
 **/
void count_sort(int *arr, int size)
{
    int i=0, max = arr[0];

    for(i=0; i<size; i++)
    {
        if(max < arr[i])
        {
            max = arr[i];
        }
    }

    int counterArr[max + 1] = {0};

    for(i=0; i < size; i++)
    {
        counterArr[arr[i]]++;
    }

    for(i=1; i<max+1; i++)
    {
        counterArr[i] = counterArr[i-1] + counterArr[i];
    }

    int sortedArr[size] = {0};
    for(i = size-1; i>=0; i--)
    {
        sortedArr[counterArr[arr[i]]-1] = arr[i];
        counterArr[arr[i]]--;
    }

    for(i=0; i<size; i++)
    {
        arr[i] = sortedArr[i];
    }
}


/**
 * @brief: 桶排序
 * @time cpl: O(nlog(n / m))  best:log(n)   worst: log(n)
 * @space cpl:O(n)
 * @trouble：桶的划分
 **/
void bucket_sort(int *arr, int size)
{
    using namespace std;

    if (size == 0) return ;

    int max = arr[0], min = arr[0];
    int i;
    for(i=0; i<size; i++)
    {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }

    vector<vector<int>> bucketList;
    for(i=0; i<size; i++)
        bucketList.push_back(vector<int>());

    int diff = max - min;
    int num;
    float section = (float) diff/ (float) (size - 1);
    for(i=0; i<size; i++)
    {
        num = (int)(arr[i]/section) - 1;
        if (num<0) num = 0;
        bucketList[num].push_back(arr[i]);
    }

    for(i=0; i<bucketList.size(); i++)
        sort(bucketList[i].begin(),bucketList[i].end());

    i = 0;
    for(auto buckVec:bucketList)
    {
        for(auto val:buckVec)
        {
            arr[i] = val;
            i++;
        }
    }
}


/**
 * @brief: 基数排序
 * @time cpl: O(d+n)
 * @space cpl: O(d+n)
 * @trouble：诸如电话号码，usec时间戳是比较合适的
 **/
void cardinal_number_sort(int *arr, int size)
{
    using namespace std;

    if (size == 0) return ;

    int max = arr[0];
    int i = 0, j = 0, k = 0;

    for(i = 0; i<size; i++)
    {
        if (arr[i] > max) max = arr[i];
    }

    vector<vector<int>> bucketList;
    for(i=0; i<10; i++)
        bucketList.push_back(vector<int>());

    int location = 1;
    int number;
    while(true)
    {
        int dd = (int) pow(10, location-1);
        if (max<dd) break;

        for(i = 0; i<size; i++)
        {
            number = (arr[i]/dd) % 10;
            bucketList[number].push_back(arr[i]);
        }


        for(i=0; i<10; i++)
        {
            for(j = 0; j<bucketList[i].size(); j++)
            {
                arr[k++] = bucketList[i][j];
            }
            bucketList[i].clear();
        }
        location ++;

    }
}

int main() {
    //    float arry[] = {1,2.5,-3,3};
    //    float arry[] = {1,2,3,4,5};
    //    float arry[] = {1,2,-1,4,5};
    //    int n = sizeof(arry)/sizeof(arry[0]);
    //    bubble_sort(arry, n);
    //    select_sort(arry,n);
    //    insert_sort(arry,n);
    //    shell_sort(arry, n);
    //    merging_sort(arry, n);
    //    quick_sort(arry, n);
    //    heap_sort(arry, n);

    //    int arry[] = {1,2,3,2,1,10};
    //    int n = sizeof(arry)/sizeof(arry[0]);
    //    count_sort(arry,n);
    //    bucket_sort(arry, n);


    int arry[] = {1,2,3,2,1,10,100,200,300,401,555};
    int n = sizeof(arry)/sizeof(arry[0]);
    cardinal_number_sort(arry,n);

    for(auto a:arry)
        std::cout << a << " ";

    return 0;
}



