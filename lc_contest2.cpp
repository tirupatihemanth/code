#include<bits/stdc++.h>
using namespace std;

/* LEETCODE CONTESTS JANUARY */

/* 01/01/2023 WEEKLY CONTEST: 326 */

// 01/01/2023 LC2520-Easy: Count the digits that divide a number
// O(d)xO(1) where d is number of digits in num
int countDigits(int num) {
    int cur = num;
    int result=0;
    while(cur){
        int digit = cur%10;
        if(num%digit==0) result++;
        cur = cur/10;
    }
    return result;
}


// 01/01/2023 LC2521-Distinct Prime Factors of product of array
// O(n*sqrt(n)). O(sqrt(n)) to get prime factors of each number
int distinctPrimeFactors(vector<int>& nums) {
    unordered_set<int> pf;
    for(int num:nums){
        for(int i=2;i*i<=num;i++){
            if(num%i==0) pf.emplace(i);
            while(num%i==0) num/=i;
        }
        
        if(num>1) pf.emplace(num);
    }
    
    return pf.size();
}


// 01/01/2023 LC2523-Medium: Closest Prime numbers in range
// O(nloglogn)xO(n) for sieve where n=right..
vector<int> closestPrimes(int left, int right) {
    
    // Sieve of eratosthenes
    bool isprime[right+1];
    fill(isprime, isprime+right+1, true);
    isprime[0]=isprime[1]=false;
    
    for(int i=2;i<=right;i++){
        if(!isprime[i]) continue;
        for(long long j=1LL*i*i;j<=right;j+=i){
            isprime[j] = false;
        }
    }

    int l=-1, r=-1, prev=-1;
    for(int i=left; i<=right; i++){
        if(!isprime[i]) continue;
        if(l==-1) l = i;
        else if(r==-1){
            r = i;
        }
        else if(i-prev < r-l){
            l=prev;
            r=i;
        }
        prev = i;
    }

    if(r==-1) return {-1, -1};
    else return {l, r};
}


// 01/01/2023 LC2522-Medium: Partition string into substrings with values at most K
// Greedy approach works.
// O(L)xO(1) where L is length of the string. 
int minimumPartition(string s, int k) {
    int result=0;
    long long num=0;
    for(char c:s){
        int digit = c-'0';
        num = num*10+digit;
        if(num>k){
            if(digit>k) return -1;
            num = digit;
            result++;
        }
    }
    // last partition
    return ++result;
}


int main(int argc, char const *argv[])
{

    return 0;
}