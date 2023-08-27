#include "leetcode.h"
using namespace std;

/* Two Pointers */
/* NeetCode.io */

/* 
Remember two pointer method works only if array is sorted or some sort of order is maintained.
 */
/* 
Amazing intuition for how 2 pointer method works using a O(n^2) matrix and pruning showed by | & -;
x's are not counted b/o symmetry. 
The path followed by our pointer movements is give by 0 where the path length can be atmost O(n)
l, r represented in a matrix the horizontal & vertical positions in the matrix.
Imagine TwoSum sorted or maxArea problems in this. (1,6) -> (2,6) -> (2,5)->(2, 4)->(3,4)

  1 2 3 4 5 6
1 x ------- o
2 x x - o o o
3 x x x o | |
4 x x x x | |
5 x x x x x |
6 x x x x x x
src: https://leetcode.com/problems/container-with-most-water/solutions/6099/yet-another-way-to-see-what-happens-in-the-o-n-algorithm/ 
 */


// 05/12/2022 LC125-Easy: Valid Palindrome
// O(n) x O(1): using two pointers. O(n) space if creating new string by removing alphanumeric chars
// and then using reverse and checking equal.
// isalnum, isalpha, isdigit all returns 0 if not non-zero int if it is true.
bool isPalindrome(string s) {
    int i=0, j=s.length()-1;
    while(i<j){
        while(i<j && !isalnum(s[i])) i++;
        while(j>i && !isalnum(s[j])) j--;
        if(tolower(s[i])!=tolower(s[j])) return false; //tolower(c) unchanged c if c isn't alphabet
        i++; j--;
    }
    return true;
}


// 05/12/2022 LC167-Medium: Two Sum II - Input Array is sorted
// Two pointers is an awesome way to eliminate unnecessary calculations similar to binary search.
// O(n)xO(1) using two pointers.
vector<int> twoSum(vector<int>& numbers, int target) {
    int i=0, j=numbers.size()-1;
    while(i<j){
        int curTarget = numbers[i]+numbers[j];
        if(curTarget == target) return {i+1, j+1};
        else if(curTarget > target) j--;
        else i++;
    }
    return {};
}

// 06/12/2022 LC15-Medium: 3Sum
// O(n^2)xO(1) Assuming standard sort is O(1) memory
// Take each element as target and iterate over the rest using two-sum.
// To avoid duplicates sort and do two sum only on the consequent elements
// Writing naive solution first and see how optimized values are being evaluated helps us
// get idea for optimized solution.
vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> result;
    int n=nums.size();

    for(int k=0;k<n;k++){
        // if(nums[k]>0) break; to further optimize - no change in O()xO() though
        if(k>0 && nums[k]==nums[k-1])continue;
        int target = -nums[k];
        int i=k+1, j=n-1;
        while(i<j){
            if(nums[i]+nums[j]==target){
                result.push_back({nums[i], nums[j], nums[k]});
                i++;
                // Since there can be multiple vals say a, b such that a+b=target.
                while(i<j && nums[i]==nums[i-1])i++;
            }
            else if(nums[i]+nums[j]<target)i++;
            else j--;
        }
    }
    return result;
}

// 06/12/2022 LC11-Medium: Container with most water.
// You can get more area for lesser width as you move pointers only if min height of the
// elements pointed by l,r is higher. If you move the greater height pointer you are bound to get
// areas lesser than current area as width will be less but height is already limited by the l height.
int maxArea(vector<int>& height) {
    int l=0, r=height.size()-1;
    int result=0;
    while(l<r){
        int curArea = min(height[l], height[r])*(r-l);
        result = max(result, curArea);
        if(height[l]<height[r])l++;
        else r--;
    }
    return result;
}

int main(int argc, char const *argv[])
{
    vector<int> v = {-1,0,1,2,-1,-4,-2,-3,3,0,4};
    threeSum(v);
    return 0;
}
