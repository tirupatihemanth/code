#include "leetcode.h"
using namespace std;



/* 1D Dynamic Programming */
/* NEETCODE.IO */


int climbStairs(int n) {
    if(!n) return n;
    if(n==1) return 1;
    if(n==2) return 2;
    int prev1 = 2, prev2=1, result;
    for(int i=3;i<=n;i++){
        result = prev1+prev2;
        prev2 = prev1;
        prev1 = result;
    }
    return result;
}


// Alt: just use prev1, prev2 instead of a whole array memo.
int minCostClimbingStairs(vector<int>& cost) {
    int n = cost.size();
    int result[n+1];
    fill(result, result+n+1, 0);
    for(int i=2;i<=n;i++){
        result[i] = min(result[i-1]+cost[i-1], result[i-2]+cost[i-2]);
    }
    return result[n];
}


int rob(vector<int>& nums) {
    int n = nums.size();
    vector<int> loot(n+1);
    int prev1=nums[0], prev2=0, result=prev1;
    
    for(int i=1;i<n;i++){
        result = max(prev1, prev2+nums[i]);
        prev2=prev1; 
        prev1=result;
    }
    return result;
}


int rob2(vector<int>& nums) {

    // Rob house 0. Hence can rob from 2..n-2
    int prev2 = nums[0], prev1 = nums[0], n=nums.size();
    int result1=nums[0];
    for(int i=2;i<n-1;i++){
        result1 = max(prev1, prev2+nums[i]);
        prev2 = prev1;
        prev1 = result1;
    }

    // Do not rob house 0. Hence can rob from 1..n-1
    prev1=prev2=0;
    int result2=0;
    for(int i=1;i<n;i++){
        result2 = max(prev1, prev2+nums[i]);
        prev2=prev1;
        prev1=result2;
    }
    return max(result1, result2);
}



// Alt: Proper DP Approach - https://leetcode.com/problems/longest-palindromic-substring/solutions/151144/bottom-up-dp-two-pointers/
string longestPalindrome(string s) {
        int n = s.length();
        string result;

        // Odd Palindromes
        for(int i=0; i<n;i++){
            int l=i, r=i;
            while(l>=0 && r<n && s[l]==s[r]){
                if(r-l+1 > result.length()){
                    result = s.substr(l, r-l+1);
                }
                l--;
                r++;
            }

            // Even Palindromes
            l=i, r=i+1;
            while(l>=0 && r<n && s[l]==s[r]){
                if(r-l+1 > result.length()){
                    result = s.substr(l, r-l+1);
                }
                l--;
                r++;
            }
        }

        return result;
}


int countSubstrings(string s) {
    int count=0;
    int n = s.length();
    for(int i=0;i<n;i++){
        int l=i, r=i;
        while(l>=0 && r<n && s[l]==s[r]){
            count++;
            l--; r++;
        }

        l=i, r=i+1;
        while(l>=0 && r<n && s[l]==s[r]){
            count++;
            l--; r++;
        }
    }
    return count;
}


int numDecodings(string s) {
    int n = s.length();
    if(s[0]=='0' || !n) return 0;
    if(n==1) return 1;
    vector<int> ways(n);
    ways[0] = 1;
    ways[1] = (s[1]!='0') + (stoi(s.substr(0,2))<27);
    for(int i=2;i<n;i++){
        if(s[i]!='0') ways[i] = ways[i-1];
        if(s[i-1]!='0' && stoi(s.substr(i-1,2))<27){
            ways[i] += ways[i-2];
        }
    }

    return ways.back();
}


// [1, 3, 4, 5] and Amount = 7. Greedy doesn't work.
int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount+1, amount+1);
    dp[0]=0;

    for(int i=1;i<=amount;i++){
        for(int coinVal:coins){
            if(coinVal<=i){
                dp[i] = min(dp[i], 1+dp[i-coinVal]);
            }
        }
    }

    return dp[amount]==amount+1?-1:dp[amount];
}


// Alt: optimize with just curMin, curMax values
// Max Product of sub array ending at i.
int maxProduct(vector<int>& nums) {
    vector<int> dp1(nums), dp2(nums);
    int result = nums[0];
    for(int i=1;i<nums.size();i++){
        dp1[i] = max({dp1[i-1]*nums[i], nums[i], dp2[i-1]*nums[i]});
        dp2[i] = min({dp1[i-1]*nums[i], nums[i], dp2[i-1]*nums[i]});
        result = max(result, dp1[i]);
    }

    return result;
}


bool bfs(string &s, int idx, vector<string> &wordDict, vector<int>& dp){
    if(idx==s.length()) return true;
    if(dp[idx]!=0) return dp[idx]==1;

    for(auto &word:wordDict){
        if(s.find(word,idx)==idx && bfs(s, idx+word.length(), wordDict, dp)){
            return dp[idx]=1;
        }
    }

    dp[idx]=-1;
    return false;
}

// Alt: instead of bfs do a bottom up dp starting from right end.
bool wordBreak(string s, vector<string>& wordDict) {
    vector<int> dp(s.length());
    return bfs(s, 0, wordDict, dp);
}


// Length of LIS ending at index i. 
// Alt: You can iterate from RHS of nums and checking LIS starting from index i.
// Alt: O(nlogn) given below in comment copied from LC.
// O(n^2)xO(n)
int lengthOfLIS(vector<int>& nums) {
    vector<int> dp(nums.size(), 1);

    int result=1;
    for(int i=1;i<nums.size();i++){
        for(int j=i-1;j>=0;j--){
            if(nums[j]<nums[i]){
                dp[i] = max(dp[i], dp[j]+1);
                result = max(result, dp[i]);
            }
        }
    }

    return result;
}

/*

[1,2,7,8,3,4,5,9,0]
1 -> [1]
2 -> [1,2]
7 -> [1,2,7]
8 -> [1,2,7,8]
3 -> [1,2,3,8]  // we replaced 7 with 3, since for the longest sequence we need only the last number and 1,2,3 is our new shorter sequence
4 -> [1,2,3,4] // we replaced 8 with 4, since the max len is the same but 4 has more chances for longer sequence
5 -> [1,2,3,4,5]
9 -> [1,2,3,4,5,9]
0 -> [0,2,3,4,5,9] // we replaced 1 with 0, so that it can become a new sequence

length of result array is the length of LIS but the values could be wrong.
int lengthOfLIS(vector<int>& nums) {
    vector<int> res;
    for(int i=0; i<nums.size(); i++) {
        auto it = std::lower_bound(res.begin(), res.end(), nums[i]);
        if(it==res.end()) res.push_back(nums[i]);
        else *it = nums[i];
    }
    return res.size();
}
*/

int main(int argc, char const *argv[])
{
    
    vector<int> coins = {1, 2, 5};
    cout << coinChange(coins, 11) << endl;
     return 0;
}