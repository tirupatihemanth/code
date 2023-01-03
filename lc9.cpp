#include<bits/stdc++.h>
#include "leetcode.h"
using namespace std;

/* TREE */
/* NEETCODE.IO */

// 29/12/2022 LC226-Easy: Invert Binary Tree
// O(n)xO(n)
TreeNode* invertTree(TreeNode* root) {
    if(!root) return root;
    swap(root->left, root->right);
    invertTree(root->left);
    invertTree(root->right);
    return root;
}


// 29/12/2022 LC226-Easy: Invert Binary Tree
// Preorder traversal (if we push right first though)
// O(n)xO(n) but uses stack data structure (heap memory) instead of application call stack which could overflow easily
TreeNode* invertTree_dfs_i(TreeNode* root) {
    if(!root) return root;
    stack<TreeNode*> sk;
    sk.push(root);
    while(sk.size()){
        auto top = sk.top();
        sk.pop();
        swap(top->left, top->right);
        if(top->left)sk.push(top->left);
        if(top->right)sk.push(top->right);
    }
    return root;
}


// 29/12/2022 LC226-Easy: Invert Binary Tree
// O(n)xO(n)
TreeNode* invertTree_bfs(TreeNode* root) {
    if(!root) return root;
    queue<TreeNode*> q;
    q.push(root);
    while(q.size()){
        auto front = q.front();
        q.pop();
        swap(front->left, front->right);
        if(front->left) q.push(front->left);
        if(front->right) q.push(front->right);
    }
    return root;
}


// 29/12/2022 LC104: Maximum Depth of Binary Tree
// O(n)xO(n)
int maxDepth(TreeNode* root) {
    if(!root) return 0;
    return 1+max(maxDepth(root->left), maxDepth(root->right));
}


// 29/12/2022 LC104: Maximum Depth of Binary Tree
// O(n)xO(n) Pre-order traversal (if we push right first though)
int maxDepth_dfs_i(TreeNode* root) {
    if(!root) return 0;

    stack<pair<TreeNode*, int>> sk;
    sk.emplace(root, 1);
    int maxDepth=1;
    
    while(sk.size()){
        auto [node, depth] = sk.top();
        sk.pop();
        maxDepth = max(maxDepth, depth);
        if(node->left) sk.emplace(node->left, depth+1);
        if(node->right) sk.emplace(node->right, depth+1);
    }

    return maxDepth;
}


// 29/12/2022 LC104: Maximum Depth of Binary Tree
// O(n)xO(n)
int maxDepth_bfs(TreeNode* root) {
    if(!root) return 0;

    queue<TreeNode*> q;
    q.push(root);
    int height=0;
    
    while(q.size()){
        int level_size = q.size();
        while(level_size--){
            auto node = q.front();
            q.pop();
            if(node->left) q.emplace(node->left);
            if(node->right) q.emplace(node->right);    
        }
        height++;
    }

    return height;
}


int diameter_dfs(TreeNode* root, int &diameter){
    if(!root) return 0;
    int lh = diameter_dfs(root->left, diameter);
    int rh = diameter_dfs(root->right, diameter);
    diameter = max(lh+rh, diameter);
    return 1+max(lh, rh);
}

// 29/12/2022 LC543-Easy: Diameter of a binary tree
// O(n)xO(n)
int diameterOfBinaryTree(TreeNode* root) {
    int diameter = 0;
    diameter_dfs(root, diameter);
    return diameter;
}


int isbalanced_dfs(TreeNode* root, bool &isBalanced){
    if(!root || !isBalanced ) return 0;

    int lh = isbalanced_dfs(root->left, isBalanced);
    int rh = isbalanced_dfs(root->right, isBalanced);

    if(abs(lh-rh)>1) isBalanced = false;
    return 1+max(lh, rh);
}


// 29/12/2022 LC110-Easy: Balanced binary tree
// Alt: You can return a pair in dfs function. pair(bool, height);
// O(n)xO(n)
bool isBalanced(TreeNode* root) {
    bool isBalanced = true;
    isbalanced_dfs(root, isBalanced);
    return isBalanced;
}


// 29/12/2022 LC100-Easy: Same Tree
// O(p+q)xmax(O(p), O(q))
bool isSameTree(TreeNode* p, TreeNode* q) {
    if(!p && !q) return true;
    if(!p || !q) return false;

    return p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}


// 29/12/2022 LC572-Easy: Subtree of another tree
// O(mn) where m is #nodes in root and n is #nodes in subroot
bool isSubtree(TreeNode* root, TreeNode* subRoot) {
    if(!subRoot) return true;
    if(!root) return false;
    return isSameTree(root, subRoot) || isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
}


// 29/12/2022 LC235-Medium: LCA of a BST
// O(h)xO(1). where h = logn if balanced.
TreeNode* lowestCommonAncestor_bst(TreeNode* root, TreeNode* p, TreeNode* q) {

    auto cur = root;
    while(cur){
        if(cur->val > max(p->val, q->val)) cur = cur->left;
        else if(cur->val < min(p->val, q->val)) cur = cur->right;

        // Could be on either side or one of the two values could be equal to root->val
        else return cur;
    }
    // Dead code since it is guaranteed that p, q are in the BST.
    return cur;    
}


// returns false if there is no valid path from root to given node
// i.e the given node is not a valid element of the tree
// O(n)xO(n)
bool findPath(TreeNode* root, TreeNode *node, vector<TreeNode*> &path){
    if(!root || !node) return false;
    path.push_back(root);
    bool found = root == node || 
            findPath(root->left, node, path) || 
            findPath(root->right, node, path);
    if(found) return true;
    path.pop_back();
    return false;
    
}


// 29/12/2022 LCA in any binary tree.
// !NEETCODE !LEETCODE
// O(n)xO(n) 2 traversals. Requires storing path also
TreeNode* lowestCommonAncestor_alt(TreeNode* root, TreeNode* p, TreeNode* q) {
    vector<TreeNode*> path1, path2;
    findPath(root, p, path1);
    findPath(root, q, path2);
    int i=1;
    while(i<path1.size() && i<path2.size() && path1[i]==path2[i]){
        i++;
    }

    if(path1.empty() || path2.empty()) return nullptr;
    return path1[i-1];
}


// 29/12/2022 LCA in any binary tree.
// !NEETCODE !LEETCODE
// Used when the p, q are guaranteed to be in the tree.
// O(n)xO(n). 1 traversal. No need to store/find the actual paths from roots.
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(!root) return nullptr;
    if(root == p || root == q) return root;
    
    auto left = lowestCommonAncestor(root->left, p, q);
    auto right = lowestCommonAncestor(root->right, p, q);
    if(left && right) return root;
    if(!left) return right;
    else return left;
}


// 29/12/2022 LC102-Medium: Binary Tree Level Order Traversal
// O(n)xO(n) Uses move semantics to avoid copy into a vector.
vector<vector<int>> levelOrder(TreeNode* root) {
    if(!root) return vector<vector<int>>();
    vector<vector<int>> result;
    queue<TreeNode*> q;
    q.push(root);
    while(int level_size = q.size()){
        vector<int> level_nodes(level_size);
        for(int i=0;i<level_size;i++){
            auto top = q.front();
            q.pop();
            
            // Alt: you can push w/o checking left & right. Then you'll add a check if top!=null then do below 3 ops
            // Also before pushing level_nodes to result you'll push only if it's non-empty since all null nodes for last level
            level_nodes[i] = top->val;
            if(top->left) q.push(top->left);
            if(top->right) q.push(top->right);
        }

        // converts level_nodes i.e lvalue into a rvalue and thus avoids calling a copy constructor & 
        // calls move constructor on vector<int> object. Thus avoid copy. 
        // level_nodes will become unusable but we don't need it anyway
        result.push_back(move(level_nodes));
    }
    return result;
}


// 30/12/2022 LC199-Medium: Binary Tree Right Side View
// O(n)xO(n)
vector<int> rightSideView(TreeNode* root) {
    if(!root) return vector<int>();
    vector<int> result;
    queue<TreeNode*> q;
    q.push(root);
    while(q.size()){
        int level_size = q.size();
        for(int i=0;i<level_size;i++){
            auto front = q.front();
            q.pop();
            if(i==level_size-1) result.push_back(front->val);
            if(front->left) q.push(front->left);
            if(front->right) q.push(front->right);
        }
    }
    return result;
}


void dfs_rightSideView(TreeNode *root, int depth, vector<int> &result){
    if(!root) return;

    // Pushing the first node of the new greatest level into the result.
    // Alt: If you are just printing then instead of result use an int max_level i.e till now and when
    // depth > max_level update it and print the node.
    // Because of visiting right first first node will always be the right most of that level
    // when there is no right node but there is left node in that level not blocked by right node
    // from the right view we insert that.

    if(result.size()==depth){
        result.push_back(root->val);
    }

    // reverse these two to get left view.
    dfs_rightSideView(root->right, depth+1, result);
    dfs_rightSideView(root->left, depth+1, result);
}

// 30/12/2022 LC199-Medium: Binary Tree Right Side View
// O(n)xO(n)
vector<int> rightSideView_dfs(TreeNode* root) {
    if(!root) return vector<int>();
    vector<int> result;
    dfs_rightSideView(root, 0, result);
    return result;
}


int dfs_goodNodes(TreeNode *root, int cur_max){
    if(!root) return 0;
    
    if(root->val<cur_max) 
        return dfs_goodNodes(root->left, cur_max) + dfs_goodNodes(root->right, cur_max);

    return 1 + dfs_goodNodes(root->left, root->val) + dfs_goodNodes(root->right, root->val);
}

// 30/12/2022 LC1448: Count Good Nodes in a Binary Tree
// O(n)xO(n)
int goodNodes(TreeNode* root) {
    if(!root) return 0;
    return dfs_goodNodes(root, root->val);
}

// 30/12/2022 LC1448: Count Good Nodes in a Binary Tree
// O(n)xO(n)
int goodNodes_bfs(TreeNode* root) {
    if(!root) return 0;
    queue<pair<TreeNode*, int>> q;
    q.push({root, root->val});
    int good_nodes=0;
    while(q.size()){
        auto &front = q.front();
        int new_max = front.second;
        if(front.first->val>=front.second){
            good_nodes++;
            new_max = front.first->val;
        }
        if(front.first->left) q.emplace(front.first->left, new_max);
        if(front.first->right) q.emplace(front.first->right, new_max);

        // If you pop immediately after q.front() then pair is destroyed & you are still refererring to it using front.
        q.pop();
    }
    return good_nodes;
}


// 30/12/2022 LC98-Medium: Validate Binary Search Tree
// Alt: Using INT_MIN & INT_MAX is not good practice as root value itself could be INT_MAX/INT_MIN
// Hence use pointers and treat nullptr as -INF/+INF.
// O(n)xO(n)
bool isValidBST(TreeNode* root, TreeNode *minNode = nullptr, TreeNode *maxNode = nullptr) {
    if(!root) return true;
    if(minNode && root->val<=minNode->val || maxNode && root->val>=maxNode->val)
        return false;
    return  isValidBST(root->left, minNode, root) &&
            isValidBST(root->right, root, maxNode);
}


// 30/12/2022 LC98-Medium: Validate Binary Search Tree
// Iterative pre-order traversal using stack with min & max ranges as above.
// O(n)xO(n)
bool isValidBST_i(TreeNode *root){
    if(!root) return true;

    // Fixed sized array of size 3. Alt: You can use three stacks and push/pop simultaneously.
    // Since you have three stack arguments for the above isValidBST function.        
    stack<array<TreeNode*, 3>> sk;
    sk.push({root, nullptr, nullptr});
    
    while(sk.size()){
        auto top = sk.top();
        sk.pop(); // Since top is not a reference we can pop & destroy.
        if(top[1] && top[0]->val<=top[1]->val ||
            top[2] && top[0]->val>=top[2]->val){
                return false;
            }

        // Doesn't matter if pushed right/left. Just to show that I am using a named traversal i.e pre-order.
        if(top[0]->right) sk.push({top[0]->right, top[0], top[2]});
        if(top[0]->left) sk.push({top[0]->left, top[1], top[0]});
    }

    return true;
}


bool isValidBST_alt(TreeNode* root, TreeNode*& prev) {
    if(!root) return true;
    if(!isValidBST_alt(root->left, prev)) return false;
    if(prev && prev->val>=root->val) return false;
    prev = root;
    return isValidBST_alt(root->right, prev);
}

// 30/12/2022 LC98-Medium: Validate Binary Search Tree
// inorder traversal of a BST will print ascending order. So just ensure previous printed < current element
// Or you can set prev as a global variable.
// O(n)xO(n). 
bool isValidBST_alt(TreeNode *root){
    TreeNode* prev = nullptr;
    return isValidBST_alt(root, prev);
}


// 30/12/2022 LC98-Medium: Validate Binary Search Tree
// Iterative inorder traversal using stack
// Cur in iterative inorder traversal represent root of the current subtree we are visiting.
// If it is null you have no subtree & no more nodes to visit at current level so go up a level by popping from stack.
// If that is also empty then no more nodes to travel & we break out of our iterative traversal.
// O(n)xO(n)
bool isValidBST_alt_i(TreeNode *root){
    
    TreeNode* prev = nullptr, *cur = root;

    // We don't need two arg in stack despite isValidBST_alt having two args. Since the second arg
    // is just emulating a global variable b/o persistent reference which here is just replaced with automatic var prev.
    stack<TreeNode*> sk; 
    
    while(cur || sk.size()){
        while(cur){
            sk.push(cur);
            cur = cur->left;
        }
        auto top = sk.top();
        sk.pop();
        if(prev && prev->val>=top->val) return false;
        prev = top;
        cur = top->right;
    }
    
    return true;
}


TreeNode* buildTree(vector<int>& preorder, int &pre_idx, unordered_map<int, int> &iomap, int i, int j){
    if(i>j) return nullptr;

    auto root = new TreeNode(preorder[pre_idx]);
    int io_idx = iomap[preorder[pre_idx]];
    
    pre_idx++;
    root->left = buildTree(preorder, pre_idx, iomap, i, io_idx-1);
    root->right = buildTree(preorder, pre_idx, iomap, io_idx+1, j);
    return root;
}

// 31/12/2022 LC105-Medium: Construct Binary Tree from inorder & preorder traversal;
// Works only when there are unique values in the tree or else can't solve the problem. Consider all 1,1,1,1,1
// But if you store null ptrs also for every non-null node just preorder is enough to construct back a tree.
// Preorder index denotes the root the current subtree between indices i, j in inorder vector.
// We can't construct a BT from just preorder & postorder. 
// Ex: consider a-b-c-d all left childs and a-b-c-d where all are right childs. Same pre & post but diff trees.
// O(n)xO(n). 
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    int pre_idx=0;
    unordered_map<int, int> iomap;
    for(int i=0;i<inorder.size();i++){
        iomap[inorder[i]]=i;
    }
    return buildTree(preorder, pre_idx, iomap, 0, inorder.size()-1);
}


TreeNode* buildTree_po(vector<int>& postorder, int &post_idx, unordered_map<int, int> &iomap, int i, int j){
    if(i>j) return nullptr;

    auto root = new TreeNode(postorder[post_idx]);
    auto io_idx = iomap[postorder[post_idx]];

    post_idx--;
    root->right = buildTree_po(postorder, post_idx, iomap, io_idx+1, j);
    root->left = buildTree_po(postorder, post_idx, iomap, i, io_idx-1);
    return root;
}

// LC106-Medium: Construct Binary Tree from inorder and postorder
// !NEETCODE
// Works only when there are unique values in the tree or else can't solve the problem.
// O(n)xO(n)
TreeNode* buildTree_po(vector<int>& inorder, vector<int>& postorder) {
    unordered_map<int, int> iomap;
    for(int i=0;i<inorder.size();i++){
        iomap[inorder[i]]=i;
    }
    int post_idx=postorder.size()-1; 
    return buildTree_po(postorder, post_idx, iomap, 0, inorder.size()-1);
}


TreeNode* dfs_kthSmallest(TreeNode* root, int &k){
    if(!root) return nullptr;
    auto left = dfs_kthSmallest(root->left, k);
    if(left) return left;
    if(--k==0) return root;
    return dfs_kthSmallest(root->right, k);
}

// 31/12/2022 LC230-Medium: Kth smallest element in a BST
// O(n)xO(n)
int kthSmallest(TreeNode* root, int k) {
    auto result = dfs_kthSmallest(root, k);
    if(!result) return -1;
    return result->val;
}


// 31/12/2022 LC230-Medium: Kth smallest element in a BST
// O(n)xO(n)
int kthSmallest_i(TreeNode* root, int k) {
    stack<TreeNode*> sk;
    auto cur = root;
    int count=0;
    while(cur || sk.size()){
        while(cur){
            sk.push(cur);
            cur = cur->left;
        }
        auto top = sk.top();
        sk.pop();
        if(++count==k){
            return top->val;
        }
        cur = top->right;
    }
    return -1;
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


// 31/12/2022 LC297-Hard: Serialize and Deserialize Binary Tree
// Uses preorder traversal (dfs) with null node info also stored for every non-null node => enough to deserialize
// O(n)xO(n) - Serialize. O(n)xO(n) - Deserialize
class Codec {

    void dfs_serialize(TreeNode* root, ostringstream &oss){
        if(!root){
            oss << "n ";
            return;
        }

        oss << root->val << " ";
        dfs_serialize(root->left, oss);
        dfs_serialize(root->right, oss);
    }

    TreeNode* dfs_deserialize(istringstream &iss){
        string word;
        iss>>word;
        if(word == "n"){
            return nullptr;
        }

        auto root = new TreeNode(stoi(word));
        root->left = dfs_deserialize(iss);
        root->right = dfs_deserialize(iss);
        return root;
    }

public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream oss;
        dfs_serialize(root, oss);
        return oss.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream iss(data);
        return dfs_deserialize(iss);
    }
};


// 31/12/2022 LC297-Hard: Serialize and Deserialize Binary Tree
// Uses BFS. Similar to how leetcode serializes trees. No trailing nulls in serialized string.
// Alt: Simple bfs serialize if you are okay with inserting all null for every leaf node like the preorder solution
// just remove the lastNode part.
// O(n)xO(n) - Serialize. O(n)xO(n) - Deserialize
class Codec_bfs {

public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(!root) return string();
        ostringstream oss;
        
        queue<TreeNode*> q;
        q.push(root);
        TreeNode* lastNode = root;
        
        while(q.size()){
            auto front = q.front();
            q.pop();
            if(front){
                oss << front->val << " ";
                q.push(front->left);
                q.push(front->right);
                if(front->left) lastNode = front->left;
                if(front->right) lastNode = front->right;
            }
            else oss << "n ";
            if(front == lastNode) break;
        }
        return oss.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream iss(data);

        string word;
        iss>>word;
        if(word.empty()) return nullptr;
        
        
        TreeNode* root = new TreeNode(stoi(word));

        queue<TreeNode*> q;
        q.push(root);

        while(q.size()){
            auto front = q.front();
            q.pop();
            if(!(iss>>word)) break;
            if(word!="n"){
                front->left = new TreeNode(stoi(word));
                q.push(front->left);
            }

            if(!(iss>>word)) break;
            if(word!="n"){
                front->right = new TreeNode(stoi(word));
                q.push(front->right);
            }
        }

        return root;
    }
};


int main(int argc, char const *argv[])
{
    Codec codec;

    auto root = codec.deserialize("1 2 2 ");
    cout << codec.serialize(root) << endl;
    return 0;
}