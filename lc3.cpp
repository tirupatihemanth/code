#include "leetcode.h"
using namespace std;

/* Arrays & Hashing. */
/* A Neetcode.io compilation */


// 04/12/2022 LC1-Easy: Two Sum
// O(N) x O(N) using complement method.
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> ump;
    for(int i=0;i<nums.size();i++){
        int complement = target-nums[i];
        if(ump.find(complement)!=ump.end()){
            return {ump[complement], i};
        }
        ump[nums[i]] = i;
    }
    return {};
}

// 04/12/2022 LC49-Medium: Group Anagrams
// O(n*l) where n is size of strs and l be the max length of a string
// Idea is to create an effective hash for the vector of counts.
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> gaMap;
    for(string &s:strs){
        int arr[26] = {0};
        for(char c:s) arr[c-'a']++;
        string key;
        for(int i=0;i<26;i++) if(arr[i]) key.append(to_string(arr[i])).push_back('a'+i);
        gaMap[key].push_back(s);
    }
    vector<vector<string>> result;
    result.reserve(gaMap.size());
    for(auto &x:gaMap) result.push_back(x.second);
    return result;
}

// 05/12/2022 LC347-Medium: Top K Frequent Elements
//O(n)xO(n). Uses hashmap for finding frequencies and then bucket sort/hashing based on frequency.
//O(nlogk)xO(n) if you use min heap based priority queue impl.
//O(n) avg x O(n) if you use quickselect based solution.
vector<int> topKFrequent(vector<int>& nums, int k) {
    if(!k) return {};
    unordered_map<int, int> ump;
    for(int x:nums) ump[x]++;
    vector<int> freqHashing[nums.size()+1];
    for(auto &x: ump){
        freqHashing[x.second].push_back(x.first);
    }
    vector<int> result;
    for(int i=nums.size();i>=0 && k>0;i--){
        for(int j=0;j<freqHashing[i].size() && k>0;j++, k--){
            result.push_back(freqHashing[i][j]);
        }
    }
    return result;
}

// 05/12/2022 LC238-Medium: Product of Array Except Self
// O(n)xO(1) assuming output array doesn't count in memory complexity. 
// Not using division op. Else just total product/num[i] will just give result array;
vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size(), suffixProduct=nums[n-1];
    vector<int> result(nums.begin(), nums.end());
    for(int i=1;i<n-1;i++){
        result[i]*=result[i-1];
    }
    result[n-1] = result[n-2];
    for(int i=n-2;i>0;i--){
        result[i] = result[i-1]*suffixProduct;
        suffixProduct*=nums[i];
    }
    result[0] = suffixProduct;
    return result;
}

// 05/12/2022 LC36-Medium: Valid Sudoku
// O(9)xO(9). Instead of hashsets you can also use row[9][9], col, grid bool matrices since values of board 
// are only range from '1' to '9' map them to indices 0-8 and index for already seen or not.
bool isValidSudoku(vector<vector<char>>& board) {
    vector<unordered_set<char>> row_sets(board.size());
    vector<unordered_set<char>> col_sets(board.size());
    vector<unordered_set<char>> grid_sets(board.size());

    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(board[i][j]=='.')continue;
            
            if(!row_sets[i].emplace(board[i][j]).second) return false;
            if(!col_sets[j].emplace(board[i][j]).second) return false;
            if(!grid_sets[(i/3)*3+(j/3)].emplace(board[i][j]).second) return false;
        }
    }
    return true;
}

// 05/12/2022 LC271-Medium: Encode and Decode Strings; LNT659;
// Both O(nl)xO(1) where n is size of strs and l is max length of a string.
class EncodeAndDecode{
    public:

    string encode(vector<string> &strs){
        string encodedStr;
        for(string &str:strs){
            encodedStr+=to_string(str.length())+";"+str;
        }
        return encodedStr;
    }

    vector<string> decode(string str){
        vector<string> strs;
        int i=0;
        while(i<str.size()){
            int length=0;
            while(str[i]!=';'){
                length = length*10 + (str[i]-'0');
                i++;
            }
            i++;
            strs.push_back(str.substr(i, length));
            i+=length;
        }
        return strs;
    }
};

// 05/12/2022 LC128-Medium: Longest Consecutive Sequence
// O(n) x O(n): Each element is visited once for to check if it is the start of a sequence 
// and to check if it's part of some sequence. 
// Idea is to visualize the given array on the number line and identify patter as a human eye would recognize
int longestConsecutive(vector<int>& nums) {
    unordered_set<int> st(nums.begin(), nums.end());
    int max_length = 0;
    int cur_length;

    for(int x:nums){
        if(!st.count(x-1)){
            cur_length = 1;
            while(st.count(++x)){
                cur_length+=1;
            }
            max_length = max(max_length, cur_length);
        }
    }

    return max_length;
}


/* NEETCODE ALL PROBLEMS BEGIN */



int main(int argc, char const *argv[])
{

    vector<int> nums = {};
    cout << longestConsecutive(nums)<<endl;
    // groupAnagrams(strs);
    return 0;
}
