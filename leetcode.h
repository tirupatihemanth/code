#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <forward_list>
#include <list>
#include <string>
#include <sstream>
#include <string_view>
#include <numeric>

#define f(i,n) for(int i=0;i<n;i++)
#define lli long long int
#define ulli unsigned long long int

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/*
class Node {
public:
    int val;
    Node* next;
    Node* random;
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

template<typename Container>
void printContainer(Container c){
    for(auto &x:c){
        cout << x << " ";
    }
    cout << endl;
}


template<typename T>
void printMatrix(vector<vector<T>> &mat){
    for(auto &r:mat){
        for(auto &elem:r){
            cout << elem << " ";
        }
        cout << endl;
    }
}


ListNode* reverseList(ListNode* head) {
    if(!head) return head;
    ListNode *cur=head, *next=nullptr, *prev=nullptr;

    while(cur){
        next = cur->next;
        cur->next = prev;
        prev=cur;
        cur=next;   
    }

    return prev;
}

void printList(ListNode *head){
    while(head){
        cout << head->val<<" ";
        head = head->next;
    }
    cout << endl;
}

ListNode* makeList(vector<int> vals){
    ListNode *head = new ListNode, *cur = head;
    for(int x:vals){
        cur->next = new ListNode;
        cur->next->val = x;
        cur = cur->next;
    }
    ListNode *temp = head;
    head = head->next;
    delete temp;
    return head;
}

TreeNode* makeBST(vector<int> vals){
    if(!vals.size()) return nullptr;
    TreeNode* root = new TreeNode(vals[0]);
    for(int i=1;i<vals.size();i++){
        TreeNode* cur = root, *parent;
        while(cur){
            parent = cur;
            if(cur->val>vals[i]) cur = cur->left;
            else cur = cur->right;
        }
        if(parent->val>vals[i]) parent->left = new TreeNode(vals[i]);
        else parent->right = new TreeNode(vals[i]);
    }

    return root;
}