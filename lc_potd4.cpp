#include<bits/stdc++.h>
using namespace std;


/* LEETCODE POTD MAY */


// 01/05/2023 LC1491-Easy: Avg Salary excluding Min & Max Salary
// O(n)xO(1)
double average(vector<int>& salary) {
    int min = *min_element(begin(salary), end(salary));
    int max = *max_element(begin(salary), end(salary));
    int sum = accumulate(begin(salary), end(salary), 0);
    return (sum-(min+max))/(salary.size()-2.0);
}


// 02/05/2023 LC1822-Easy: Sign of the Product of an Array
// O(n)xO(1)
int arraySign(vector<int>& nums) {
    int result=1;
    for(int &num:nums){
        if(num==0) return 0;
        else if(num < 0) {
            result*=-1;
        }
    }
    return result;
}


// 03/05/2023 LC2215-Easy: Find the Difference of Two Arrays
// O(n)xO(n)
vector<vector<int>> findDifference(vector<int>& nums1, vector<int>& nums2) {

    unordered_set<int> s1(nums1.begin(), nums1.end());
    unordered_set<int> s2(nums2.begin(), nums2.end());
    vector<vector<int>> result(2);

    copy_if(s1.begin(), s1.end(), back_inserter(result[0]), [&s2](int needle){ return !s2.count(needle);});

    copy_if(s2.begin(), s2.end(), back_inserter(result[1]), [&s1](int needle){ return !s1.count(needle);});
    

    // If you use sets instead of unordered sets then you can use set_difference algo
    // set_difference(begin(s1), end(s1), begin(s2), end(s2), back_inserter(result[0]));
    // set_difference(begin(s2), end(s2), begin(s1), end(s1), back_inserter(result[1]));

    return result;
}


// 04/05/2023 LC649-Medium: Dota2 Senate
// TODO: O(?)xO(n)
string predictPartyVictory(string senate) {
    queue<int> qR_Idx, qD_Idx;
    for(int i=0;i<senate.length();i++){
        if(senate[i]=='R')qR_Idx.push(i);
        else qD_Idx.push(i);
    }

    while(qR_Idx.size() && qD_Idx.size()){
        int R_idx = qR_Idx.front();qR_Idx.pop();
        int D_Idx = qD_Idx.front();qD_Idx.pop();
        R_idx < D_Idx?qR_Idx.push(R_idx+senate.length()):qD_Idx.push(D_Idx+senate.length());
    }

    return qR_Idx.empty()?"Dire":"Radiant";
}


// 05/05/2023 LC1456-Medium: Maximum Number of Vowels in a Substring of Given Length
// O(n)xO(1)
int maxVowels(string s, int k) {
    int count=0;
    int i=0;
    unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};

    for(;i<k;i++){
        if(vowels.count(s[i])) count++;
    }

    if(count == k) return count;
    int result = count;
    for(;i<s.length();i++){
        if(vowels.count(s[i])) count++;
        if(vowels.count(s[i-k])) count--;
        if(count==k) return count;
        result = max(result, count);
    }
    return result;
}


// 06/05/2023 LC1498-Medium: Number of Subsequences That Satisfy the Given Sum Condition
int numSubseq(vector<int>& nums, int target) {
    int M = 1e9+7;
    sort(nums.begin(), nums.end());
    int n = nums.size(), l=0, r=n-1;
    int result=0;
    vector<int> pows(n); pows[0]=1;
    for(int i=1;i<n;i++){
        pows[i] = (pows[i-1] * 2)%M;
    }
    while(l<=r){
        if(nums[l]+nums[r]>target) r--;
        else{
            result = (result + pows[r-l])%M;
            l++;
        }
    }
    return result;
}


// 08/05/2023 LC1572-Easy: Matrix Diagonal Sum
// O(n)xO(1)
int diagonalSum(vector<vector<int>>& mat) {
    int result=0, n=mat.size();
    for(int i=0;i<n;i++){
        result += mat[i][i];
        result += mat[i][n-i-1];
    }

    return n%2?result-mat[n/2][n/2]:result;
}


// 09/05/2023 LC54-Medium: Spiral Matrix
// O(nxn)xO(1). This method is useful for clockwise or anti-clockwise also. Just change dirs array order.
vector<int> spiralOrder(vector<vector<int>>& matrix) {
    array<int, 2> steps = {{(int)matrix[0].size(), (int)matrix.size()}};
    array<array<int, 2>, 4> dirs = {{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}};
    int i=0, j=-1, dir=0;
    vector<int> result;
    result.reserve(steps[0]*steps[1]);

    while(steps[dir%2]){
        for(int iter=0;iter<steps[dir%2];iter++){
            i+=dirs[dir][0];
            j+=dirs[dir][1];
            result.push_back(matrix[i][j]);
        }
        steps[!(dir%2)]--;
        dir = (dir+1)%4;
    }
    
    return result;
}
    

// 09/05/2023 LC54-Medium: Spiral Matrix
// O(nxn)xO(1). Basic method. See the above/below better version.
vector<int> spiralOrder_alt(vector<vector<int>>& matrix) {
    int num_y = matrix.size(), num_x = matrix[0].size();
    int i=0, j=-1, counter;
    vector<int> result;
    result.reserve(num_x*num_y);

    while(num_x>0 && num_y>0){
        
        // right
        counter=0;
        while(counter<num_x){
            result.push_back(matrix[i][++j]);
            counter++;
        }
        num_y--;
        if(!num_y) break;

        // down
        counter = 0;
        while(counter<num_y){
            result.push_back(matrix[++i][j]);
            counter++;
        }
        num_x--;
        if(!num_x) break;
        
        // left
        counter = 0;
        while(counter<num_x){
            result.push_back(matrix[i][--j]);
            counter++;
        }
        num_y--;
        if(!num_y) break;

        // up
        counter=0;
        while(counter<num_y){
            result.push_back(matrix[--i][j]);
            counter++;
        }
        num_x--;
        if(!num_x) break;
    }

    return result;
}


// 10/05/2023 LC59-Medium: Spiral Matrix II
// O(nxn)xO(nxn). Great way to solve spiral matrix problems.
vector<vector<int>> generateMatrix(int n) {
    vector<vector<int>> matrix(n, vector<int>(n));
    array<array<int, 2>, 4> dirs = {{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}};
    array<int, 2> steps = {n, n};
    int i=0, j=-1, dir=0, num=0;
    while(steps[dir%2]){
        for(int iter=0;iter<steps[dir%2];iter++){
            i+=dirs[dir][0];
            j+=dirs[dir][1];
            num++;
            matrix[i][j]= num;
        }
        steps[!(dir%2)]--;
        dir = (dir+1)%4;
    }
    return matrix;
}

int main(int argc, char const *argv[])
{

    return 0;
}