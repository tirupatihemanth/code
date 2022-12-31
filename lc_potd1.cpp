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
int dfs_maxPathSum(TreeNode* root, int &result){
    if(!root) return 0;
    int left = dfs_maxPathSum(root->left, result);
    int right = dfs_maxPathSum(root->right, result);
    result = max(left+right+root->val, result);
    
    return max(root->val+max(left, right), 0);
}

// 11/12/2022 LC124-Hard: Binary Tree Maximum Path Sum
// O(n)xO(h). At any node maxPath Sum is max of path passing through that node, path already
// found in left subtree or a path already found in right subtree. i.e doing a post order dfs traversal.
int maxPathSum(TreeNode* root) {
    int maxPathSum = INT_MIN;
    dfs_maxPathSum(root, maxPathSum);
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

// 13/12/2022 LC931-Medium: Minimum Falling Path Sum
// O(mn)xO(1) Bottom up DP solution. Alt: Top down can be done.
int minFallingPathSum(vector<vector<int>>& matrix) {
    if(!matrix.size()) return 0;
    int m = matrix.size(), n = matrix[0].size();
    // You can also do top down DP from i=1 and taking max element in last row
    for(int i=m-2; i>=0; i--){
        for(int j=0;j<n;j++){
            int j1 = max(j-1, 0), j2 = min(j+1, n-1);
            matrix[i][j] += min({
                matrix[i+1][j1],
                matrix[i+1][j],
                matrix[i+1][j2]
            });
        }
    }
    return *min_element(matrix[0].begin(), matrix[0].end());
}


// Top Down DP. Remove memo and we just have top-down recursion with overlapping sub-problems -> TLE
// O(n)xO(n): O(n) b/o element of result is computed only once in O(1) time. O(n) stack space + memo.
/* 
    For most DP probs follow these steps
    STEP 1: Come up with recursion relation: rob(i) = max(curVal+rob(i+2), rob(i+1)); i.e top-down
    STEP 2: If there are overlapping subproblems use a memo as array/unordered_map => Solved.
    STEP 3: To improve on stack space. Convert recursive top-down to iterative bottom-up using table/array.
    STEP 4: To improve on memo space. Based on what previous values are used in recursion store only those N vars.
 */
int rob(vector<int>& nums, vector<int> &memo, int start=0) {
    if(start>=nums.size()) return 0;
    if(memo[start]!=-1) return memo[start];

    int result = max(nums[start]+rob(nums, memo, start+2), rob(nums, memo, start+1));
    return memo[start] = result;
}

// 14/12/2022 LC198-Medium: House Robber
int rob_r(vector<int> &nums){
    vector<int> memo(nums.size(), -1);
    return rob(nums, memo);
}

// 14/12/2022 LC198-Medium: House Robber
// O(n)xO(n). O(n) memo. Bottom-up DP using tabulation.
int rob(vector<int> &nums){
    vector<int> maxRobbed(nums.size()+2, 0);

    for(int i=nums.size()-1;i>=0;i--){
        maxRobbed[i] = max(nums[i]+maxRobbed[i+2], maxRobbed[i+1]);
    }

    return maxRobbed[0];
}    

// 14/12/2022 LC198-Medium: House Robber
// O(n) x O(1). Only O(1) memo. Bottom up DP.
int rob_alt(vector<int> &nums){
    int prev1=0, prev2=0, result;
    
    for(int i=nums.size()-1;i>=0;i--){
        result = max(nums[i]+prev2, prev1);
        prev2 = prev1;
        prev1 = result;
    }

    return result;
}  

// Top Down DP.
int longestCommonSubsequence(string &text1, string &text2, int i, int j, int *memo) {
    int m = text1.length(), n = text2.length();
    if(i==m || j==n) return 0;
    if(memo[i*n+j]!=-1) return memo[i*n+j];

    if(text1[i]==text2[j]){
        memo[i*n+j] = 1 + longestCommonSubsequence(text1, text2, i+1, j+1, memo);
    }
    else
        memo[i*n+j] = max(
            longestCommonSubsequence(text1, text2, i+1, j, memo), 
            longestCommonSubsequence(text1, text2, i, j+1, memo)
            );
    
    return memo[i*n+j];
}

// 15/12/2022 LC1143-Medium: Longest Common Subsequence
// O(mn)xO(mn). Top Down DP with memo.
int longestCommonSubsequence_r(string text1, string text2){
    int memo[text1.size()][text2.size()];
    fill(&memo[0][0], &memo[text1.size()-1][text2.size()-1]+1, -1);

    return longestCommonSubsequence(text1, text2, 0, 0, &memo[0][0]);
}


// 15/12/2022 LC1143-Medium: Longest Common Subsequence
// O(mn)xO(mn). Bottom up DP using tabulation.
int longestCommonSubsequence(string text1, string text2) {
    int mat[text1.size()+1][text2.size()+1];

    // Variable sized array initialization not allowed hence use fill
    // fill works because internally n-dim array is 1d contiguous array
    fill(&mat[0][0], &mat[text1.size()][text2.size()]+1, 0);
    
    for(int i=1;i<=text1.size();i++){
        for(int j=1;j<=text2.size();j++){
            if(text1[i-1]==text2[j-1])
                mat[i][j] = mat[i-1][j-1]+1;
            else
                mat[i][j] = max(mat[i-1][j], mat[i][j-1]);
        }
    }

    return mat[text1.size()][text2.size()];
}


// 15/12/2022 LC1143-Medium: Longest Common Subsequence
// Bottomu DP. memo optimized by storing only two columns.
// O(mn)xO(n)
int longestCommonSubsequence_alt(string text1, string text2) {
    int mat[2][text2.size()+1];
    fill(&mat[0][0], &mat[1][text2.size()]+1, 0);
    
    for(int i=1;i<=text1.size();i++){
        for(int j=1;j<=text2.size();j++){
            if(text1[i-1]==text2[j-1])
                mat[i%2][j] = mat[!(i%2)][j-1]+1;
            else
                mat[i%2][j] = max(mat[!(i%2)][j], mat[i%2][j-1]);
        }
    }

    return mat[text1.size()%2][text2.size()];
}


// 16/12/2022 LC232-Easy: Implement queue using stacks
// push: O(1). Pop: O(1) amortized. O(n) worst. Since for each element push&pop ops are done utmost twice
class MyQueue {
    stack<int> push_sk, pop_sk;
public:
    MyQueue() {
        
    }
    
    void push(int x) {
        push_sk.push(x);
    }
    
    int pop() {
        int result = peek();
        pop_sk.pop();
        return result;
    }
    
    int peek() {
        if(pop_sk.empty()){
            while(!push_sk.empty()){
                pop_sk.push(push_sk.top());
                push_sk.pop();
            }
        }
        return pop_sk.top();
    }
    
    bool empty() {
        return push_sk.empty() && pop_sk.empty();
    }
};

// 19/12/2022 LC1971: Find if path exists in graph.
// Like BFS you have to set visited true while inserting into stack itself. Else You wil insert
// same node multiple times into the stack.
// O(V+E)xO(V)
bool validPath_dfs_i(int n, vector<vector<int>>& edges, int source, int destination) {
    vector<int> adj[n];
    for(auto &v: edges){
        adj[v[0]].push_back(v[1]);
        adj[v[1]].push_back(v[0]);
    }

    bool visited[n];
    fill(visited, visited+n, false);
    stack<int> sk;

    sk.push(source);
    visited[source]=true;
    while(!sk.empty()){
        int u = sk.top();
        sk.pop();
        if(u==destination) return true;
        
        for(int v:adj[u]){
            if(visited[v]) continue;
            sk.push(v);
            visited[v]=true;
        }
    }
    return false;
}

// 19/12/2022 LC1971: Find if path exists in graph.
// O(V+E)xO(E)
bool validPath_bfs(int n, vector<vector<int>>& edges, int source, int destination) {
    vector<int> adj[n];
    for(auto &v: edges){
        adj[v[0]].push_back(v[1]);
        adj[v[1]].push_back(v[0]);
    }

    bool visited[n];
    fill(visited, visited+n, false);
    queue<int> q;

    q.push(source);
    visited[source]=true;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        if(u==destination) return true;
        for(int v:adj[u]){
            if(visited[v]) continue;
            visited[v]=true;
            q.push(v);
        }
    }
    return false;
}


bool validPath_dfs(vector<int> adj[], int s, int destination, bool visited[]){
    if(s == destination) return true;
    visited[s] = true;
    for(int v: adj[s]){
        if(visited[v]) continue;
        if(validPath_dfs(adj, v, destination, visited)) return true;
    }

    return false;
}


// 19/12/2022 LC1971: Find if path exists in graph.
// O(V+E)xO(E)
bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
    vector<int> adj[n];
    for(auto &v: edges){
        adj[v[0]].push_back(v[1]);
        adj[v[1]].push_back(v[0]);
    }

    bool visited[n];
    fill(visited, visited+n, false);
    return validPath_dfs(adj, source, destination, visited);
}


void dfs(vector<vector<int>> &rooms, int s, bool visited[]){
    visited[s]=true;
    for(int v:rooms[s]){
        if(!visited[v]) dfs(rooms, v, visited);
    }
}


// 20/12/2022 LC841-Medium: Keys and Rooms
// O(V+E)xO(V) Basically given adjacency list we are doing dfs to see if it's connected or not
bool canVisitAllRooms(vector<vector<int>>& rooms) {
    bool visited[rooms.size()];
    fill(visited, visited+rooms.size(), false);
    dfs(rooms, 0, visited);
    return all_of(visited, visited+rooms.size(), [](auto x){return x;});
}


bool twoColour_dfs(vector<int> adj[], int s, short colour[]){
    for(int &v:adj[s]){
        if(colour[v]==-1){
            colour[v]=!colour[s];
            twoColour_dfs(adj, v, colour);
        }
        else if(colour[v]==colour[s]){
            return false;
        }
    }
    return true;
}

// 21/12/2022 LC886-Possible Bipartition
// A graph is bipartite iff it's two colourable
// Alt: A graph is bipartite iff it doesn't have an odd cycle
// O(V+E)xO(V+E)
bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
    vector<int> adj[n+1];
    for(auto &v:dislikes){
        adj[v[0]].push_back(v[1]);
        adj[v[1]].push_back(v[0]);
    }
    short colour[n+1];
    fill(colour, colour+n+1, -1);
    for(int i=1;i<n+1;i++){
        if(colour[i]!=-1) continue;
        colour[i]=0;
        if(!twoColour_dfs(adj, i, colour)) return false;
    }
    return true;
}


void dfs1(vector<int> adj[], int s, vector<int> &result, int numNodes[]){
    numNodes[s]=1;
    for(int v:adj[s]){
        if(numNodes[v]) continue;
        dfs1(adj, v, result, numNodes);
        numNodes[s]+=numNodes[v];
        result[s]+=result[v]+numNodes[v];
    }
}

void dfs2(vector<int> adj[], int s, int parent, vector<int> &result, int numNodes[]){
    for(int v: adj[s]){
        if(parent==v)continue;
        // result[v] = result[s]-numNodes[v]+(n-numNodes[v])
        result[v] = result[s]-2*numNodes[v]+result.size();
        dfs2(adj, v, s, result, numNodes);
    }
}


// 22/12/2022 LC834-Hard: Sum of Distances in Tree
// Technique called ***** RE-ROOTING *****
// When we move the room from one node to it's adjacent then sum of all distances from cur node
// will decrease by 1 for No. of adj subtree nodes rooted at adj node and increase by 1 for 
// all remaining nodes i.e n-#adj subtree nodes
// You can also think of it as dp where you are passing parent value to the child.
// O(n) since O(E)=O(V)=O(n)
vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
    vector<int> adj[n], result(n, 0);
    for(auto &v:edges){
        adj[v[0]].push_back(v[1]);            
        adj[v[1]].push_back(v[0]); 
    }

    int numNodes[n];
    fill(numNodes, numNodes+n, 0);
    dfs1(adj, 0, result, numNodes);
    dfs2(adj, 0, -1, result, numNodes);
    return result;
}


// 23/12/2022 LC309: Best time to buy and sell stock with cooldown
// O(N^2)xO(N) => Alt: O(N)xO(N) optimization 
int maxProfit_naiveDP(vector<int>& prices) {
    int n = prices.size();
    int maxProfit[n];
    fill(maxProfit, maxProfit+n, 0);

    for(int i=n-2;i>=0;i--){

        // profit you can generate for buying on day i is prices[j]-prices[i]+maxProfit[j+2] 
        // max profit for buying on day i is obtained by iterating j from i+1 to n.
        // But (prices[j]+maxProfit[j+2]) - prices[i] in equation only first part only changes 
        // in that iteration keep that maxValue stored. Refer next sol.
        for(int j=i+1;j<n;j++){
            if(prices[j]>prices[i]){
                int curProfit = prices[j]-prices[i];
                curProfit += j+2<n?maxProfit[j+2]:0;
                maxProfit[i] = max(maxProfit[i], curProfit);
            }
        }
        maxProfit[i] = max(maxProfit[i], maxProfit[i+1]);
    }
    
    return maxProfit[0];
}


// 23/12/2022 LC309: Best time to buy and sell stock with cooldown
// O(N)xO(N) -> Alt: O(N)xO(1) => you only need maxProfit[i+1], maxProfit[i+2]
int maxProfit_DP(vector<int>& prices) {
    int n = prices.size();
    int maxProfit[n], maxSell;
    maxProfit[n-1]=0;

    // Selling on last day you get a sale price of prices[n-1] + 0 accumulated profit
    maxSell = prices[n-1];

    // Max sell indicates the day where you could sell to get the max sale price + acccumulated profit you could get if you buy on ith day.
    // have bought on ith day.
    for(int i=n-2;i>=0;i--){
        // Either you don't buy on ith day & get maxProfit[i+1] Or
        // You buy on ith day and sell it on the best day to get max profit
        maxProfit[i] = max(maxProfit[i+1], maxSell-prices[i]);

        // Selling on day i you get a sale price of prices[i] + accumulated profit of maxProfit[i+2]
        maxSell = max(maxSell, prices[i] + (i+2<n?maxProfit[i+2]:0));
    }
    return maxProfit[0];
}


// 23/12/2022 LC309: Best time to buy and sell stock with cooldown

/* 
    CONCEPT: State transition based DP. Identify variables to reprsent states and deduce equations for transitions

         _______
        |       |
        |----->BUY <-----COOLDOWN
                \         ^
                 \       /
                  v     /
                    SELL
                   ^    |
                   |____|


 */

// O(N)xO(N) Alt:O(N)xO(1) as # of states are finite you can only store the last useful value of a state
int maxProfit(vector<int> &prices){

    int n = prices.size();
    
    // Each of the values represent maxProfit that can be reached for i in the given state.
    int buy[n]; // In can buy state
    int sell[n]; // In can sell state i.e you just reached here after buy
    int cooldown[n];  // In cool down state i.e just reached here after sell.
    buy[0]=0; // You are in buy state => you don't have any stock.
    cooldown[0]=0; // You won't be here in the state just take some small value INT_MIN also works
    sell[0]=-prices[0]; //You reached here after buying prices[0] i.e a profit of -prices[0]

    for(int i=1;i<n;i++){
        buy[i] = max(buy[i-1], cooldown[i-1]);
        sell[i] = max(sell[i-1], buy[i-1]-prices[i]);
        cooldown[i] = sell[i-1]+prices[i];
    }

    // You won't get profit when you are already bought but didn't sell yet
    // You can rather stay in buy state without buying than come to sell state.
    return max(cooldown[n-1], buy[n-1]); 
}


// 24/12/2022 LC790-Medium: Domino and Tromino Tiling
// O(n)xO(n) -> can optimize to O(n)xO(1) since only dependent on a few prev values.
int numTilings(int n) {
    int N = 1e9 + 7;

    // Draw a state diagram with transition for types of dominos & trominos d1, d2, t1, t2, t3, t4
    // s[i] indicates the number of ways to reach state s after adding i tiles.
    int s1[n+1], s2[n+1], s3[n+1], s4[n+1];
    s1[0]=s2[0]=s3[0]=s4[0]=0; // when no tile is added 0 ways to reach that tile.
    s1[1]=s2[1]=s3[1]=s4[1]=1; // Ways to reach state s after adding 1 tile is 1 in each case.

    // You can substitue s2, s3, s4 recursive equations into s1 to simplify it further to
    // s1[i] = 2*s1[i-1]+s1[i-3]; change based cases to s1[1]=1;s1[2]=2;s1[3]=5; and start iteration from n=4
    // You are substituting in s1 because your result will be in s1 i.e s1[n] i.e trying to remove other states.
    for(int i=2;i<=n;i++){

        // You can fill ith tile in s1 either from s1[i-1] by adding just d1 or s2[i-1] by adding d2
        // or from s3[i-2] by adding t4 or from s4[i-2] by adding t3.
        // If you add t4 to s3[i-1] you will get i+1 tiles not i tiles. Hence you can reach i tiles filled i.e
        // s1[i] from s3[i-2] and adding a t4 to it. s3[i-2] you would'v just reached from s1[i-3]+t3 for understanding
        s1[i] = ((s1[i-1]+s2[i-1])%N+(s3[i-2]+s4[i-2])%N)%N;
        s2[i] = s1[i-1];

        // You can reach s3 on adding ith tile either from adding 1 t3 tile from s1[i-1] or d2 tile from s4[i-1]
        s3[i] = (s1[i-1]+s4[i-1])%N;
        s4[i] = (s1[i-1]+s3[i-1])%N;
    }

    // You will completely fill the given 2xn tile board only in s1 state in other cases there is empty slot.
    return s1[n];
}


// 25/12/2022 LC2389: Longest Subsequence with limited sum
// Remember subsequence needn't be contiguous. It isn't subarray.
// O(nlogn)xO(n) => since modifying input array space complexity is O(n)
vector<int> answerQueries(vector<int>& nums, vector<int>& queries) {
    vector<int> result(queries.size());
    sort(nums.begin(), nums.end());
    partial_sum(nums.begin(), nums.end(), nums.begin());

    for(int i=0;i<queries.size();i++){
        result[i] = upper_bound(nums.begin(), nums.end(), queries[i]) - nums.begin();
    }

    return result;
}


// 26/12/2022 LC55-Medium: Jump Game
// O(n)xO(1)
bool canJump(vector<int>& nums) {
    int reach=1, i=0;
    for(i=0;i<nums.size() && reach > 0;i++){
        reach = max(reach-1, nums[i]);            
    }

    return i==nums.size();
}


// 27/12/2022 LC2279-Medium: Maximum bags with full capacity of rocks
// O(nlogn)xO(n). Greedy approach.
int maximumBags(vector<int>& capacity, vector<int>& rocks, int additionalRocks) {
    
    for(int i=0;i<capacity.size();i++){
        capacity[i]-=rocks[i];
    }

    sort(capacity.begin(), capacity.end());

    int result=0;
    for(int i=0;i<capacity.size() && capacity[i]-additionalRocks<=0;i++){
        additionalRocks-=capacity[i];
        result+=1;
    }
    return result;
}


// 28/12/2022 LC1962-Medium: Remove stones to minimize the total
// O(n+klogn)xO(n)
int minStoneSum(vector<int>& piles, int k) {
    make_heap(begin(piles), end(piles));
    while(k-->0){
        pop_heap(begin(piles), end(piles));
        piles.back()-=piles.back()/2;
        push_heap(begin(piles), end(piles));
    }
    return accumulate(begin(piles), end(piles), 0);
}


// 29/12/2022 LC1834-Medium: Single-Threaded CPU
// O(NlogN)xO(N)
vector<int> getOrder(vector<vector<int>>& tasks) {
    int n = tasks.size();
    vector<int> result, idx(n);
    result.reserve(n);
    
    // No input array modification
    iota(idx.begin(), idx.end(), 0);
    
    sort(idx.begin(), idx.end(), [&](int x, int y){ return tasks[x][0] < tasks[y][0]; });
    
    auto cmp = [&tasks](int x, int y){ 
        return tasks[x][1]==tasks[y][1]?x>y:tasks[x][1]>tasks[y][1]; 
    };

    priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);

    long long curTime=tasks[idx[0]][0];
    int i=0;

    while(i<n || !pq.empty()) {
        
        if(pq.empty() && curTime<tasks[idx[i]][0]){
            curTime = tasks[idx[i]][0];
        }
        
        while(i < n && tasks[idx[i]][0]<=curTime){
            pq.push(idx[i]);
            i++;
        }
        
        result.push_back(pq.top());
        curTime+=tasks[pq.top()][1];
        pq.pop();
    };
    return result;
}


void dfs_allPaths(vector<vector<int>>& graph, int s, int d, vector<int> &recSk, vector<vector<int>> &result){
    recSk.push_back(s);
    if(s==d) result.push_back(recSk);

    for(int v:graph[s]){
        dfs_allPaths(graph, v, d, recSk, result);
    }

    recSk.pop_back();
}


// 30/12/2022 LC797: All Paths from source to target
// See how easy it is to think path problems with dfs instead of bfs
// O(n*2^n)xO(n). O(n) space since return value is not counted in space complexity. Only recSk is counted.
// Let every node i is connected j if i<j. For a path of lenth k b/w 0 & n-1 we have k-1 nodes
// in between which can be chosen from n-2 nodes. i.e n-2Ck-1. Now k=1 to n-2 i.e summation => 2^n-2 paths.
// And each path length is O(n) => O(n*2^n) time. Why not permutation? Because it's directed & acyclic.
// O(n*2^n) nodes in all paths is the size of result. why? basically 2^n-2 is #of subsets. Each subset
// and it's complement has n-2 nodes combined.
vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
    vector<vector<int>> result;
    vector<int> recSk;

    dfs_allPaths(graph, 0, graph.size()-1, recSk, result);
    return result;
}


int uniquePathsIII(vector<vector<int>>& grid, int i, int j, int empty){
    if(i<0 || i>=grid.size() || j<0 || j>=grid[0].size()) return 0;
    if(grid[i][j]==2 && empty==0) return 1;
    if(grid[i][j]!=0) return 0;
    grid[i][j]=-1;
    empty--;
    int result = uniquePathsIII(grid, i+1, j, empty) +
                    uniquePathsIII(grid, i-1, j, empty) +
                    uniquePathsIII(grid, i, j+1, empty) +
                    uniquePathsIII(grid, i, j-1, empty);
    grid[i][j]=0;
    empty++;
    return result;
}


// 31/12/2022 LC980-Hard: Unique Paths III
// O(3^N)xO(N): Each node (except for start) will have three possibilities, O(N) for DFS stack. 
// Where N is # empty cells i.e 0s.
int uniquePathsIII(vector<vector<int>>& grid) {
    int empty=0, start_i=0, start_j=0;
    for(int i=0;i<grid.size();i++){
        for(int j=0;j<grid[0].size();j++){
            if(grid[i][j]==1){
                start_i=i;
                start_j=j;
                grid[i][j]=0;
            }
            // increment for grid[i][j]=0;
            if(grid[i][j]==0) empty++;
        }
    }

    // you can reset grid[start_i][start_j]=1 if you don't want to keep input intact after this.
    return uniquePathsIII(grid, start_i, start_j, empty);
}


int main(int argc, char const *argv[])
{
    //cout << closeStrings("cabbba", "abbccc")<<endl;   
    
    vector<int> v = {10,5,15,3,7,18};
    // TreeNode* root = makeBST(v);
    // cout << rangeSumBST(root, 7, 15) << endl;
    // cout << maxAncestorDiff(root)<<endl;
    // cout << minimumAverageDifference(v)<<endl;
    
    // int m, n;
    // cin >> m >> n;
    // cout <<uniquePaths(m, n)<<endl;
    // cout << longestCommonSubsequence_r("abcde", "ace")<< endl;
    // vector<vector<int>> edges = {{0,1},{0,2},{2,3},{2,4},{2,5}};
    // printContainer(sumOfDistancesInTree(6, edges));

    vector<int> prices = {1,2,3,0,2};
    // cout << maxProfit(prices);

    // vector<vector<int>> tasks = {{19,13},{16,9},{21,10},{32,25},{37,4},{49,24},{2,15},{38,41},{37,34},{33,6},{45,4},{18,18},{46,39},{12,24}};
    // printContainer(getOrder(tasks));

    vector<vector<int>> grid = {{1,0,0,0},{0,0,0,0},{0,0,2,-1}};
    cout << uniquePathsIII(grid) << endl;
    return 0;
}
