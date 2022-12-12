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


// 06/12/2022 LC328-Medium: Odd Even Linked List
ListNode* oddEvenList(ListNode* head) {
    if(!head) return head;
    ListNode* odd, *even, *oddHead, *evenHead;
    odd = head;
    even = evenHead = head->next;

    while(even && even->next){
        odd->next = odd->next->next;
        odd = odd->next;
        even->next = even->next->next;
        even = even->next;
    }

    odd->next = evenHead;
    return head;
}


// 07/12/2022 LC938-Easy: Range Sum of BST
// O(n) x O(n) another style soln using iterative impl.
int rangeSumBST_iter(TreeNode* root, int low, int high) {
    if(!root) return 0;
    stack<TreeNode*> sk;
    sk.push(root);
    int rangeSum=0;
    while(!sk.empty()){
        TreeNode * cur = sk.top();
        sk.pop();
        if(!cur) continue;
        if(low <=  cur->val && cur->val <=high){
            rangeSum+=cur->val;
        }
        if(cur->val > low){
            sk.push(cur->left);
        }
        if(cur->val<high){
            sk.push(cur->right);
        }
    }
    return rangeSum;
}

// 07/12/2022 LC938-Easy: Range Sum of BST
// O(n)xO(n) recursive impl.
int rangeSumBST(TreeNode* root, int low, int high) {
    if(!root) return 0;
    if(root->val<low){
        return rangeSumBST(root->right, low, high);
    }
    else if(root->val>high){
        return rangeSumBST(root->left, low, high);
    }
    return root->val + rangeSumBST(root->left, low, high) + rangeSumBST(root->right, low, high);
}


void getLeaves(vector<int> &leaves, TreeNode* root){
    if(!root) return;
    if(!root->left && !root->right){
        leaves.push_back(root->val);
        return;
    }
    getLeaves(leaves, root->left);
    getLeaves(leaves, root->right);
}

// 08/12/2022 LC872-Easy: Leaf-Similar Trees.
// O(n1+n2)xO(H)
bool leafSimilar(TreeNode* root1, TreeNode* root2) {
    vector<int> leaves1, leaves2;
    getLeaves(leaves1, root1);
    getLeaves(leaves2, root2);
    return leaves1==leaves2;
}


int maxAncestorDiff(TreeNode* root, int ancMinVal, int ancMaxVal){
    if(!root) return abs(ancMaxVal-ancMinVal);
    int newMinVal = min(ancMinVal, root->val);
    int newMaxVal = max(ancMaxVal, root->val);
    return max(
        maxAncestorDiff(root->left, newMinVal, newMaxVal), 
        maxAncestorDiff(root->right, newMinVal, newMaxVal)
    );
}

// 09/12/2022 LC1026-Medium: Maximum difference between node and ancestor.
// O(n)xO(h) Finding the max of abs(ancestor-child) value.
int maxAncestorDiff(TreeNode* root){
    if(!root) return 0;
    return maxAncestorDiff(root, root->val, root->val);
}


int treeSumMaxProduct(TreeNode* root, long long &maxP, int treeSum){
    if(!root) return 0;
    
    int subTreeSum = root->val + 
                    treeSumMaxProduct(root->left, maxP, treeSum) + 
                    treeSumMaxProduct(root->right, maxP, treeSum);

    maxP = max( maxP, (treeSum-subTreeSum)*(long long)subTreeSum );

    return subTreeSum;

}

// 10/12/2022 LC1339-Medium: Maximum Product of Splitted Binary Tree
// O(n)xO(h)
int maxProduct(TreeNode* root) {
    long long maxP=LONG_LONG_MIN;
    // Calculate total sum of all nodes in tree using same function
    int treeSum = treeSumMaxProduct(root, maxP, 0);
    maxP = LONG_LONG_MIN;
    // pass maxP by reference and accumulate maxProduct value
    treeSumMaxProduct(root, maxP, treeSum);
    return maxP%int(1e9+7);
}

// Though returning zero instead of negative height will give incorrect height (not technically
// at all since we are returning maximum sum of vals from given node to the leaves) but
// it solves the problem of maxPathSum as negative height will only reduce maxPathSum through
// current rootnode.
int maxHeight(TreeNode* root, int &maxPathSum){
    if(!root) return 0;
    int leftHeight = maxHeight(root->left, maxPathSum);
    int rightHeight = maxHeight(root->right, maxPathSum);
    int maxHeight = max(leftHeight, rightHeight);
    
    maxPathSum = max(maxPathSum, root->val+leftHeight+rightHeight);

    return root->val+maxHeight>0?root->val+maxHeight:0;
}

// 11/12/2022 LC124-Hard: Binary Tree Maximum Path Sum
// O(n)xO(h). At any node maxPath Sum is max of path passing through that node, path already
// found in left subtree or a path already found in right subtree. i.e doing a post order dfs traversal.
int maxPathSum(TreeNode* root) {
    int maxPathSum = INT_MIN;
    maxHeight(root, maxPathSum);
    return maxPathSum == INT_MIN?0:maxPathSum;
}


// 12/12/2022 LC70-Easy: Climbing Stairs
// O(n)xO(1): Can reach nth step from (n-1)+1 step OR (n-2)+2 step
int climbStairs(int n) {
    if(!n) return n;
    if(n==1) return 1;
    if(n==2) return 2;
    int prev1 = 2, prev2=1, result;
    for(int i=3;i<=n;i++){
        result = prev1+prev2;
        prev2 = prev1;
        prev1 = result;
    }
    return result;
}

// 12/12/2022 LC62-Medium: Unique Paths.
// O(mn)xO(mn). Initialization required for grid[1][] row and grid[][1] column to 1.
// Combinatorics: (m+n-2)! / (m-1)!*(n-1)! i.e m*(m+1)*...(m+n-2)/1*2*..(n-1) But could overflow even if
// you are simultaneously multiplying and dividing using iteration.

int uniquePaths(int m, int n) {
    vector<vector<int>>grid(m+1, vector<int>(n+1, 1));

    for(int i=2;i<m+1;i++){
        for(int j=2;j<n+1;j++){
            grid[i][j] = grid[i][j-1]+grid[i-1][j];
        }
    }

    return grid[m][n];        
}

// 12/12/2022 LC91-Medium: Decode Ways
// O(l)xO(l) string upto length l can be decoded from either string of l-1 provided lth char!='0'
// or from string upto length l-2 provided (l-1)th char and lth char form num b/2 10-26.
// space complexity can be made O(1) as count[i+1] only depended on last two vals.
int numDecodings(string s) {
    if(!s.length() || s[0]=='0') return 0;
    vector<int> count(s.length()+1, 0);
    count[0]=count[1]=1;
    for(int i=1;i<s.length();i++){
        if(s[i]!='0') count[i+1]=count[i];
        if(s[i-1]!='0'){
            int num=s[i-1]-'0';
            num = num*10 + s[i]-'0';
            if(num>=10 && num<=26) count[i+1]+=count[i-1];
        }
        
    }
    return count[s.length()];
}

// 12/12/2022 LC639-Hard: Decode Ways II
// O(l)xO(l) Same as Decode Ways problem but with * as a valid char representing values ranging [1,9].
// space complexity can be made O(1) as count[i+1] only depended on last two vals.
int numDecodings_II(string s) {
    if(!s.length() || s[0]=='0') return 0;
    vector<lli> count(s.length()+1, 0);
    count[0]=1;
    count[1]=s[0]=='*'?9:1;
    for(int i=1;i<s.length();i++){
        
        if(s[i]!='0'){
            if(s[i]=='*') count[i+1] = count[i]*9;
            else count[i+1]=count[i];
        }

        if(s[i-1]!='0'){
            if(s[i]=='*'){
                if(s[i-1]=='1') count[i+1] += (count[i-1]*9);
                else if(s[i-1]=='2') count[i+1] += (count[i-1]*6);
            }
            if(s[i-1]=='*'){
                if(s[i]=='*') count[i+1] += (count[i-1]*15);
                else if(s[i]<='6') count[i+1] += (count[i-1]*2);
                else if(s[i]>'6') count[i+1] += count[i-1];
            }
            if(s[i]!='*' && s[i-1]!='*'){
                int num=s[i-1]-'0';
                num = num*10 + s[i]-'0';
                if(num>=10 && num<=26) count[i+1] += count[i-1];
            }
        }
        count[i+1] %= int(1e9+7);
    }
    return count[s.length()];
}

int main(int argc, char const *argv[])
{
    //cout << closeStrings("cabbba", "abbccc")<<endl;   
    
    vector<int> v = {10,5,15,3,7,18};
    TreeNode* root = makeBST(v);
    // cout << rangeSumBST(root, 7, 15) << endl;
    // cout << maxAncestorDiff(root)<<endl;
    // cout << minimumAverageDifference(v)<<endl;
    
    // int m, n;
    // cin >> m >> n;
    // cout <<uniquePaths(m, n)<<endl;
    return 0;
}
