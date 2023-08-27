#include "leetcode.h"
using namespace std;


/* GREEDY */
/* NEETCODE.IO */


int maxSubArray(vector<int>& nums) {
    if(nums.empty()) return 0;
    int baggage=nums[0];
    int result=nums[0];
    for(int i=1;i<nums.size();i++){
        baggage = baggage>0?baggage+nums[i]:nums[i];
        result = max(result, baggage);
    }
    return result;
}


// Alt: DP sol is O(n^2). Check LC Submissions.
// O(n)xO(1)
bool canJump(vector<int>& nums) {
    int fuel = 1;
    for(int i=0;i<nums.size();i++){
        fuel = max(nums[i], fuel-1);
        if(!fuel && i!=nums.size()-1) return false;
    }
    return true;
}


// Alt: DP Sol is O(n^2). Check LC Submissions
// O(n)xO(1)
int jump(vector<int>& nums) {
    int l=0, r=0, n=nums.size();
    int result=0;
    while(r<n-1){
        int new_r=r;
        for(int i=l;i<=r && r<n;i++){
            new_r = max(new_r, i+nums[i]);
        }
        l = r+1;
        r = new_r;
        result++;
    }
    return result;
}


int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int n = gas.size();

    int result=0, total=0, sum=0;
    for(int i=0;i<n;i++){
        total += (gas[i]-cost[i]);
        sum += (gas[i]-cost[i]);
        if(total<0){
            result = i+1;
            total=0;
        }
    }

    if(sum<0) return -1;
    return result;
}


int main(int argc, char const *argv[])
{
    
     return 0;
}