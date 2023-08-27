#include "leetcode.h"
using namespace std;

/* BINARY SEARCH */
/* NEETCODE.IO */

// 15/12/2022 LC704-Easy: Binary Search
// O(logn)xO(1). Alt: Recursive impl will take O(logn) space also.
int binarySearch(vector<int>& nums, int target){
    int start = 0, end = nums.size()-1;
    while(start<=end){
        int mid = start+(end-start)/2;

        if(nums[mid]==target) 
            return mid;
        else if(nums[mid]>target) 
            end = mid-1;
        else 
            start = mid+1;
    }
    return -1;
}


// 15/12/2022 LC74-Medium: Search a 2D Matrix
// O(logmn)xO(1) == O(logm) + O(logn) x O(1). Alt: BS to a row first. Then BS within a row.
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    if(!matrix.size()) return false;
    int m = matrix.size(), n = matrix[0].size();
    int start = 0, end = m*n-1;

    while(start<=end){
        int mid = start + (end-start)/2;
        if(matrix[mid/n][mid%n] == target) return true;
        else if(matrix[mid/n][mid%n] > target) end = mid-1;
        else start = mid+1;
    }

    return false;
}


// 15/12/2022 LC875-Medium: Koko Eating Bananas
// O(n*logm) where n = size of piles vector. m is max element in piles.
// Both start & end will eventually converge to the smallest eating speed such that cur_hours still < limit h.
int minEatingSpeed(vector<int>& piles, int h) {
    int start = 1;
    int end = *max_element(piles.begin(), piles.end());

    while(start<end){
        int mid = start + (end-start)/2;
        long long cur_hours = 0LL;
        for(int x:piles) cur_hours += ceil(x/double(mid)); // If you use float() it will overflow

        if(cur_hours<=h) end = mid;
        else start = mid+1;
    }

    return end;
}


// 15/12/2022 LC33-Medium: Search in rotated sorted array.
// Alt: find min in the rotated array i.e the pivot in O(logn) then BS two sorted arrays to the left/right
// O(logn)xO(1)
int searchRotated(vector<int>& nums, int target) {
    int n = nums.size(), start = 0, end = n -1;

    while(start<=end){
        int mid = start + (end-start)/2;
        if(nums[mid]==target) return mid;
        // If you are present in left sorted array.
        else if(nums[mid]>nums[n-1]){
            if(nums[mid] < target || target <= nums[n-1])
                start = mid+1;
            else 
                end = mid-1;
        }
        // If you are present in right sorted array
        else{
            if(nums[mid]>target || target > nums[n-1]) 
                end = mid-1;
            else 
                start = mid + 1;
        }
    }

    return -1;
}

// 15/12/2022 LC153-Medium: Find minimum in rotated sorted array
// Alt: if nums[left] < nums[right] ret left; if nums[mid]>nums[n-1] i.e we are in first half 
// then start = mid+1. else we are in second half which has the min so end = mid; => start < end
// eventually converges to our value or start = mid+1 makes next start our mid then first condition.
// O(logn)xO(1). 
int minRotated(vector<int>& nums) {
    int start=0, end = nums.size()-1;

    // We shrink start & end w/o discarding min value i.e our value stays in [start, end];
    while(start < end){
        int mid = start + (end-start)/2;
        // pivot must be on the right since the values must've wrapped around & became smaller.
        // mid+1 because we know mid is not min b/o it's > at least 1 elem num[end]. So skip mid.
        if(nums[mid]>nums[end]) start = mid+1;
        // current value might be the pivot or it might be to the left. Can't be right b/o no wrap around.
        else end = mid;
    }

    // breaks at start==end.
    return nums[end];
}


// 17/12/2022 LC981-Medium: Time based key-value pairs
// O(1)xO(1) for set. O(logn)xO(1) for get.
class TimeMap {
    
    unordered_map<string, vector<pair<int, string>>> timeMap;
public:
    TimeMap() {
        
    }
    
    void set(string key, string value, int timestamp) {
        timeMap[key].emplace_back(timestamp, value);
    }
    
    string get(string key, int timestamp) {
        auto it = timeMap.find(key);
        if(it==timeMap.end()) return "";
        auto &v = it->second;

        // Using default upper_bound -> key can be of diff type than v items
        
        // auto it_v = upper_bound(v.begin(), v.end(), timestamp, [](int timestamp, pair<int, string> &y){ return timestamp < y.first;});
        // if(it_v == v.begin()) return "";
        // else return prev(it_v)->second;

        int start = 0, end = v.size()-1;
        string result;
        while(start<=end){
            int mid = start + (end-start)/2;
            if(v[mid].first==timestamp) return v[mid].second;
            else if(v[mid].first < timestamp){
                result = v[mid].second;
                start = mid+1;
            }
            else end = mid-1;
        }

        return result;
        
    }
};


int main(int argc, char const *argv[])
{
    vector<int> v = {805306368,805306368,805306368};
    cout << minEatingSpeed(v, 1000000000);
    return 0;
}