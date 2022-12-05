#include <bits/stdc++.h>
#include "leetcode.h"

using namespace std;

// Leetcode POTD December


// 02/12/2022 LC1657-Medium
// O(n) x O(1) n is length of string.
bool closeStrings(string word1, string word2) {
    if(word1.length()!=word2.length()) return false;
    int arr1[26] = {0};
    int arr2[26] = {0};
    for(int i=0;i<word1.length();i++){
        arr1[word1[i]-'a']++;
        arr2[word2[i]-'a']++;
    }
    for(int i=0;i<26;i++){
        if(!arr1[i]&&arr2[i] || arr1[i]&&!arr2[i]){
            return false;
        }
    }
    sort(arr1, arr1+26, greater<int>());
    sort(arr2, arr2+26, greater<int>());

    for(int i=0;i<26;i++){
        if(arr1[i]!=arr2[i]) return false;
    }
    return true;
}

//03/12/2022 LC451: Sort Characters by frequency in desc
// Naive: O(nlogn)xO(1) => sort string based on freq. But if you want all chars of same freq to come
// together then comparator must be ret arr[c1]>arr[c2] && (arr[c1]==arr[c2] && c1<c2)
// O(n)xO(1) Uses multimap. where n = len(s)
string frequencySort(string s) {
    int arr[256] = {0};
    for(char c:s) arr[c]++;
    multimap<int, char, greater<int>> mmp;
    for(int i=0;i<256;i++) if(arr[i]!=0) mmp.insert({arr[i], i});
    int i=0;
    for(auto &x:mmp){
        int freq = x.first;
        while(freq--) s[i++]=x.second;
    }
    return s;
}


// 04/12/2022 LC2256-Medium: Minimum Average Difference
int minimumAverageDifference(vector<int>& v) {
    if(!v.size()) return -1;
    long long totalSum = 0, curSum = 0;
    totalSum = accumulate(v.begin(), v.end(), totalSum);
    int minAvgDiff = numeric_limits<int>::max(), minIdx=0, curAvgDiff, n=v.size();
    for(int i=0;i<v.size()-1;i++){
        curSum += v[i];
        curAvgDiff = abs(curSum/(i+1)-(totalSum-curSum)/(n-i-1));
        if(minAvgDiff>curAvgDiff){
            minAvgDiff = curAvgDiff;
            minIdx = i;
        }
    }

    if(totalSum/n<minAvgDiff) return n-1;
    return minIdx;
}


int main(int argc, char const *argv[])
{
    //cout << closeStrings("cabbba", "abbccc")<<endl;   
    
    vector<int> v = {1,2,3};

    // cout << minimumAverageDifference(v)<<endl;
    return 0;
}
