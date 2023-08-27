#include "leetcode.h"
using namespace std;


/* 2D DYNAMIC PROGRAMMING */
/* NEETCODE.IO */


int uniquePaths(int m, int n) {
    int result=0;
    vector<vector<int>> dp(m, vector<int>(n));
    for(int i=0;i<m;i++) dp[i][0]=1;
    for(int j=0;j<n;j++) dp[0][j]=1;
    for(int i=1;i<m;i++){
        for(int j=1;j<n;j++){
            dp[i][j] = dp[i-1][j]+dp[i][j-1];
        }
    }

    return dp[m-1][n-1];   
}


int longestCommonSubsequence(string text1, string text2) {
    int m = text1.size(), n = text2.size();
    vector<vector<int>> dp(m+1, vector<int>(n+1));
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            dp[i][j] = max({
                dp[i-1][j-1] + (text1[i-1]==text2[j-1]),
                dp[i][j-1],
                dp[i-1][j]
            });
        }
    }
    return dp[m][n];
}


int main(int argc, char const *argv[])
{
    
     return 0;
}