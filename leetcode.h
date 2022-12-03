#include <bits/stdc++.h>
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

template<typename Container>
void printContainer(Container c){
    for(auto &x:c){
        cout << x << " ";
    }
    cout << endl;
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