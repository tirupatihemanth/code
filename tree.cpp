#include<bits/stdc++.h>
#define f(i,n) for(int i=0; i<n; i++)

using namespace std;


struct Node{
    int data;
    Node* left, *right;

    Node(int data):data(data), left(nullptr), right(nullptr){

    }
};

// Tree traversals
void inorder(Node* root){
    if(!root)return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// as long as there is left subtree store it in stack.
// Now for each element in stack process it and it's right sub tree.
// theta(n)xO(h)
void inorder_iter(Node* root){
    if(!root)return;
    stack<Node*> stack;
    Node *cur = root;
    while(cur!=nullptr || !stack.empty()){
        if(cur){
            stack.push(cur);
            cur = cur->left;
            continue;
        }
        Node *top = stack.top();
        cout << top->data << " ";
        stack.pop();
        cur = top->right; 
    }
}


void preorder(Node* root){
    if(!root)return;
    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}

void preorder_iter(Node* root){
    if(!root) return;
    Node* cur=root;
    stack<Node*> stack;

    while(cur!=nullptr || !stack.empty()){
        while(cur){
            stack.push(cur);
            cout << cur->data << " ";
            cur = cur->left;
        }

        Node* top = stack.top();
        stack.pop();
        cur = top->right;
    }
}

void preorder_iter2(Node* root){
    if(!root) return;
    stack<Node*> stack;
    Node* cur = root;
    while(cur || !stack.empty()){
        if(cur){
            cout<<cur->data<<" ";
            if(cur->right) stack.push(cur->right);
            cur = cur->left;
            continue;
        }
        if(!stack.empty()){
            cur = stack.top();
            stack.pop();
        }
        
    }
}

void preorder_iter3(Node* root){
    if(!root) return;
    stack<Node*> stack;
    stack.push(root);
    while(!stack.empty()){
        Node* top = stack.top();
        cout << top->data << " ";
        stack.pop();
        if(top->right) stack.push(top->right);
        if(top->left) stack.push(top->left);
    }
}

void postorder(Node* root){
    if(!root)return;
    postorder(root->left);
    postorder(root->right);
    cout<<root->data<<" ";
}

// O(n)xO(n) using queue or theta(n) x theta(w) where w is width of BT. 
// O(nh)xO(h) using distance_k & height loop from [0, h-1]
void bft(Node* root){
    if(!root)return;
    queue<Node*> q;
    q.push(root);

    while(!q.empty()){
        Node* front = q.front();
        q.pop();
        cout << front->data<<" ";
        if(front->left)q.push(front->left);
        if(front->right)q.push(front->right);
    }
}

// Vertical Order Traversal with a DFT. DFT cannot be used as vertical order 
// from top to bottom (level wise) will not be maintained within a level.

/* 
In this case 12 printed before 9 b/o preorder traversal. You can store map<int, map<int, int>> while 
first map is based on hd and second map is (..., int height=1) which is passed as another param in dfs function
             1
          /     \
         2       3
        /  \    /  \
       4    5  6    7
                \  /  \
                 8 10  9 
                     \
                     11
                       \
                        12 

 */

//O(nlogn) since mp insert is logn
 void vot(Node* root, map<int, vector<int>>& mp, int hd=0){
    if(!root) return;
    mp[hd].push_back(root->data);
    vot(root->left, mp, hd-1);
    vot(root->right, mp, hd+1);
}

//VOT with bft ensure correct order within vertical levels i.e from top to bottom
// O(n^2) solution is finding min_hd, max_hd then iterating for each and printing nodes at that level

/* 
This is O(n). O(nlogn) if you use map & not maintain min_hd & max_hd. 
then using vector<int, vector<int>> of size max_hd-min_hd+1 to store the values
Can also be done in O(1) by using unordered_map if it's okay to print any vertical level first. or can 
First find min&max hd then use hashmap to print vertical levels in order from left to right.
 */

void vot_bft(Node* root){
    if(!root)return;
    // map<int, vector<int>> mp;
    unordered_map<int, vector<int>> mp;
    queue<pair<Node*, int>> q;
    int hd=0, min_hd=INT_MAX, max_hd=INT_MIN;
    q.emplace(root, hd);

    while(!q.empty()){
        auto p = q.front();
        q.pop();
        hd = p.second;
        min_hd = min(min_hd, hd);
        max_hd = max(max_hd, hd);
        mp[hd].push_back(p.first->data);
        if(p.first->left)q.emplace(p.first->left, hd-1);
        if(p.first->right)q.emplace(p.first->right, hd+1);
    }
    for(int i=min_hd; i<=max_hd;i++){
        f(j,mp[i].size()) cout << mp[i][j] <<" ";
        cout << endl;
    }
}

int HD(Node* root, Node* node, int hd=0){
    if(!root) return INT_MIN;
    if(root==node) return hd;
    return max(HD(root->left, node, hd-1), HD(root->right, node, hd+1));
}
//Views

//bft using nullptr to demarkate levels within queue.
void left_view(Node* root){
    if(!root)return;
    queue<Node*> q;
    q.push(nullptr); //for right view push nullptr after root. AFter every pop push children and check if front is nullptr then print curr front
    q.push(root); // for left view also you can push nullptr after root. Bust have to use bool first_node set to true at every nullptr and false after printing any element i.e first element of a level.

    while(!q.empty()){
        if(q.size()==1 && q.front()==nullptr) break;
        if(q.front()==nullptr){
            q.pop();
            q.push(nullptr);
            cout <<q.front()->data<<" ";
        }
        Node* front = q.front();
        q.pop();
        if(front->left)q.push(front->left);
        if(front->right)q.push(front->right);
    }
}

// Print first node at higher level not encountered before
// recur left first to print left view, right first to print right view
void left_view_r(Node* root, int cur_level=1){
    if(!root) return;
    static int max_level = INT_MIN;
    if(cur_level>max_level){
        cout << root->data<<" ";
        max_level=cur_level;
    }
    left_view_r(root->left, cur_level+1);
    left_view_r(root->right, cur_level+1);
}

//bft.
void right_view(Node* root){
    if(!root)return;
    queue<Node*> q;
    q.push(root);
    while(!q.empty()){
        int n = q.size(); // No. of elements at cur_level. Print first for left view, last for right view.
        while(n--){
            Node* front = q.front();
            q.pop();
            if(n==0){
                cout << front->data<<" ";
            }
            if(front->left)q.push(front->left);
            if(front->right)q.push(front->right);
        }
    }
}

/* 
just print the store first node per hd in vot using hashmap.
top_view & bottom_view can be done using bft/dft in O(n).
BFT: top_view don't update hashmap once inserted. bottom_view always update hashmap so you get bottom node in VOT.
DFT: Also need to keep track of height in the map. If current height > height in map for a given hd then update for 
bottom view for top view update if current height < height in map.
 */

// O(n) bft.
void top_view(Node* root){
    if(!root)return;
    queue<pair<Node*, int>> q; //keep track of hd
    unordered_map<int, int> mp;
    int hd=0, min_hd=INT_MAX, max_hd=INT_MIN;
    q.emplace(root, hd);
    while(!q.empty()){
        auto p = q.front();
        q.pop();
        hd = p.second;
        min_hd=min(min_hd, hd);
        max_hd=max(max_hd, hd);
        if(mp.find(hd)==mp.end()){
            mp[hd]=p.first->data;
        }
        if(p.first->left) q.emplace(p.first->left, hd-1);
        if(p.first->right) q.emplace(p.first->right, hd+1);
    }
    for(int i=min_hd; i<=max_hd; i++){
        cout << mp[i]<<" ";
    }
    cout << endl;
}

//O(n) with dft/preorder traversal. Can be done with bft also
void bottom_view(Node* root, unordered_map<int, pair<int, int>> &mp, int &min_hd, int &max_hd, int height=1, int hd=0){
    if(!root)return;
    min_hd = min(min_hd, hd);
    max_hd = max(max_hd, hd);
    if(!mp.emplace(hd, make_pair(root->data, height)).second){
        if(mp[hd].second < height){
            mp[hd].first = root->data;
            mp[hd].second = height;
        }
    }

    bottom_view(root->left, mp, min_hd, max_hd, height+1, hd-1);
    bottom_view(root->right, mp, min_hd, max_hd, height+1, hd+1);
}


void mirror(Node* root){
    if(!root)return;
    swap(root->left, root->right);
    mirror(root->left);
    mirror(root->right);
}

void dll(Node* root, Node** prev=new Node*(nullptr)){
    if(!root) return;
    dll(root->left, prev);
    root->left = *prev;
    if(*prev){   
        (*prev)->right = root;
    }
    *prev = root;
    dll(root->right, prev);
}

void dll_clean(Node* root, Node** head){
    if(!root) return;
    static Node* prev=nullptr;
    dll_clean(root->left, head);

    if (prev)
    {
        root->left=prev;
        prev->right=root;
    }
    else
    {
        *head=root;
        root->left=nullptr;
    }
    prev=root;
    dll_clean(root->right, head);
}

void print_dll(Node* head){
    while(head){
        cout<<head->data<<" ";
        head = head->right;
    }
}

// O(n)xO(h)
int height(Node* root){
    if(!root)return 0;
    return max(height(root->left), height(root->right))+1;
}

// O(n)xO(h)
void distance_k(Node* root, int k){
    if(!root) return;
    if(!k){
        cout << root->data << " ";
        return;
    }

    distance_k(root->left, k-1);
    distance_k(root->right, k-1);
}

// O(n) x O(h)
// O(n) x O(w) iterative with queue
int size(Node* root){
    if(!root) return 0;
    return size(root->left)+size(root->right)+1;
}

// O(n)xO(h)
// O(n)xO(w) if using queue & iterative sol. Thus if tree is skewed i.e w is less use iterative, if perfect then use recursive.
int max(Node* root){
    if(!root) return INT_MIN;
    return std::max({max(root->left), max(root->right), root->data});
}

bool find_path(Node* root, int data, vector<int>& path){
    if(!root) return false;
    path.push_back(root->data);
    if(root->data==data) return true;
    if(!find_path(root->left, data, path) && !find_path(root->right, data, path)){
        path.pop_back();
        return false;
    }
    else return true;
}

// O(n)xO(n). Multiple traversals
int lca(Node* root, int data1, int data2){
    if(!root) return INT_MAX;
    vector<int> path1, path2;
    find_path(root, data1, path1);
    find_path(root, data2, path2);

    int lca=-1;
    f(i,min(path1.size(), path2.size())){
        if(path1[i]==path2[i]){
            lca=i;
        }
        else break;
    }
    if(lca==-1) return -1;
    return path1[lca];
}

// Assume both data1, data2 are in the tree. If only one is there then you get that value
// O(n)xO(n). More precisely O(n) x theta(h) Single traversal. No need to store path arrays.
int lca2(Node* root, int data1, int data2){
    if(!root) return -1;
    if(root->data==data1 || root->data == data2) return root->data;
    int left = lca2(root->left, data1, data2);
    int right = lca2(root->right, data1, data2);
    
    if(left>=0 && right>=0) return root->data;
    else if(left < 0) return right;
    else return left;
}

// O(N^2) - since diameter = left + right heights + 1 Hence height (which is O(N)) is 
// calculated for each node. Diameter Aka width of a tree. 
int diameter(Node* root){
    if(!root) return 0;
    int cur_diameter = height(root->left) + height(root->right) + 1;
    return max({cur_diameter, diameter(root->left), diameter(root->right)});
}

//Simultaneously calculating height & diameter instead of calling height() again & again for each node.
//height as pointer because we return diameter and when coming back in recursion call stack we update
//parent height local variable by passing address as arg and updating using this pointer
// O(N)
int diameter(Node* root, int *height){
    //heights of left & right childs
    int lh=0, rh=0;
    if(!root){
        return 0;
    }
    int ld = diameter(root->left, &lh);
    int rd = diameter(root->right, &rh);

    *height = 1 + max(lh, rh);
    return max({lh+rh+1, ld, rd});
}

// O(N). height function modified for diameter. We are accumulating diameter value (unlike above) 
// hence no need pointer just reference is enough.

int height_diameter(Node* root, int &diameter){
    if(!root) return 0;
    int lh = height_diameter(root->left, diameter);
    int rh = height_diameter(root->right, diameter);

    diameter = max(lh+rh+1, diameter);
    return 1 + max(lh, rh);
}

int main(int argc, char const *argv[])
{
    Node *root=nullptr;

    //Build Tree
    root = new Node(10);
    root->left = new Node(20);
    root->right = new Node(30);
    root->left->left = new Node(15);
    root->left->right = new Node(25);
    root ->right->right = new Node(40);
    root ->right->right->right = new Node(50);


    inorder(root);
    cout << endl;
    inorder_iter(root);
    cout << endl;

    preorder(root);
    cout << endl;
    preorder_iter(root);
    cout << endl;
    preorder_iter2(root);
    cout << endl;
    preorder_iter3(root);
    cout << endl;

    postorder(root);
    cout << endl;
    cout << height(root)<<endl;
    distance_k(root, 1);
    cout << endl;
    bft(root);
    cout << endl;
    cout << size(root)<<endl;

    cout << max(root)<<endl;

    cout << lca2(root, 30, 40)<<endl;

    cout << diameter(root)<<endl;

    cout << diameter(root, new int)<<endl;
    int diameter = INT_MIN;
    height_diameter(root, diameter);
    cout << diameter<<endl;
    cout <<"Views"<<endl;
    top_view(root);
    cout << endl;

    left_view(root);
    cout << endl;
    left_view_r(root);
    cout << endl;

    right_view(root);
    cout << endl;

    cout <<"Bottom View"<<endl;
    unordered_map<int, pair<int, int>> mp;
    int min_hd=INT_MAX, max_hd=INT_MIN;
    bottom_view(root, mp, min_hd, max_hd);
    for(int i=min_hd; i<=max_hd; i++){
        cout << mp[i].first<<" ";
    }
    cout << endl;
    
    cout << HD(root, root->right->right->right)<<endl;
    /* map<int, vector<int>> mp;
    vot(root, mp);
    for(auto v:mp){
        f(i,v.second.size()){
            cout <<v.second[i]<<" ";
        }
        cout<<endl;
    }
    cout << endl; */

    vot_bft(root);
    // mirror(root);
    // inorder(root);

    /* dll(root);
    while(root->left){
        root = root->left;
    }
    print_dll(root); */

    //!!!!!! Mutating function. root no longer represent a tree.
    Node* dll_head;
    dll_clean(root, &dll_head);
    print_dll(dll_head);
    return 0;
}
