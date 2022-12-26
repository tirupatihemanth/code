#include<bits/stdc++.h>
using namespace std;

/* LEETCODE CONTESTS DECEMBER */

/* 18/12/2022 WEEKLY CONTEST: 324 */

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


/* 24/12/2022 BIWEEKLY CONTEST: 94 */


// 26/12/2022 LC2511-Easy: Maximum enemy forts that can be captured
// O(n)xO(1)
int captureForts(vector<int>& forts) {
    
    int maxForts=0, prev=0;
    for(int i=0;i<forts.size();i++){
        if(forts[i]!=0){
            if(forts[i]==-forts[prev]){
                maxForts = max(i-prev-1, maxForts);
            }
            prev = i;
        }
    }
    return maxForts;
}


// 26/12/2022 LC2512-Medium: Reward Top K Students
// O(nlogn)xO(n)
vector<int> topStudents(vector<string>& positive_feedback, vector<string>& negative_feedback, vector<string>& report, vector<int>& student_id, int k) {
    unordered_set<string> posSet(positive_feedback.begin(), positive_feedback.end());
    unordered_set<string> negSet(negative_feedback.begin(), negative_feedback.end());
    vector<pair<int, int>> top(student_id.size());
    
    
    for(int i=0;i<report.size();i++){
        istringstream iss(report[i]);
        string word;
        int score=0;
        while(!iss.eof()){
            iss >> word;
            if(posSet.count(word)) score+=3;
            else if(negSet.count(word)) score-=1;
        }
        
        // To sort in decreasing order of score but in the increasing order of student_id
        top[i]={-score, student_id[i]};
    }
    
    partial_sort(top.begin(), top.begin()+k, top.end());
    
    vector<int> result(k);
    for(int i=0;i<k;i++){
        result[i] = top[i].second;
    }
    return result;

    //Alt
    /* vector<int> result;
    transform(top.begin(), top.begin()+k, back_inserter(result), [](auto &p){return p.second;});
    return result; */
}


// Binary Expansion for getting a^n in O(logn) time
int binpow(int a, int n, int m = 1e9+7){
    long long result = 1;
    long long count=a;
    count%=m;
    while(n>=1){
        if(n&1) result = (result*count)%m;
        n>>=1;
        count  = (count*count)%m;
    }

    return result;
}

// Modular Multiplicative Inverse by Fermat's little theorem
int modMulInv(int a, int m=1e9+7){
    return binpow(a, m-2, m);
}

// Factorial function
int fact(int n, int m=1e9+7){
    long long result = 1;
    for(int i=2;i<=n;i++){
        result = (result*i)%m;
    }
    return result;
}

// 26/12/2022 LC2514-Hard: Count Anagrams
// Basically unique permutations formula. But (A/B)modM != AmodM/BmodM;
// (A/B)modM = ( (AmodM) * (B^-1modM) ) modM. Find Modular Multiplicative Inverse of B mod M using Fermat's little theorem
// Cache factorial results in a 10,000 sized array first to prevent frequent O(n) calculations.
int countAnagrams(string s) {
    
    int m = 1e9+7;
    long long result = 1;
    stringstream ss(s);
    int freq[26];

    while(!ss.eof()){
        string word;
        ss >> word;
        fill(freq, freq+26, 0);
        for(char c:word){
            freq[c-'a']++;
        }

        long long denom = 1;
        for(int j=0;j<26;j++){
            if(freq[j]>1){
                denom = (denom * fact(freq[j]))%m;
            }
        }

        long long perm = fact(word.length());
        perm = (perm * modMulInv(denom))%m;
        result = (result*perm)%m;
    }

    return result;
}


/* 25/12/2022 WEEKLY CONTEST: 325 */


// 25/12/2022 LC2516-Medium: Take At least K of each character from left and right
// Classic two pointer but solve the complement of the problem.
// Find the largest subarray with atmost count-k of each character. The remaining to the 
// elements to the left & right of our subarray is the minimum #chars on left & right to have given counts..
// O(n)xO(1)
int takeCharacters(string s, int k) {
    int count[3]={}, curCount[3]={};
    for(char c:s){
        count[c-'a']++;
    }
    
    if(count[0]<k || count[1]<k || count[2]<k) return -1;
    count[0] -=k;
    count[1] -=k;
    count[2] -=k;
    
    int l=0, maxLength=0;
    for(int r=0;r<s.length();r++){
        int idx = s[r]-'a';
        curCount[idx]++;
        while(curCount[idx]>count[idx]){
            curCount[s[l]-'a']--;
            l++;
        }
        maxLength = max(maxLength, r-l+1);
    }

    return s.length()-maxLength;
}


// 25/12/2022 LC2515-Easy: Shortest distance to target string in circular array
// O(n)xO(1)
int closestTarget(vector<string>& words, string target, int startIndex) {
    int result = INT_MAX;
    for(int i=0;i<words.size();i++){
        if(words[i]==target){
            int diff = abs(startIndex-i);
            result = min(result, min(diff, (int)words.size()-diff));
        }
    }

    return result==INT_MAX?-1:result;
}


int count(vector<int> &price, int tastiness){
    int cnt=1, last=price[0];
    for(int i=1;i<price.size();i++){
        if(price[i]-last>=tastiness){
            last = price[i];
            cnt++;
        }
    }
    return cnt;
}

// 26/12/2022 LC2517-Medium: Maximum tastiness of candy basket.
// O(nlogn + nlogN) where N is maxVal-minVal of price values.
int maximumTastiness(vector<int>& price, int k) {
    sort(price.begin(), price.end());
    int lo=0; // Since when two elements are same in the given basket => lowest diff.
    int hi = price.back()-price.front()+1; // This is the maximum tastiness for a basket => when only two elements are present in a basket this is the max diff possible.


    // Now for k elements to be present in a basket what is the maximum possible tastiness. 
    // We do a binary search for all possible tastiness[0, hi) we search for max possible tastiness which can give k elements.
    // In while(lo < hi) BS we ensure that our value is in [lo, hi) range becaue hi value is not checked hence we added 1 in hi initialization. 
    // While doing BS iterations also hi value shouldn't be in our desired range. In below case when count(mid)<k then hi=mid. Because our answer will never be mid, it's <mid.
    // Basically we are doing upper_bound here.
    
    while(lo<hi){
        int mid = lo+(hi-lo)/2;
        if(count(price, mid)>=k) lo = mid+1;
        else hi = mid;
    }
    return lo-1;
}

int main(int argc, char const *argv[])
{

    cout << smallestValue(4);
    return 0;
}