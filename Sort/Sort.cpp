#include <iostream>
#include <assert.h> 
#include    <stack> 
#include<string.h>

using namespace std; 

void Print(int* arr,size_t n) 
{ 
    for(size_t i = 0 ; i < n; ++i){ 
        cout<<arr[i]<<" ";
    } 
    cout<<endl; 
} 

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

void ShellSort(int* arr, size_t n)
{
    assert(arr);
    int gap = n;
    while(gap > 1)//就是在插入排序基础上加gap
    {
        gap = gap / 3 +1;
        for(size_t front = 0; front < n - gap; ++front){
            int end = front;
            int tmp = arr[end + gap];
            while(end >= 0){
                if(tmp > arr[end]){
                    arr[end + gap] = arr[end];
                    end -= gap;
                }
                else 
                    break;
            }
            arr[end + gap] = tmp;
        }
    }    
}

void AdjustDown(int* arr, size_t n, int root)
{
    assert(arr);
    int parent = root;
    int child = parent * 2 + 1;
    while(child < n){//n是最后一个数字的索引
        if(child+ 1 < n && arr[child] < arr[child+1] )
            child++;
        else if(arr[child] > arr[parent]){
            swap(arr[child],arr[parent]);
            parent = child;
            child = parent * 2 + 1;
        }
        else
            break;
    }
}

void HeapSort(int* arr, size_t n)
{
    for(int i = (n - 2)>>2; i >= 0; --i){
        AdjustDown(arr,n,i);
    }
    int end = n - 1;
    while(end){
        swap(arr[end], arr[0]);
        AdjustDown(arr,end,0);
        --end;
    }
}

int GetMid(int* arr, int left, int right)
{//三数取中 先和中间比  大的分两种情况考虑
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
{//非递归版本
    assert(arr);
    stack<int> s;
    s.push(end);
    s.push(begin);//先压end再压begin 
    while(!s.empty()){
        int left = s.top();//后进先出  这里可视作每一层递归的返回
        s.pop();
        int right = s.top();
        s.pop();
        int div = SortPart1(arr, left, right);
        if(div - 1 > left){//这里两个if{} 相当于两个分叉的递归
            s.push(div - 1);
            s.push(left);
        }
        if(div + 1 <  right){
            s.push(right);
            s.push(div + 1);
        }
    }
    Print(arr,end+1);
}

void _MerageSort(int* arr, int* tmp, int left,int right)
{
    if(left >= right)
        return;
    int mid = ((left ^ right)>>1) + (left & right);
    if(right - left > 13){
        _MerageSort(arr,tmp,left,mid);
        _MerageSort(arr,tmp,mid + 1,right);
    }
    else{
        InsertSort(arr+left, right-left + 1);
    }
    int begin1 = left;
    int begin2 = mid + 1;
    int end1 = mid ;
    int end2 = right;
    int begin = begin1;
    int index = begin1;
    while(begin1 <= end1 && begin2 <= end2){
        if(arr[begin1] < arr[begin2]){
            tmp[index++] = arr[begin1++];
        }
        else
            tmp[index++] = arr[begin2++];
    }
    while(begin1 <= end1){
        tmp[index++] = arr[begin1++];
    }
    while(begin2 <= end2){
        tmp[index++] = arr[begin2++];
    }
    while(begin <= end2){
        arr[begin] = tmp[begin];
        begin++;
    }
}

void  UR_MerageSort_Part(int* arr, int* tmp, int begin1, int begin2,int end1, int end2)
{
    int index = begin1;
    int begin = begin1;
    //int mid = ((left ^ right)>>1) + (left & right);
    //int begin1 = left;
    //int end1 = mid;
    //int begin2 = mid + 1;
    //int end2 = right;
    //int begin = begin1;
    //int index = begin1;
    while(begin1 <= end1 && begin2 <= end2){
        if(arr[begin1] > arr[begin2]){
            tmp[index++] = arr[begin2++];
        }else{
            tmp[index++] = arr[begin1++];
        }
    }
    while(begin1 <= end1){
        tmp[index++] = arr[begin1++];
    }
    while(begin2 <= end2){
        tmp[index++] = arr[begin2++];
    }
    while(begin <= end2){
        arr[begin] = tmp[begin];
        ++begin;
    }
    return;
}

void UR_MerageSort(int* arr, size_t n)
{
    assert(arr);

    

    Print(arr,n);
}

void MerageSort(int* arr, size_t n)
{
    assert(arr);
    int left = 0;
    int right = n - 1;
    int* tmp = new int[n];
    _MerageSort(arr,tmp, left,right);
    delete[] tmp;
    Print(arr,n);
    return;
}

void BubbleSort(int* arr, size_t n)
{
    for(int end = n - 1; end >= 0; --end){
        bool flag = false;
        for(int i =0 ; i < end - 1; ++i){
            if(arr[i] > arr[i + 1]){
                swap(arr[i], arr[i + 1]);
                flag = true;
            }
        }
        if(!flag)
            break;
    }
    Print(arr,n);
}

//计数排序
void CountSort(int* arr, size_t n)
{
    assert(arr);
    int max = arr[0];
    int min = arr[0];
    for(int i = 1; i < n; ++i){
        if(arr[i] > max)
            max = arr[i];
        if(arr[i] < min)
            min = arr[i];
    }
    int range = max - min;
    int* tmp = new int[range];
    memset(tmp,0,sizeof(int)*range);
    for(int i = 0; i < n ; ++i){
        tmp[arr[i] - min]++;
    }
    int index = 0;
    for(int i = 0; i < n ; ++i){
        while(tmp[i]--){
            arr[index++] = i + min;
        }
    }
    delete[] tmp;
    Print(arr,n);
}

//基数排序
int CountDigit(int* arr, size_t n)
{
    int digit = 1;
    int base = 10;
    for(int i = 0; i < n ; ++i){
        while(arr[i] >= base){
            digit++;
            base *= 10;
        }
    }
    return digit;
}

void BaseSort(int* arr, size_t n)
{
    int base = 1;
    int digit = CountDigit(arr,n);
    int* tmp = new int[n];
    while(digit--){
        int count[10] = {0};
        for(int i = 0; i < n; ++i){//保存这一位为index数字的数出现的次数
            int index = arr[i] / base % 10;
            count[index]++;
        }
        memset(tmp,0,sizeof(int)*n);
        int start[10] = {0};
        for(int i = 1; i < 10; ++i){//算这一位数是i的数字第一次出现的位置
            start[i] = start[i - 1] + count[i - 1];
        }
        for(int i = 0 ; i < n ; ++i){//把数拷贝到辅助空间
            int index = arr[i] / base % 10;
            tmp[start[index]++] = arr[i];//为什么要start【index】++ 
                                        //是因为相同index的两个arr【i】顺序向后放。
        }
        for(int i = 0; i < n; ++i){//拷贝回来
            arr[i] = tmp[i];
        }
        base *= 10;
    }
    Print(arr, n);
}

int main()
{
    int arr[] = {2,5,7,8,3,6,5,1,9,0,4,6,2,10,12,15,27,14};
    //UR_quick_sort(arr,0,sizeof(arr)/sizeof(int)-1);
    int brr[] = {2,5,7,8,6,5,1,9,0,4,6,3};
    MerageSort(arr,sizeof(arr)/sizeof(int));
    BubbleSort(arr,sizeof(arr)/sizeof(int));
    CountSort(arr,sizeof(arr)/sizeof(int));
    BaseSort(arr,sizeof(arr)/sizeof(int));
    //Print(arr, sizeof(arr)/sizeof(int));
    //UR_MerageSort(arr,sizeof(arr)/sizeof(int));
    //Print(arr, sizeof(arr)/sizeof(int));
    //InsertSort(brr, sizeof(brr)/sizeof(int));
   // ShellSort(arr, sizeof(arr)/sizeof(int));
    
    return 0;
}
