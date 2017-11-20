#include<iostream>

#include<vector>

#include<map>

#include<unordered_map>

//#include<algorithm>
using namespace std;
//leetcode.com/problems/find-pivot-index/description/
int pivotIndex(vector<int>& nums)
{
    int total = 0;
    for(size_t i = 0; i < nums.size(); ++i){
        total += nums[i];
    }
    int sum = 0;
    for(size_t i = 0; i < nums.size(); ++i){
        sum += nums[i];
        if(sum * 2 == total - nums[i+ 1])
            return i + 1;
    }
    return -1;
}

//https://leetcode.com/problems/degree-of-an-array/description/

int FindShortestSubArray(vector<int>& arr)
{
    //本题中一个数的”度“代表在数组中可以包涵所有相同数的最小长度。
    if(arr.size() < 2)
       return arr.size();
    int length = arr.size();
    unordered_map<int,int> startindex, appercount;//因为要求包含所有出现次数最多的数的最短长度
    //所以必须计算每个数的第一次出现的索引和 每个数出现的次数 这两项对应着数  所以构成键值对用
    //map  或  unoeder_map
     int maxappercount = 0;//定义一个储存遍历时当前出现最多数出现次数的变量
    for(size_t i = 0; i < arr.size(); ++i){
        if(startindex.count(arr[i]) == 0){
            //arr[i]第一次出现   记录下第一次出现的索引。
            startindex[arr[i]] = i;
        }
        appercount[arr[i]]++;//每遍历到一个数字对其出现的次数加一
        if(appercount[arr[i]] == maxappercount){
            //如果遍历到的数字出现的个数等于已知的出现最多数的的出现个数 
            //说明 这时有两个数字出现了同样多次且这两个数字出现的次数比其他数字都多。
            length = (i - startindex[arr[i]] + 1 >  length) ? length :( i - startindex[arr[i]] + 1);
            //这里 刷新length为这二者中较小的可以包含所有该数字的长度
            //length = min(i - startindex[arr[i]] + 1, length);
        }
        else if(appercount[arr[i]] > maxappercount){
            //如果新遍历的数字出现的次数大于已知的最大次数 
            length = i - startindex[arr[i]] + 1;
            //length更新为出现次数最多次的数的“度”。
            maxappercount = appercount[arr[i]];
            //更新最多出现次数  继续向后查找。
        }
    }
    return length;
}

//给定数组，和整数K，计数数组中所有满足元素乘积小于K的连续子数组的个数。
//https://leetcode.com/problems/subarray-product-less-than-k/description/
int LessKSubArray(vector<size_t>& arr,int k)
{
    size_t prod = 1;
    size_t left = 0;
    size_t ret = 0;
    for(size_t i = 0; i < arr.size(); ++i){
        prod *= arr[i];
        while(prod > k){
            prod /= arr[left++];
        }
        ret++;//= i - left + 1;
    }
    return ret;
}

int main()
{
    int arr[] = {1,3,7,6,5,6,};
    vector<int> nums;
    for(size_t i = 0; i < sizeof(arr)/sizeof(int); ++i){
        nums.push_back(arr[i]);
    }
    int brr[] = {1,2,2,3,4,2,5};
    vector<int> v(brr, brr+sizeof(brr)/sizeof(int));
    cout<<pivotIndex(nums)<<endl;
    cout<<FindShortestSubArray(v)<<endl;
    size_t crr[] = {10,5,2,6};
    vector<size_t> v1(crr, crr+sizeof(crr)/sizeof(int));
    cout<<LessKSubArray(v1,100)<<endl;
    return 0; 
}
