#include <bits/stdc++.h>
#define f(i,n) for(int i=0;i<n;i++)

using namespace std;

struct Node{
    int data;
    Node* left, * right;
    Node(int data):data(data), left(nullptr), right(nullptr){

    }
};

class minheap{
    int *arr;
    int size, capacity;
    
    public:
    minheap(int capacity):capacity(capacity), size(0){
        arr = new int[capacity];
    }

    minheap(int arr[], int size, int capacity):arr(arr), size(size), capacity(capacity){
        buildHeap();
    }

    //O(n)xO(1) function. Not O(nlogn) do maths/watch gfg video
    void buildHeap(){
        for(int i=(size-2)/2;i>=0;i--){
            heapify(i);
        }
    }

    int parent(int i){
        return (i-1)/2;
    }

    int left(int i){
        return 2*i+1;
    }

    int right(int i){
        return 2*i+2;
    }

    // Assuming only given idx is violating minheap property and no other node.
    // O(logn) x O(1)
    void heapify(int idx){
        while(idx<size){
            int lt = left(idx), rt = right(idx), smallest=idx;
            if(lt<size && arr[lt]<arr[idx]){
                smallest = lt;
            }
            if(rt<size && arr[rt]<arr[smallest]){
                smallest = rt;
            }
            if(smallest==idx) break;
            swap(arr[idx], arr[smallest]);
            idx=smallest; // or call heapify(idx) if recursive impl with appr modifications.
        }
    }

    //similar to insert
    void decreaseKey(int idx, int val){
        arr[idx]=val;
        while(idx>0 && arr[parent(idx)]>val){
            swap(arr[idx], arr[parent(idx)]);
            idx = parent(idx);
        }
    }

    void remove(int idx){
        /* 
        Alt: decreseKey(idx, INT_MIN); extract(); is enough.
         */
        decreaseKey(idx, INT_MIN);
        extract();
    }
    
    // O(logn)
    int extract(){
        if(size==0) return INT_MIN;
        if(size==1){
            size--;
            return arr[0];
        }
        int key = arr[0];
        swap(arr[0], arr[size-1]);
        size--;
        heapify(0);
        return key;
    }

    int top(){
        if(size==0) return INT_MIN;
        return arr[0];
    }

    //O(logn)
    void insert(int key){
        if(size==capacity) return;
        int cur = size;
        while(cur>0){
            if(arr[parent(cur)]<key) break;
            else{
                arr[cur]=arr[parent(cur)];
                cur=parent(cur);                
            }
        }
        arr[cur]=key;
        size++;
    }

    void print(){
        f(i,size) cout <<arr[i]<<" ";
        cout << endl;
    }

    private:
    // Not a function of this DS since used O(n)
    bool search(int key, int node=0){
        if(node>size-1) return false;
        return search(key, left(key)) || search(key, right(key));
    }

};

void inorder(Node *root){
    if(!root)return;
    inorder(root->left);
    cout << root->data<<" ";
    inorder(root->right);
}

//O(h)xO(1). If recursive O(h)xO(h)
bool search(Node *root, int key){
    while(root){
        if(root->data==key) return true;
        else if(root->data>key) root = root->left;
        else root = root->right;
    }
    return false;
}

//O(h) x O(h)
Node* insert(Node *root, int key){
    if(!root) 
        return new Node(key);
    else if(root->data>key) 
        root->left = insert(root->left, key);
    else if(root->data<key) 
        root->right = insert(root->right, key);
    
    return root;
}

// O(h) x O(1)
Node* insert_iter(Node *root, int key){
    Node* new_node = new Node(key);
    if(!root) return new_node;
    Node* cur = root, *parent=nullptr;
    while(cur){
        parent=cur;
        if(cur->data>key){
            cur = cur->left;
        } 
        else if(cur->data<key){
            cur = cur->right;
        }
        else return root;
    }

    if(parent->data<key) parent->right = new_node;
    else parent->left = new_node;
    return root;
}

// Node that is deleted is replaced by closest greater value or closest smaller value. 
// Which is inorder successor or inorder predecessor.
// Here I am always picking closest greater value.
//O(h)xO(h)
Node* remove(Node* root, int key){
    if(!root) return root;
    if(root->data<key){
        root->right = remove(root->right, key);
    }
    else if(root->data>key){
        root->left = remove(root->left, key);
    }
    else{
        if(!root->left){
            Node* temp = root->right;
            delete root;
            return temp;
        }
        if(!root->right){
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* cur=root;
        cur=cur->right;
        while(cur->left){
            cur = cur->left;
        }
        root->data = cur->data;
        root->right=remove(root->right, cur->data);
    }
    return root;
}

Node* remove_iter(Node *root, int key){
    if(!root)return root;
    if(root->data==key && !root->left && !root->right){
        delete root;
        return nullptr;
    }

    Node* cur = root, *parent;
    while(cur){
        parent=cur;
        if(cur->data>key){
            cur = cur->left;
        }
        else if(cur->data<key){
            cur = cur->right;
        }
        else break;
    }

    Node* del_node = cur;
    
    if(!cur->left){
        if(parent->left==cur){
            parent->left = cur->right;
        }
        else{
            parent->right = cur->right;
        }
        delete cur;
    }
    else if(!cur->right){
        if(parent->left==cur){
            parent->left==cur->left;
        }
        else{
            parent->right==cur->left;
        }
        delete cur;
    }
    else{
        parent = cur;
        cur = cur->right;
        while(cur->left){
            parent=cur;
            cur = cur->left;
        }
        del_node->data = cur->data;
        if(parent->right==cur){
            parent->right = cur->right;
        }
        else{
            parent->left = cur->right;
        }
        delete cur;
    }
    return root;
}

//O(h)xO(h)
int floor(Node *root, int key){
    if(!root)return INT_MIN;
    if(root->data==key) return key;
    else if(root->data<key){
        return max(root->data, floor(root->right, key));
    }
    else{
        return floor(root->left, key);
    }
}

//O(h)xO(1)
int floor_iter(Node *root, int key){
    int flr=INT_MIN;
    while(root){
        if(root->data==key){
            return key;
        }
        else if(root->data<key){
            flr = root->data;
            root = root->right;
        }
        else{
            root = root->left;
        }
    }
    return flr;
}

//Naive is O(n) i.e do inorder/preorder/postorder and get the ceil.
//O(h)xO(1)
int ceil(Node *root, int key){
    int ceil=INT_MAX;
    while(root){
        if(root->data==key) return key;
        else if(root->data>key){
            ceil = root->data;
            root = root->left;
        }
        else{
            root = root->right;
        }
    }
    return ceil;
}

int lca(Node* root, int data1, int data2){
    if(!root) return INT_MIN;

    if(root->data < min(data1, data2)){
        return lca(root->right, data1, data2);
    }
    else if(root->data > max(data1, data2)){
        return lca(root->left, data1, data2);
    }
    else{
        return root->data;
    }
}

int lca_iter(Node* root, int data1, int data2){
    
    while(root){
        if(root->data < min(data1, data2)) root = root->right;
        else if(root->data > max(data1, data2)) root = root->left;
        else return root->data;
    }
    return INT_MIN;
}

/* 
Sample Input BST
9
15 20 80 18 16 17 3 5 4

 */
int main(int argc, char const *argv[])
{
    Node *bst=nullptr;
    int n;
    cin >> n;
    int arr[n];
    f(i,n){
        cin >> arr[i];
    }
    
    minheap mhp(arr, n, 30);
    mhp.buildHeap();
    f(i,n) cout <<arr[i]<<" ";
    cout << "\nBUild Heap Done\n";

    mhp.print();
    // mhp.insert(9);
    mhp.print();
    mhp.decreaseKey(3, 14);
    // cout <<mhp.extract()<<endl;
    mhp.print();
    /* 
    f(i,n){
        int temp;
        cin >> temp;
        bst = insert_iter(bst, temp);
    } 

    inorder(bst);
    cout << endl;
    cout << search(bst, 20)<<endl;

    //bst = remove_iter(bst, 15);
     // bst = remove(bst, 15);
    inorder(bst);
    cout<<endl;

    cout << floor(bst, 19)<<endl;
    cout << floor_iter(bst, 19)<<endl;
    cout << ceil(bst, 6)<<endl;

    cout << lca(bst, 4, 3)<<endl;
    cout << lca_iter(bst, 18, 80)<<endl;
    */
    return 0;
}

