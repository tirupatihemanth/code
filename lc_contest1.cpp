#include<bits/stdc++.h>
using namespace std;

/* LEETCODE CONTESTS DECEMBER */

// 18/12/2022 LC2506-Easy: Count Pairs Of Similar Strings
// A string is similar if it has same set of chars.
// O(nl)xO(nl). n-> # of strings. l-> avg length of each string.
int similarPairs(vector<string>& words) {
    unordered_map<string, int> ump;
    
    for(auto &s:words){
        bool freq[26] = {};
        for(char c:s){
            freq[c-'a']=true;
        }
        string key;
        for(int i=0;i<26;i++){
            if(freq[i]) key.push_back('a'+i);
        }
        ump[key]++;
    }
    
    int result = 0;
    for(auto &p:ump){
        if(p.second > 1){
            result += (p.second)*(p.second-1)/2;
        }
    }
    return result;
}


// 18/12/2022 LC2507-Medium: Smallest value after replacing with sum of prime factors
// If outer loop runs k times then O(kxsqrt(n));
int smallestValue(int n){
    int result=n;
    // say this loop runs k times.
    do{
        n = result;
        int cur_num=result;

        // Get sum of all prime factors. O(sqrt(n))
        result=0;
        for(int i=2;i*i<=cur_num;i++){
            while(cur_num%i==0){
                result+=i;
                cur_num/=i;
            }
        }
        if(cur_num>1) result+=cur_num;
    } while(n!=result);
    // n==result happens for prime n i.e n doesn't reduce. (Except when n==4)
    return n;
}


// 18/12/2022 LC2509-Hard: Cycle length queries in tree.
// Alt: You find the path in vectors and then iterate over these logn vectors O(logn)xO(logn)
// O(logn)xO(1) for each query.
vector<int> cycleLengthQueries(int n, vector<vector<int>>& queries) {
    vector<int> result(queries.size(), 1);
    for(int i=0;i<queries.size();i++){
        int cycleLength=0;
        while(queries[i][0]!=queries[i][1]){
            if(queries[i][0]>queries[i][1]) 
                queries[i][0]/=2;
            else queries[i][1]/=2;
            result[i]++;
        }
    }
    return result;
}


int main(int argc, char const *argv[])
{

    cout << smallestValue(4);
    return 0;
}