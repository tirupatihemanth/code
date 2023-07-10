#include<bits/stdc++.h>
using namespace std;


/* LEETCODE POTD MARCH */


void merge(vector<int> &nums, int left, int mid){
    
    int end = min((int)nums.size(), mid + (mid-left));
    int temp[end-left], idx=0;
    int start = left, right = mid;

    while(start<mid && right<end){
        if(nums[start]<=nums[right]){
            temp[idx++]=nums[start++];
        }
        else{
            temp[idx++]=nums[right++];
        }
    }

    while(start<mid) temp[idx++]=nums[start++];
    while(right<end) temp[idx++]=nums[right++];

    copy(temp, temp+(end-left), nums.begin()+left);
}


// 01/03/2023 LC912-Medium: Sort an Array
// O(nlogn) x O(logn) 
vector<int> sortArray(vector<int>& nums) {
    
    int step = 1;
    while(step < nums.size()){
        int left=0;
        for(int right = left+step; right < nums.size(); left+=2*step, right=left+step){
            merge(nums, left, right);
        }
        step<<=1;
    }
    return nums;
}


// 20/03/2023 LC605-Easy: Can Place Flowers
// O(n)xO(1)
bool canPlaceFlowers(vector<int>& flowerbed, int n) {
    int ans=0;

    for(int i=0;i<flowerbed.size() && ans< n;++i){
        if(flowerbed[i]) continue;
        int left = i==0? 0:flowerbed[i-1];
        int right = i==flowerbed.size()-1? 0:flowerbed[i+1];
        if(!(left || right)){
            flowerbed[i] = 1;
            ans++;
        }
    }

    return ans == n;
}


int main(int argc, char const *argv[])
{

    vector<int> nums = {5,2,3,1, 5,2,3,1, 5,2,3,1, 5,2,3,1, 5,2,3,1, 5,1,1,2,0,0, 5,1,1,2,0,0, 5,1,1,2,0,0};
    sortArray(nums);
    return 0;
}