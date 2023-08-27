#include "leetcode.h"

using namespace std;


/*  CTCI CH2 - Linked Lists */


// 21/06/2023 2.1: Remove Dups
// O(n)xO(n)
// O(n^2)xO(1) If no buffer allowed. We use runner pointer to iterate & remove remaining dup elements
void removeDups(ListNode *head){
    unordered_set<int> ust;
    ListNode *cur = head, *prev = nullptr;
    while(cur){
        if(ust.count(cur->val)){
            prev->next = cur->next;
            delete cur;
            cur = prev->next;
            continue;
        }
        ust.insert(cur->val);
        prev = cur;
        cur = cur->next;
    }
}


// 21/06/2023 2.2: Return Kth Last Node
// O(n)xO(1). 1 Iteration.
// If k=1 returns the last element
ListNode* kThLastNode(ListNode *head, int k){
    if(k<=0) return nullptr;

    ListNode *last = head, *kTh = head;
    for(int i=0;i<k;i++){
        if(!last) return nullptr; // Less than K elements in the LL
        last = last->next;
    }

    
    while(last){
        last = last->next;
        kTh = kTh->next;
    }

    return kTh;
}


// 21/06/2023 2.2: Return Kth Last Node
// O(n)xO(n) recursive. O(n) call stack space
ListNode* kThLastNode_alt(ListNode *head, int &k){
    if(!head) return nullptr;
    ListNode* result = kThLastNode_alt(head->next, k);

    if(result) return result;
    else if(k==1) return head;
    k--;
    return nullptr;
}



// 22/06/2023 2.3: Delete Middle Node
// Delete the non-extreme node given that node
// O(1)xO(1)
void deleteMiddleNode(ListNode *middle){
    if(!middle || !middle->next) return;
    
    ListNode* next = middle->next;
    middle->val = next->val;
    middle->next = next->next;
    delete next;
}


// 22/06/2023 2.4: Partition
// quicksort style partition algo -> Order not preserved
// O(n)xO(1). Not Stable. Alt: insert at head for less and and tail for >=. Initially both set to given head.
ListNode *partition(ListNode *head, int x){
    ListNode *part = head, *iter = head;

    while(iter){
        if(iter->val<x){
            swap(part->val, iter->val);
            part = part->next;
        }
        iter = iter->next;
    }
    return head;
}


// O(n)xO(1) Stable.
ListNode *partition_alt(ListNode *head, int x){

    // dummy nodes to reduce null checks
    ListNode *less = new ListNode(), *greatEq = new ListNode();
    ListNode *lessHead = less, *greatEqHead = greatEq;

    while(head){
        if(head->val<x){
            less->next = head;
            less = less->next;
        }
        else{
            greatEq->next = head;
            greatEq = greatEq->next;
        }
        head = head->next;
    }

    less->next = greatEqHead->next;
    greatEq->next = nullptr;
    delete greatEqHead;
    head = lessHead->next;
    delete lessHead;
    return head;
}


// 28/06/2023 2.5: Sum Lists I
// O(N1+N2)xO(1). Head of the lists have lowest signficant digits
ListNode* sumLists(ListNode *head1, ListNode *head2){
    ListNode *result = new ListNode(), *iter = result;
    bool carry=false;
    while(head1 || head2 || carry){

        int val = carry;
        if(head1){
            val += head1->val;
            head1 = head1->next;
        }

        if(head2){
            val+=head2->val;
            head2 = head2->next;
        }

        iter->next = new ListNode(val%10);
        iter = iter->next;
        carry = val>=10;
    }

    iter = result;
    result = result ->next;
    delete iter;
    return result;
}


// 28/06/2023 2.5: Sum Lists II
// O(N1+N2)xO(1). Reverse both lists in O(N1+N2)xO(1) and then do as Sum Lists I
// O(N1+N2)xO(max(N1, N2)). Recursive or Using stack to first push all digits & compute sum while popping
ListNode* sumListsII(ListNode *head1, ListNode *head2){
    
}


int main(int argc, char const *argv[]){
    
    
    ListNode *head = makeList({3, 5, 8, 5, 10, 2, 1});

    // removeDups(head);
    // printList(head);

    // cout << kThLastNode(head, 1)->val << endl;
    // int k = 1;
    // cout << kThLastNode_alt(head, k)->val << endl;

    // deleteMiddleNode(head->next->next);
    // printList(head);

    // printList(partition(head, 5));
    printList(partition_alt(head, 5));
    return 0;
}