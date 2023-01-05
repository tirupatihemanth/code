#include<bits/stdc++.h>
using namespace std;


/* BACKTRACKING */
/* NEETCODE.IO */
/* 
    1. In backtracking think of decisions you have to make at each step starting from '.' i.e root node.
 */



void dfs_subsets_alt(vector<int>& nums, int cur, vector<int> &subset, vector<vector<int>> &result){
    result.push_back(subset);
    for(int i=cur;i<nums.size();i++){
        subset.push_back(nums[i]);
        dfs_subsets_alt(nums, i+1, subset, result);
        subset.pop_back();
    }
}


// DEFUALT
void dfs_subsets(vector<int>& nums, int cur, vector<int> &subset, vector<vector<int>> &result){
    if(cur == nums.size()){
        result.push_back(subset);
        return;
    }
    dfs_subsets(nums, cur+1, subset, result);
    subset.push_back(nums[cur]);
    dfs_subsets(nums, cur+1, subset, result);
    subset.pop_back();
}

// 04/01/2023 LC78-Medium: Subsets
// Nums are distinct
// Alt: dfs_subsets_alt => you don't collect subsets at leaves but collect them as you go. Further
// You flatten from binary tree to n-ary tree. 
// O(n*2^n)xO(n). To build each subset we take O(n) and there are O(2^n) subsets. Recursion stack is O(n).
vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> result;
    result.reserve(1U<<nums.size());
    
    vector<int> subset;
    subset.reserve(nums.size());

    dfs_subsets(nums, 0, subset, result);
    // Alt: dfs_subsets_alt(nums, 0, subset, result);
    return result;
}


// 04/01/2023 LC78-Medium: Subsets
// Bit manipulation. Nums are distinct
// O(n*2^n)xO(1). // using move semantics & not counting storage for output.
vector<vector<int>> subsets_iter(vector<int>& nums) {
    
    // bit manipulation can be done only upto 32 bits.
    // if unsigned long long then upto 64 bits
    if(nums.size()>32) return {};

    unsigned int pset_size = 1U << nums.size();
    vector<vector<int>> result(pset_size);

    for(int i=0;i<pset_size;i++){
        vector<int> subset;
        int j = i, idx=0;
        while(j){
            if(j&1) subset.push_back(nums[idx]);
            j>>=1;
            idx++;
        }
        result[i] = move(subset);
    }
    return result;
}


void dfs_combinationSum(vector<int> &candidates, int idx, int target, vector<int> &cur_comb, vector<vector<int>> &result){
    if(target==0){
        result.push_back(cur_comb);
        return;
    }
    if(target<0 || idx==candidates.size()) return;

    // Two decisions - stop including the current node in children => idx+1
    // Or include it in all children & When you include it don't increment idx you might want to include again.
    // Hence we have a binary tree
    dfs_combinationSum(candidates, idx+1, target, cur_comb, result);
    cur_comb.push_back(candidates[idx]);
    dfs_combinationSum(candidates, idx, target-candidates[idx], cur_comb, result);
    cur_comb.pop_back();
}

// 04/01/2023 LC39-Medium: Combination Sum
// Distinct +ve candidates. -ve candidates => infinite possibilities.
// O(target*2^target)xO(target). Since bianry tree -> (2 decisions for each node)
// values in candidates at least 1. So depth of tree can be upto target hence O(2^n) TC since (2^n)-1 nodes
// and each combinationSum is constructed using O(target).
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> result;
    vector<int> cur_comb;
    dfs_combinationSum(candidates, 0, target, cur_comb, result);
    return result;
}


void dfs_permute(vector<int>& nums, int idx, vector<vector<int>> &result){
    if(idx==nums.size()) result.push_back(nums);

    for(int i=idx;i<nums.size();i++){
        // Equivalent to deleting i & finding (n-1)! permutations & then adding nums[i] to the result of dfs.
        swap(nums[i], nums[idx]);        
        dfs_permute(nums, idx+1, result);

        // replacing back the idx and getting ready to delete some other element
        swap(nums[idx], nums[i]);
    }
}


// 04/01/2023 LC46-Medium: Permutations
// O(n*n!)xO(n)
vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> result;
    dfs_permute(nums, 0, result);
    return result;
}


void dfs_subsetsWithDup_alt(vector<int>& nums, int idx, vector<int> &subset, vector<vector<int>> &result){
    result.push_back(subset);
    for(int i=idx;i<nums.size();i++){
        if(i>idx && nums[i]==nums[i-1]) continue;
        subset.push_back(nums[i]);
        dfs_subsetsWithDup_alt(nums, i+1, subset, result);
        subset.pop_back();
    }
}


// DEFAULT
// By dividing decision with having num[idx] and not having num[idx] their subtrees will never have same
// elements thus eliminating duplicates.
void dfs_subsetsWithDup(vector<int>& nums, int idx, vector<int> &subset, vector<vector<int>> &result){
    if(idx == nums.size()){
        result.push_back(subset);
        return;
    }

    
    // All subsets that includes nums[idx]
    subset.push_back(nums[idx]);
    dfs_subsetsWithDup(nums, idx+1, subset, result);
    subset.pop_back();

    // All subsets that doesn't include nums[idx] -> remove all consequent same elements.
    while(++idx<nums.size() && nums[idx]==nums[idx-1]);
    dfs_subsetsWithDup(nums, idx, subset, result);
}

// 04/01/2023 LC90-Medium: Subsets II
// Return distinct subsets when duplicates are present
// O(n*2^n)xO(n)
vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    vector<vector<int>> result;
    vector<int> subset;
    sort(nums.begin(), nums.end());
    dfs_subsetsWithDup(nums, 0, subset, result);
    // dfs_subsetsWithDup_alt(nums, 0, subset, result);
    return result;
}


void dfs_combinationSum2(vector<int>& candidates, int idx, int target, vector<int> &cur_comb, vector<vector<int>> &result){
    if(target==0){
        result.push_back(cur_comb);
        return;
    }
    if(target<0 || idx == candidates.size()) return;

    cur_comb.push_back(candidates[idx]);
    dfs_combinationSum2(candidates, idx+1, target-candidates[idx], cur_comb, result);
    cur_comb.pop_back();

    while(++idx<candidates.size() && candidates[idx]==candidates[idx-1]);
    dfs_combinationSum2(candidates, idx, target, cur_comb, result);
}

// 04/01/2023 LC40-Medium: Combination Sum II
// O(n*2^n)xO(n)
vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    vector<vector<int>> result;
    vector<int> cur_comb;
    sort(candidates.begin(), candidates.end());

    dfs_combinationSum2(candidates, 0, target, cur_comb, result);
    return result;
}


bool dfs_exist(vector<vector<char>>& board, string &word, int i, int j, int idx=0) {
    if(idx==word.size()) return true;
    if(i<0 || i>=board.size() || j<0 || j>=board[0].size()) return false;
    if(!board[i][j] || board[i][j]!=word[idx]) return false;

    board[i][j] = 0;
    bool ans = dfs_exist(board, word, i, j+1, idx+1)
                || dfs_exist(board, word, i, j-1, idx+1)
                || dfs_exist(board, word, i+1, j, idx+1)
                || dfs_exist(board, word, i-1, j, idx+1);
    board[i][j] = word[idx];
    return ans;
}

// 05/01/2023 LC79-Medium: Word Search
// Alt: prune search by reversing the word & starting search if # of word[0] > # of word[L-1] in board.
// O(m*n*4^L)xO(L) where L is length of the word. O(L) for call stack.
bool exist(vector<vector<char>> &board, string word){
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[0].size();j++){
            if(dfs_exist(board, word, i, j)) return true;
        }
    }
    return false;
}


void dfs_partition_alt(string &s, int idx, string &substr, vector<string> &partition, vector<vector<string>> &result){
    auto isPali = [](string &s){return equal(s.begin(), s.begin()+s.length()/2, s.rbegin());};
    if(idx == s.length()){
        if(isPali(substr)){
            partition.push_back(substr);
            result.push_back(partition);
            partition.pop_back();
        }
        return;
    }

    substr.push_back(s[idx]);
    dfs_partition_alt(s, idx+1, substr, partition, result);
    substr.pop_back();

    if(substr.length() && isPali(substr)){
        partition.push_back(move(substr)); // reduce copy.
        substr = string(1, s[idx]);
        dfs_partition_alt(s, idx+1, substr, partition, result);
        substr = move (partition.back()); // reduce copy
        partition.pop_back();
    }
}


bool isPali(string &s, int i, int j){
    while(i<j){
        if(s[i]!=s[j]) return false;
        i++;
        j--;
    }
    return true;
};

// DEFUALT    
void dfs_partition(string &s, int idx, vector<string> &partition, vector<vector<string>> &result){
    
    if(idx==s.length()){
        result.push_back(partition);
        return;
    }

    for(int i=idx;i<s.length();i++){
        if(isPali(s, idx, i)){
            partition.push_back(s.substr(idx, i-idx+1));
            dfs_partition(s, i+1, partition, result);
            partition.pop_back();
        }
    }
}

// 05/01/2023 LC131-Medium: Palindrome Partitioning
// Alt: your method of making decision to build the current substring or break string till before to a partiion
// if palindrome and start new substr from here.
// O(L*2^L)xO(L) => ignoring the output memory. From Alt method 2 possibilities at every char -> break substr & create
// partition or continue building current substring => 2^L partitions possible. O(L) to build each partition.
vector<vector<string>> partition(string s) {
    vector<vector<string>> result;
    vector<string> partition;
    dfs_partition(s, 0, partition, result);
    return result;
}


void dfs_letterCombinations(string &digits, int idx, string &cur_comb, string *keypad, vector<string> &result){
    if(idx==digits.length()){
        result.push_back(cur_comb);
        return;
    }

    for(char &c: keypad[digits[idx]-'2']){
        cur_comb.push_back(c);
        dfs_letterCombinations(digits, idx+1, cur_comb, keypad, result);
        cur_comb.pop_back();
    }
}

// 05/01/2023 LC17-Medium: Letter combinations of a phone number
// Basically combination problem: 3*3*3*4*4*3...... => Easily implemented with backtracking here. 
// Alt: You could also just take previous result and for each element in result add each char for current digit
// and construct new result. => Iterative solution. Easier with backtracking. Look at leetcode submission for iter.
// O(L*4^L)xO(L) for stack & cur_comb. output storage is never counted in space complexity. L = len(digits).
vector<string> letterCombinations(string digits) {
    if(digits.empty()) return vector<string>();

    string keypad[10] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> result;
    string cur_comb;
    dfs_letterCombinations(digits, 0, cur_comb, keypad, result);

    return result;
}


int main(int argc, char const *argv[])
{

    return 0;
}