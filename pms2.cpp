#include <bits/stdc++.h>
using namespace std;

/* RECURSION */
/* GFG */

// 14/12/2022 
// Backtracking approach: Gives duplicates if repeated chars are present. What are we actually doing?
// For each char fixed in first pos we find all permutations of remaining n-1 chars.
// O(n!xn)xO(n): O(n) for printing/storing result permutaiton string. O(n) stack space.
void stringPermutations(string &s, int start){
    if(start == s.length()-1){
        cout << s << endl;
        return;
    }

    for(int i=start; i<s.length();i++){
        swap(s[start], s[i]);
        stringPermutations(s, start+1);
        
        //backtrack
        swap(s[start], s[i]);
    }
}

// 14/12/2022 
// Backtracking approach: Gives only unique permutations.
// NOTE: !! Expects sorted string !!
// O(n!xn)xO(n): O(n) for printing/storing result permutaiton string. O(n) stack space.
// TODO: Wrong. Modify this.
int count=0;
void stringPermutations_dist(string &s, int start){
    if(start == s.length()-1){
        cout << s << endl;
        ::count++;
        return;
    }

    for(int i=start; i<s.length();i++){
        // sorted string expected.
        if(i>start && s[i-1]==s[i]) continue;
        if(i>start && s[start]==s[i]) continue;

        swap(s[start], s[i]);
        stringPermutations_dist(s, start+1);
        
        //backtrack
        swap(s[start], s[i]);
    }
}

// 14/12/2022 
// STL approach: Gives only unique permutations
// O(n!xn) x O(1): since O(n) to compute next_permutation() and there are O(n!) permutations
void stringPermutations(string s){
    sort(s.begin(), s.end());
    do{
        cout << s<<endl;
    }while(next_permutation(s.begin(), s.end()));
}

// 14/12/2022 Not distinct
// backtracking: recursion whether each element is included or not.
// O(nx2^n)xO(n) stack space. 2^n subsets each printing/storing/building is O(n).
void powerset(string &s, int idx, string &cur){

    if(idx == s.length()){
        cout << cur << endl;
        return;
    }

    powerset(s, idx+1, cur);

    cur.push_back(s[idx]);
    powerset(s, idx+1, cur);
    cur.pop_back();

}

// 14/12/2022 Not distinct
// backtracking: fix each element and print all subsequent subsets having this as prefix.
// Same complexity but lesser operations than each element yes/no approach (draw tree). Since in yes/no
// for each element method you collect all subsets at leaves i.e at depth O(n) but here you go there only
// for subsets of length n
// O(nx2^n)xO(n). Better than previous powerset impl.
void powerset_alt(string &s, int idx, string &cur){
    // Must pass "" as cur to start with.
    cout << cur << endl;

    // if idx == s.length() return; is not needed.
    // Since automatically for loop won't be executed
    for(int i=idx;i<s.length();i++){
        cur.push_back(s[i]);
        powerset_alt(s, i+1, cur);
        cur.pop_back();
    }
}

// 13/12/2022 Not distinct
// O(n*2^n)xO(1). Bit manipulation 
void powerset_iter(string &s){
    unsigned int pset_size = 1U << s.size();
    for(unsigned int i=0;i<pset_size;i++){
        // Once cur_set become zero no more elements of set to be considered for this subset so inner for loop ends.
        for(unsigned int cur_set = i, j=0; cur_set; cur_set>>=1, j++){
            if(cur_set & 1) cout << s[j];
        }
        cout << endl; // first time nothing printed as inner for loop is not executed i.e empty subset.
    }
}

// TODO:
void powerset_dist(string &s){

}

int main(int argc, char const *argv[])
{
    string s1 = "aabbccd"; 
    pair<int, int> p = {1,2};

    // sort(s1.begin(), s1.end());
    stringPermutations_dist(s1, 0);
    cout << ::count<<endl;
    string s;
    // powerset(s1, 0, s);
    // powerset_alt(s1, 0, s);
    // powerset_iter(s1);
    return 0;
}
