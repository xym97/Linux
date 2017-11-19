#include<iostream>
#include<vector>
#include<map>
//#include<unordered_map>
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
    if(arr.size() < 2)
       return arr.size();
    int length = arr.size();
    map<int,int> startindex, appercount;
    int maxappercount = 0;
    for(size_t i = 0; i < arr.size(); ++i){
        if(startindex.count(arr[i]) == 0){
            startindex[arr[i]] = i;
        }
        appercount[arr[i]]++;
        if(appercount[arr[i]] == maxappercount){
            length = (i - startindex[arr[i]] + 1 >  length) ? length :( i - startindex[arr[i]] + 1);
            //length = min(i - startindex[arr[i]] + 1, length);
        }
        else if(appercount[arr[i]] > maxappercount){
            length = i - startindex[arr[i]] + 1;
            maxappercount = appercount[arr[i]];
        }
    }
    return length;
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
    return 0; 
}

