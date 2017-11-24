#include <iostream>
#include <assert.h>
#include    <stack>

using namespace std;

void InsertSort(int* arr, size_t n)
{
    assert(arr && n > 0);
    int front = 0;
    for(; front < n - 1; ++front){
        int end = front;
        int tmp = arr[end + 1];
        while(end >= 0){
            if(tmp < arr[end]){
                arr[end + 1] = arr[end];
                --end;
            }
            else
                break;
        }
        arr[end + 1] = tmp;
    }
}

int GetMid(int* arr, int left, int right)
{
    int mid = ((right - left) >> 2 )+ left;
    //int mid = ((left^right) >> 1) + (left & right);
    if(arr[left] < arr[mid]){
        if(arr[mid] < arr[right]){
            return mid;
        }
        else if(arr[left] < arr[right]){
            return left;
        }
        else
            return right;
    }
    else{
        if(arr[left] < arr[right]){
            return left;
        }
        else if(arr[right] < arr[mid]){
            return mid;
        } 
        else 
            return right;
    }
}

int SortPart1(int* arr, int begin, int end)
{
    assert(arr);
    int cur = begin;
    int prev = cur - 1;
    int keyindex = GetMid(arr,begin,end);
    swap(arr[keyindex],arr[end]);
    int key = arr[end];
    while(cur < end){//arr[cur] 小于 key 时 prev一直跟在cur后面 一旦arr[cur] 大于key prev就不动了 
        if(arr[cur] < key && ++prev != cur)
            swap(arr[prev],arr[cur]);
        cur++;//cur在任何情况下都向后走
    }
    swap(arr[++prev],arr[end]);
    return prev;
}

int SortPart2(int* arr, int begin, int end)
{
    assert(arr);
    int key = arr[end];//以最后一个值作为key 并且保存key的值
    while(begin < end){
        while(arr[begin] <= key && begin < end)
            ++begin;
        arr[end] = arr[begin];
        while(arr[end] >= key && begin < end)
            --end;
        arr[begin] = arr[end];
    }
    if(begin == end)
        arr[begin] = key;
    return begin;
}

int SortPart3(int* arr, int begin, int end)
{
    assert(arr);
    int& key = arr[end];//key 一定要是引用
    while(begin < end){
        while(arr[begin] <= key && begin < end)
            ++begin;
        while(arr[end] >= key && begin < end)
            --end;
        if(begin < end)
            swap(arr[begin], arr[end]);
    }
    //if(begin == end)
    swap(arr[begin], key);//这里前面一定要是 key 让最后一个作为中间值的数字交换到它的位置上；
    return begin;
}


void quick_sort(int* arr, int begin, int end)
{
    assert(arr);
    if(begin >= end){
        return;
    }
    if(end - begin > 13){
         int div = SortPart1(arr, begin, end);
         quick_sort(arr, div + 1, end);
         quick_sort(arr, begin, div - 1);
    }
    else{
        InsertSort(arr+begin, end - begin + 1);
    }
}

void UR_quick_sort(int* arr, int begin, int end)
{
    assert(arr);
    stack<int> s;
    s.push(end);
    s.push(begin);
    while(!s.empty()){
        int left = s.top();
        s.pop();
        int right = s.top();
        s.pop();
        int div = SortPart1(arr, left, right);
        if(div - 1 > left){
            s.push(div - 1);
            s.push(left);
        }
        if(div + 1 <  right){
            s.push(right);
            s.push(div + 1);
        }
    }
}

void Print(int* arr)
{
    for(size_t i = 0 ; i < sizeof(arr)/sizeof(int); ++i){
        cout<<arr[i]<<" ";        
    }
    cout<<endl;
}

int main()
{
    int arr[] = {2,5,7,8,3,6,5,1,9,0,4,6,2,10,12,15,27,14};
    UR_quick_sort(arr,0,sizeof(arr)/sizeof(int)-1);
    for(size_t i = 0 ; i < sizeof(arr)/sizeof(int); ++i){
        cout<<arr[i]<<" ";        
    }
    cout<<endl;
    // Print(arr);
    int brr[] = {2,5,7,8,6,5,1,9,0,4,6,3};
    InsertSort(brr, sizeof(brr)/sizeof(int));
    for(size_t i = 0 ; i < sizeof(brr)/sizeof(int); ++i){
        cout<<brr[i]<<" ";
    }
    cout<<endl;
    return 0;
}
