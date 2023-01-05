#include<bits/stdc++.h>
using namespace std;

/* LEETCODE POTD JANUARY */


// 01/01/2023 LC290-Easy: Word Pattern
// O(n)xO(n) where n is length of pattern
bool wordPattern(string pattern, string s) {
    
    istringstream iss(s);

    unordered_map<string, char> ump;
    unordered_set<char> st;

    int i=0;
    for(string word;iss>>word;i++){
        if(i==pattern.length()) return false;
        if(ump.count(word)){
            if(ump[word]!=pattern[i]) return false;
        }
        else if(st.count(pattern[i])) return false;
        else {
            ump[word] = pattern[i];
            st.emplace(pattern[i]);
        }
    }

    return i==pattern.length();
}


// 02/01/2023 LC520-Easy: Detect Capital
// O(n)xO(1)
bool detectCapitalUse(string word) {
    if(word.length()==1) return true;

    if(islower(word[0]) || islower(word[1])){
        return all_of(word.begin()+1, word.end(), [](char c)->bool{return islower(c);});
    }
    return all_of(word.begin()+2, word.end(), [](char c)->bool{return isupper(c);});
}


// 03/01/2023 LC944-Easy: Delete columns to make sorted.
// O(nl)xO(1) where n is #columns & l is string length.
int minDeletionSize(vector<string>& strs) {
    int l = strs[0].length();
    int ans=0;
    for(int j=0;j<l;j++){
        for(int i=1;i<strs.size();i++){
            if(strs[i][j]<strs[i-1][j]){
                ans++;
                break;
            }        
        }
    }
    return ans;
}


// 04/01/2023 LC2244-Medium: Minimum rounds to complete all tasks
// O(n)xO(n)
int minimumRounds(vector<int>& tasks) {
    unordered_map<int, int> ump;
    for(int d:tasks) ump[d]++;

    int ans=0;
    for(auto &[_, count]:ump){
        if(count==1) return -1;
        else ans+=(count+2)/3; 
        // count = 3k we have k rounds.
        // count = 3k+1 we have 3(k-1)+2+2 => k+1 rounds
        // count = 3k+2 we have 3k + 2 => k+1 rounds
    }
    return ans;
}


// 05/01/2023 LC452-Minimum Number of Arrows to Burst Balloons
// Greedy Approach.
// Consider [6-9], [7,8] [9-11]. Shoting arrow at 9 would've shot 1st also. But our algo doesn't do that. But it's okay 
// as it is definitely taken care of by an arrow at 7 which anyway we have to fire to get [7,8].
// Alt: Sort asc by ending position. And then iterate from the beginning.
// O(nlogn)xO(1). (Assuming sort is O(1) space which isn't)
int findMinArrowShots(vector<vector<int>>& points) {
    // Sort asc by beginning position
    sort(points.begin(), points.end());

    int ans=1, min=points.back()[0];
    for(int i=points.size()-2;i>=0;i--){
        if(points[i][1]<min){
            ans++;
            min = points[i][0];
        }
    }
    return ans;
}

int main(int argc, char const *argv[])
{

    return 0;
}