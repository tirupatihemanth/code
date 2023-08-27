#include <iostream>
#include <unordered_set>
#include "leetcode.h"

using namespace std;


/*  CTCI CH1 - Arrays & Strings */

// 19/06/2023 1.1: Is Unique
// O(n)xO(n)
bool is_unique(string str){

    // Or you could use boolean array
    unordered_set<char> ust(str.begin(), str.end());    
    return ust.size() == str.length();
}

// 19/06/2023 1.1: Is Unique
// O(n)xO(1)
// Assumptions: ASCII Alphabet only and all small
bool is_unique_alt(string str){
    int hm=0;
    for(char &c:str){
        int val = c-'a';
        if(hm & (1<<val)) return false;
        hm |= (1<<val);
    }

    return true;
}


// 20/06/2023 1.2: Check Permutation
// Assuming ASCII -> 128 characters. Extended ASCII -> 256 characters. 
// Remember strings needn't be just alphabets it can be any of ASCII 128 chars 
// O(n)xO(1)
bool check_permutation(string str1, string str2){
    if(str1.length()!=str2.length()) return false;
    int hm[128] = {0};
    for(char &c: str1) hm[c]++;
    for(char &c:str2){
        if(--hm[c]<0) return false;
    }
    return true;
}


// 20/06/2023 1.3: URLify
// O(n)xO(1)
void URLify(char *str, int len){
    int num_spaces=0;
    for(int i=0;i<len;i++){
        if(str[i]==' ') num_spaces++;
    }
    int i = len + num_spaces*2 - 1;
    int j = len-1;
    while(j>0){
        if(str[j]==' '){
            str[i--]='0';
            str[i--]='2';
            str[i--]='%';
        }
        else{
            str[i--]=str[j];
        }
        j--;
    }
}


// 20/06/2023 1.3: Palindrome Permutation
// Assumptions: ASCII 128 chars only
// Can do bit vector approach with an integer if only lower alphabets used.
// O(n)xO(1)
bool palin_perm(string str){
    bool hm[128] = {false};

    for(char &c:str){
        hm[c] = !hm[c];
    }

    int count=0;
    for(auto var: hm){
        if(var) count++;
        if(count>1) return false;
    }
    
    return true;
}


// 20/06/2023 1.5: One Edit Away (Or Zero Edit Away)
// O(n)xO(1)
bool one_edit_away(string str1, string str2){
    int n1 = str1.length(), n2 = str2.length();
    if(abs(n1-n2)>1) return false;
    if(n1<n2){
        swap(str1, str2);
        swap(n1, n2);
    } // swap is O(1) since underlying container address swapped.
    
    bool diffFound=false;
    for(int i=0, j=0;j<n2;i++){
        if(str1[i]!=str2[j]){
            if(diffFound) return false;
            diffFound = true;
            if(n1==n2) j++;
        }
        else j++;
    }
    return true;
}


// 20/06/2023 1.6: String Compression
// Assume only upper & lower case alphabets => A=65 to z=122 => total 58 space needed
string str_compress(string str){
    if(str.length()<=1) return str;
    string result;
    char prev = str[0];
    int prev_count=1;
    for(int i=1;i<str.length();i++){
        if(str[i]!=prev){
            result.push_back(prev);
            result+=to_string(prev_count);
            prev = str[i];
            prev_count=1;
        }
        else prev_count++;
    }
    result.push_back(prev);
    result+=to_string(prev_count);
    return result.length()<str.length()?result:str;
}


// 20/06/2023 1.7: Rotate Matrix
// O(n^2)xO(n^2)
vector<vector<int>> rotate_matrix(vector<vector<int>> &mat){
    int m = mat.size(), n = mat[0].size();
    vector<vector<int>> result(m, vector<int>(n));

    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            result[j][m-i-1] = mat[i][j];
        }
    }
    return result;
}


void _matTranspose(vector<vector<int>> &mat){
    for(int i=0;i<mat.size();i++){
        for(int j=i+1;j<mat[0].size();j++){
            swap(mat[i][j], mat[j][i]);
        }
    }
}


// 20/06/2023 1.7: Rotate Matrix
// O(n^2)xO(1)
// Transpose & reverse rows to get 90 CW rotation
// Transpose & reverse cols to get 90 ACW rotation
void rotate_matrix_1(vector<vector<int>> &mat){
    int m = mat.size(), n = mat[0].size();
    _matTranspose(mat);
    for(int i=0;i<m;i++){
        reverse(mat[i].begin(), mat[i].end());
    }
}


// 20/06/2023 1.7: Rotate Matrix
// O(n^2)xO(1) Layer by layer method.
void rotate_matrix_2(vector<vector<int>> &mat){
    
    if(mat.empty() || mat[0].size()!=mat.size()) return;

    int N = mat.size();
    for(int i=0;i<N/2;i++){
        for(int j=i; j<N-i-1;j++){
            int temp = mat[i][j];
            mat[i][j] = mat[N-j-1][i];
            mat[N-j-1][i] = mat[N-i-1][N-j-1];
            mat[N-i-1][N-j-1] = mat[j][N-i-1];
            mat[j][N-i-1] = temp;

        }
    }
}


// 21/06/2023 1.8: Zero Matrix
// O(mxn)xO(m+n). For O(1) you can try using first row & cols to indicate status. 
// Use vars FirstRowHasZero, FirstColHasZero to nullify them at last.
void zero_matrix(vector<vector<int>> &mat){
    int m = mat.size(), n = mat[0].size();
    bool row_status[m], col_status[n];
    fill(row_status, row_status+m, true);
    fill(col_status, col_status+n, true);

    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(!mat[i][j]){
                row_status[i] = false;
                col_status[j] = false;
            }
        }
    }

    for(int i=0;i<m;i++){
        if(!row_status[i]){
            for(auto &num:mat[i]){
                num = 0;
            }
        }
    }

    for(int j=0;j<n;j++){
        if(!col_status[j]){
            for(int i=0;i<m;i++){
                mat[i][j] = 0;
            }
        }
    }
}


// 21/06/2023 1.9: String Rotation
// Conditions: Make only 1 call to check for substring
// O(m+n)xO(n). 
bool str_rotation(string s1, string s2){
    if(s1.length()!=s2.length() || s1.empty()) return false;
    s1 += s1;
    if(s1.find(s2)==string::npos) return false;
    return true;
}


int main(){

    cout << is_unique("helo") << endl;
    cout << is_unique_alt("helo") << endl;
    cout << check_permutation("hell", "lleh") << endl;

    char str[] = "Mr John Smith    ";
    URLify(str, 13);
    cout << str << endl;

    cout << palin_perm("@#&@#&") << endl;
    cout << one_edit_away("pale", "bake") << endl;
    cout << str_compress("aabbccddd") << endl;


    // vector<vector<int>> mat = {{1,2,3, 4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16}};
    // vector<vector<int>> mat = {{1,2}, {3, 4}};

    // vector<vector<int>> rotated_mat = rotate_matrix(mat);
    // printMatrix<int>(rotated_mat);
    // rotate_matrix_1(mat);
    // printMatrix(mat);
    // rotate_matrix_2(mat);
    // printMatrix(mat);
    


    // vector<vector<int>> mat = {{1,0,2, 4}, {5,6,0,8}, {9,10,11,12}, {13,14,15,16}};
    // zero_matrix(mat);
    // printMatrix(mat);

    cout << str_rotation("waterbottle", "erbottlewat") << endl;
    return 0;
}