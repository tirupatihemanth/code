#include <bits/stdc++.h>
using namespace std;

/* SLIDING WINDOW */
/* NEETCODE.IO */

/* 
Sliding window also uses two pointers. Can look at it multiple ways 
1. Where you accumulate a property on the l-pointer and consume new data from the r pointer.
2. Where you maintain a property invariant b/w the l & r pointers. Ex: longest substring, char replacement
 */


// 07/12/2022 LC121-Easy: Best time to buy and sell stock
// O(n) x O(1); Always has the smallest price we've seen so far on left pointer. It may not always yield
// biggest profit as highs after the lowest left might not be that large, but we'd max(profit) anyways.
int maxProfit(vector<int>& prices) {
    int l=0, r=1, profit=0;

    while(r<prices.size()){
        profit = max(profit, prices[r]-prices[l]);
        if(prices[r]<prices[l]) l = r;
        r++;
    }

    return profit;
}

// 07/12/2022 LC3-Medium: Longest substring without repeating characters
// Your window is always having the substring without repeating characters
// O(n) x O(n)
int lengthOfLongestSubstring(string s) {
    unordered_set<char> seen;
    int l=0, max_lls=0;
    for(int r=0; r<s.length(); r++){
        while(seen.count(s[r])){
            seen.erase(s[l]);
            l++;
        }
        seen.insert(s[r]);
        max_lls = max(max_lls, (int)seen.size());
    }
    return max_lls;
}

// 07/12/2022 LC424-Medium: Longest Repeating Character Replacement.
// Alternate solution to the below soln. More easy to understand.
// Whenever your total variable are limited like alphabets i.e 26 think in this way.
// O(26n)xO(1) soln
int characterReplacement_alt(string s, int k) {
    unordered_set<char> alphabet(s.begin(), s.end());
    int max_length = 0;
    for(char c:alphabet){
        int l=0, leave=k;
        for(int r=0;r<s.length();r++){
            if(s[r]!=c){
                if(leave>0) leave--;
                else{
                    while(s[l]==c)l++;
                    l++;                        
                }
            }
            max_length = max(max_length, r-l+1);
        }
    }
    return max_length;
}

// 07/12/2022 LC424-Medium: Longest Repeating Character Replacement.
// Two pointer invariant is windowsLength-mostFreq <= k i.e each window i.e substring is a valid window
// (i.e how many characters that needed to be converted into the mostFreq element in the window <= k)
// O(n)xO(1) solution. O(26n)xO(1) solution commented out.
int characterReplacement(string s, int k){
    unordered_map<char, int> freq;
    int l=0, max_length=0, max_freq=0;
    for(int r=0;r<s.length();r++){
        freq[s[r]]++;

        // unless r-l+1 increase anyway our max_length won't change so when we decrement freq if 
        // we simulatenously don't reduce if needed the maxfreq it won't cause any issues.
        max_freq = max(max_freq, freq[s[r]]);

        //O(26) operation
        //int max_freq = accumulate(freq.begin(), freq.end(), max_freq, [](int x, auto y){return max(x,y.second);});
        
        //'if' also works instead of while
        while((r-l+1)-max_freq>k){
            freq[s[l]]--;
            l++;
        }
        max_length = max(max_length, r-l+1);
    }

    return max_length;
}

// 07/12/2022 LC567-Medium: Permutation in a string
// O(n)xO(1) my soln. we insert and remove each element of the string s2 atmost once each so O(n)
// If we store using array then instead of mp2.clear() we have to reset all 26 values then O(26n)
bool checkInclusion_alt(string s1, string s2) {
    unordered_map<char, int> mp1, mp2;
    for(char c: s1){
        mp1[c]++;
    }

    int l=0;
    for(int r=0;r<s2.length();r++){
        if(!mp1.count(s2[r])){
            l=r+1;
            mp2.clear();
            continue;
        }
        if(mp2[s2[r]]==mp1[s2[r]]){
            while(s2[l]!=s2[r]){
                mp2[s2[l]]--;
                l++;
            }
            l++;
        }
        else mp2[s2[r]]++;
        if(r-l+1==s1.size()) return true;
    }
    return false;
}

// 07/12/2022 LC567-Medium: Permutation in String
// -------
// O(26n)xO(1) take s1 sized windows in s2 and compare their hashmaps
// and continue doing that as you slide window i.e l++ & r++ if matches == 26 return true.
// O(n)xO(1) eliminates comparing entire hashmaps of 26 alphabets for every windows by 
// --------
// keeping track of no. of matches for current window and upating no. of matches based on 
// including and excluding elements.
bool checkInclusion(string s1, string s2){
    if(s1.length()>s2.length()) return false;
    int mp1[26] = {0};
    int mp2[26] = {0};
    for(int i=0;i<s1.length();i++){
        mp1[s1[i]-'a']++;
        mp2[s2[i]-'a']++;
    }
    int matches = 0;
    for(int i=0;i<26;i++) matches+= mp1[i]==mp2[i];
    if(matches==26) return true;

    for(int r=s1.length(), l=0;r<s2.length();r++){
        if(mp2[s2[r]-'a']==mp1[s2[r]-'a']) matches--;
        else if(mp2[s2[r]-'a']+1==mp1[s2[r]-'a']) matches++;
        mp2[s2[r]-'a']++;

        if(mp2[s2[l]-'a']==mp1[s2[l]-'a']) matches--;
        else if(mp2[s2[l]-'a']-1==mp1[s2[l]-'a']) matches++;
        mp2[s2[l]-'a']--;
        l++;
        if(matches==26) return true;
    }

    return false;
}

int main(int argc, char const *argv[])
{
    // cout << lengthOfLongestSubstring("aabaab!bb")<<endl;

    cout << characterReplacement("AABABBA", 1)<<endl;
    return 0;
}
