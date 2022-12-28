#include<bits/stdc++.h>
#include "leetcode.h"
using namespace std;

/* LINKED LIST */
/* NEETCODE.IO */


// 30/11/2022 LC206-Easy Reverse Linked List
// 2 pointer approach => Default
// O(n)xO(1)
ListNode* reverseList_2p(ListNode *head){
        ListNode *cur = head, *prev=nullptr;
        while(cur){
            /* auto next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next; */
            swap(cur->next, prev);
            swap(prev, cur);
        }
        return prev;
}

// 27/11/2022 LC206-Easy
// 3 pointer iterative. Don't read this
// O(n)xO(1)
ListNode* reverseList_3P(ListNode* head) {
    ListNode *cur=head, *next=nullptr, *prev=nullptr;

    while(cur){
        next = cur->next;
        cur->next = prev;
        prev=cur;
        cur=next;
    }

    return prev;
}

// 27/11/2022 LC206-Easy
// O(n)xO(n) => Since tailRecur compiler optimized call stack
ListNode* reverseList_tailRecur(ListNode* head, ListNode *prev=nullptr){
    if(!head) return prev;
    ListNode* next = head->next;
    head->next = prev;
    return reverseList_tailRecur(next, head);
}

// 27/11/2022 LC206-Easy
// O(n)xO(n)
ListNode* reverseList_recur(ListNode* head){
    if(!head || !head->next) return head;
    ListNode* new_head = reverseList_recur(head->next);
    head->next->next=head;
    head->next=nullptr;
    return new_head;
}


// 28/11/2022 LC21-Easy: Merge two sorted lists
// Iterative with very little if-else b/o temp head.
// O(m+n)xO(1)
ListNode* mergeTwoLists(ListNode* list1, ListNode *list2){
    //This temp result node helps avoid lot of if(result) statements.
    ListNode* result = new ListNode;
    ListNode* tail = result;
    while(list1 && list2){
        if(list1->val<list2->val){
            tail = tail->next = list1;
            list1=list1->next;
        }
        else{
            tail = tail->next = list2;
            list2 = list2->next;
        }
    }

    if(list1) tail->next = list1;
    else tail->next = list2;

    tail = result;
    result = result->next;
    delete tail;
    return result;
}

// 28/11/2022 LC21-Easy: Merge two sorted lists
// O(m+n)xO(m+n)
ListNode* mergeTwoLists_recur(ListNode* list1, ListNode *list2){
    if(!list1) return list2;
    if(!list2) return list1;

    if(list1->val<list2->val){
        list1->next = mergeTwoLists_recur(list1->next, list2);
        return list1;
    }
    list2->next = mergeTwoLists_recur(list1, list2->next);
    return list2;

}


// 02/12/2022 LC143-Medium: Reorder List
// 3 STEP: Find middle. reverse second half. Interweave two lists.
// O(N)xO(1)
ListNode* reorderList(ListNode* head){

    if(!head || !head->next) return head;
    // Find middle of the linked list
    auto slow = head, fast = head;
    while(fast->next && fast->next->next){
        slow = slow->next;
        fast = fast->next->next;
    }


    // reverse second half of the LL i.e from slow.
    // 1->2->3->4->5 to 1->2->3 and 5->4

    ListNode* cur = slow->next;
    slow->next = nullptr;
    ListNode *prev = nullptr;

    while(cur){
        auto next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    auto head2 = prev;
    auto head1 = head;

    // Interweave two LL
    // In odd case head2 will have two elements i.e less than head1 with 3 elements
    while(head2){
        auto temp = head1->next;
        head1->next = head2;
        head2 = head2->next;
        head1->next->next = temp;
        head1 = temp;
    }

    return head;
}


ListNode* reorderList_r(ListNode* cur, ListNode *head){
    if(!cur) return head;
    auto curHead = reorderList_r(cur->next, head);
    if(!curHead) return nullptr;
    if(curHead==cur || curHead->next==cur){
        return cur->next=nullptr;
    }
    cur->next = curHead->next;
    curHead->next = cur;
    return cur->next; // Next element from the start
}

// 13/12/2022 LC143-Medium: Reorder List
// Recursive - keep forward head as param and reorder once you hit bottom of dfs.
// O(n)xO(n) b/o stackspace during dfs.
ListNode* reorderList_r(ListNode* head){
    reorderList_r(head, head);
    return head;
}


// 02/12/2022 LC143-Medium: Reorder List
// Using stack to store the second half instead of reversing.
// Alt: You canjust store all nodes in an array. take start & end pointers & interweave.
// 3 step: Finding Middle. Storing second half in stack. Interweave list & stack.
// O(N)xO(N)
ListNode* reorderList_iter(ListNode* head) {
    if(!head || !head->next) return head;
    stack<ListNode*> sk;
    ListNode *cur = head, *fast=head;

    //while(fast && fast->next)
    //Gets cur to n/2+1 element if n/2 is even
    // n/2 and n/2+1 are mids if n is even.
    // n/2+1 is mid if n is odd.

    //fast->next && fast->next->next
    // Gets cur to n/2 if n is even. ceil(n/2) i.e n/2+1 if n is odd.
    while(fast->next && fast->next->next){
        cur=cur->next;
        fast = fast->next->next;
    }

    while(cur->next){
        sk.push(cur->next);
        cur = cur->next;
    }

    cur=head;
    while(!sk.empty()){
        sk.top()->next = cur->next;
        cur->next = sk.top();
        sk.pop();
        cur=cur->next->next;
    }
    cur->next=nullptr;
    return head;
}


// 27/12/2022 LC19-Medium: Remove Nth node from the end of the list
// O(n)xO(1). One pass. Two pointer technique.
ListNode* removeNthFromEnd(ListNode* head, int n) {
    auto dummy = new ListNode;
    dummy->next = head;

    auto left = dummy, right = dummy;

    // Shift right pointer n times.
    // Now left will point to just before nth element from the end when right reaches last element
    while(n-->0)
        right = right->next;

    while(right->next){
        left = left->next;
        right = right->next;
    }

    auto temp = left->next;
    left->next = left->next->next;
    delete temp;

    // Since head could be deleted
    head = dummy->next;
    delete dummy;
    return head;
}


// 27/12/2022 LC138-Medium: Copy list with random pointer
// O(n)xO(n)
Node* copyRandomList(Node* head) {
    unordered_map<Node*, Node*> mp = {{nullptr, nullptr}};
    auto cur = head;
    while(cur){
        mp[cur] = new Node(cur->val);
        cur = cur->next;
    }

    cur = head;
    while(cur){
        mp[cur]->next = mp[cur->next];
        mp[cur]->random = mp[cur->random];
        cur = cur->next;
    }

    return mp[head];
}


// 27/12/2022 LC2-Medium: Add Two Numbers
// O(n)xO(n)
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    bool carry=false;
    auto result = new ListNode, prev = result;

    while(l1 || l2 || carry){
        int val=carry;
        val += l1?l1->val:0;
        val += l2?l2->val:0;
        carry = val>=10; // carry can never be more than 1 when adding two numbers
        val%=10;

        prev->next = new ListNode(val);
        l1 = l1?l1->next:l1;
        l2 = l2?l2->next:l2;
        prev = prev->next;
    }

    // delete dummy node
    prev = result;
    result = result->next;
    delete prev;

    return result;
}


// 27/12/2022 LC141-Easy: Linked List Cycle
// Floyd's cycle finding algorithm or Hare-Tortoise algorithm
// Alt: O(n)xO(n). keep all visited nodes in hashet if you see an already seen node then there's a cycle.
// O(n)xO(1). In each iteration distance b/w slow & fast decreases by 1 when they've entered a cycle because
// slow moves away by 1 and fast closes in gap by 2. Thus it takes at most n steps for them to reach.
bool hasCycle(ListNode *head) {
    auto slow = head, fast = head;

    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
        if(slow==fast) return true;
    }

    return false;
}


// 28/12/2022 LC287-Medium: Find the duplicate number

/* Floyd algorithm to detect the beginning of the cycle. Beginning of the cycle is the duplicate number.
Let the cycle begins after x steps from the start and slow & fast meets first time at
a distance of y steps from the beginning of the cycle.
Total distance travelled by slow * 2 = total distance travelled/steps taken by fast. b/o fast takes 2 steps while slow takes 1 step.
2*(x+y) = x+y+nc whre c is the length of cycle and n is the # of loops fast did before meeting slow ptr.
x+y=nc i.e x+y distance is a multiple of c. Thus with slow ptr at start and fast at meeting point and sliding
they will meet at the beginning of the cycle. */

// Alt: find meeting point. Then find length of cycle by counting # of steps(c) taken to meet again. Then start
// window with slow at start and fast c steps ahead. Slide the window to find the beginning of the cycle.

// O(n)xO(1)
int findDuplicate(vector<int>& nums) {
    int slow=0, fast=0;
    do{
        slow = nums[slow];
        fast = nums[nums[fast]];
    } while(slow!=fast);

    slow=0;
    // Slide the slow-fast windows to the right.
    while(slow!=fast){
        slow=nums[slow];
        fast=nums[fast];
    }
    return slow;
}


// 28/12/2022 LC146-Medium: LRU Cache
// O(1) for get, put operations.
class LRUCache {
    list<pair<int, int>> cache;
    unordered_map<int, list<pair<int,int>>::iterator> ump;
    int capacity;

    void evict(){
        int key = cache.back().first;
        cache.pop_back();
        ump.erase(key);
    }

public:
    LRUCache(int capacity):capacity(capacity) {
    }

    int get(int key) {
        auto it = ump.find(key);
        if(it==ump.end()) return -1;

        cache.splice(cache.begin(), cache, it->second);
        // splice doesn't involve construction/destruction of any element it only moves them
        // Hence iterators/pointers are still valid.
        return it->second->second;
    }

    void put(int key, int val) {
        auto it = ump.find(key);
        if(it!=ump.end()){
            it->second->second = val;
            cache.splice(cache.begin(), cache, it->second);
            return;
        }

        if(ump.size()==capacity) evict();

        cache.emplace_front(key, val);
        ump[key]=cache.begin();
    }
};


// 28/12/2022 LC23-Hard: Merge k sorted lists
// O(Nlogk)xO(1) => k is # of lists. N is total number of nodes in all lists combined.
// You are using input array itself => 0 space heap cost.
// O(k) space if you create separate priority_queue.
ListNode* mergeKLists_pq(vector<ListNode*>& lists) {
    // pop_heap on empty list will cause exception.
    if(!lists.size()) return nullptr;

    // When true list2 will be placed at the top and when false list1 is placed at the top.
    // Since default is max_heap with default < operation.
    auto cmp = [](ListNode *list1, ListNode *list2){
        if(!list1) return true; // places list2 at the top.
        if(!list2) return false; // places list1 at the top.
        return list1->val > list2->val;
    };

    // O(k)
    make_heap(lists.begin(), lists.end(), cmp);

    ListNode *result = new ListNode, *prev = result;

    // You pop every element once i.e O(nlogk)
    while(true){
        pop_heap(lists.begin(), lists.end(), cmp);
        if(!lists.back()) break; // Only nullptrs are there in the vector now.
        prev->next = lists.back();
        prev = prev->next;
        lists.back() = lists.back()->next;
        push_heap(lists.begin(), lists.end(), cmp);
    }

    prev = result;
    result = result->next;
    delete prev;
    return result;
}


ListNode* mergeKLists_r(vector<ListNode*>& lists, int start, int end){
    if(start==end) return lists[start];
    int mid = start + (end-start)/2;
    auto list1 = mergeKLists_r(lists, start, mid);
    auto list2 = mergeKLists_r(lists, mid+1, end);
    return mergeTwoLists(list1, list2);

}

// 28/12/2022 LC23-Hard: Merge k sorted lists
// O(Nlogk)xO(logk) O(logk) for recursion stack. Towards the last => k/2 merges i.e (k/2)*(n+n)=nk.
// Each merge O(n+n) ops where n is avg # of elements in a list. similarly k/4*(2n+2n)=nk....
ListNode* mergeKLists_r(vector<ListNode*>& lists){
    if(!lists.size()) return nullptr;
    return mergeKLists_r(lists, 0, lists.size()-1);
}


// 28/12/2022 LC23-Hard: Merge k sorted lists
// Alt: O(kN) solution is first combine lists one by one. This is optimized by reducing #of steps from k to logk.
// O(Nlogk)xO(1). No recursion stack unlike above.
ListNode* mergeKLists(vector<ListNode*>& lists) {
    if(!lists.size()) return nullptr;
    int size=1; // size of the interval
    while(size < lists.size()){
        for(int i=0;i+size < lists.size();i+=2*size){
            auto list1 = lists[i], list2 = lists[i+size];
            lists[i] = mergeTwoLists(list1, list2);
        }
        size<<=1;
    }
    return lists[0];
}


// 02/12/2022 LC25-Hard: Reverse Nodes in K-Group
// O(N) x O(1)
ListNode* reverseKGroup(ListNode* head, int k) {
    auto result = new ListNode, prev = result, next=head;
    while(true){
        auto cur = next;
        for(int i=0;i<k-1 && next;i++){
            next=next->next;
        }
        if(!next){
            prev->next = cur;
            break;
        }
        auto temp = next;
        next = next->next;
        temp->next = nullptr;

        
        prev->next = reverseList_2p(cur);
        prev = cur;
    }

    prev = result;
    result = result->next;
    delete prev;
    return result;
}


// 02/12/2022 LC25-Hard: Reverse Nodes in K-Group
// O(N) x O(N/k) b/o stack space
ListNode* reverseKGroup_r(ListNode* head, int k){
    auto next = head;
    for(int i=0;i<k-1 && next;i++){
        next = next->next;
    }

    if(!next){
        return head;
    }

    auto temp = next;
    next = next->next;
    temp->next = nullptr;

    auto result = reverseList_2p(head);
    head->next = reverseKGroup_r(next, k);
    return result;
}


int main(int argc, char const *argv[])
{
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2,2);
    cout << cache.get(1) << endl;
    return 0;
}