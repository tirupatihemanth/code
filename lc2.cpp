#include "leetcode.h"

using namespace std;

/* LINKED LISTS */

// 02/12/2022 LC2181-Medium: Merge Nodes Between Zeros
// O(N) x O(1)
ListNode* mergeNodes(ListNode* head) {
    ListNode *cur = head, *tail = new ListNode;
    tail->next = head;
    int sum=0;
    while(cur){
        if(cur->val==0 & sum!=0){
            tail->next->val = sum;
            tail = tail->next;
            sum=0;
        }
        sum = sum+=cur->val;
        cur = cur->next;
    }
    cur = tail->next;
    tail->next=nullptr;

    // Free the rest
    ListNode* temp;
    while(cur){
        temp = cur->next;
        delete cur;
        cur = temp;
    }

    return head;
}


// 02/12/2022 LC1290-Easy: Convert Binary Number in a LL to integer
int getDecimalValue(ListNode* head) {
    int n=0;
    while(head){
        n = (n<<1) | head->val; //If we are reading a decidmal number then n = n*10 + head->val
        head = head->next;
    }
    return n;
}


// 02/12/2022 LC2130-Medium: Maximum Twin Sum of a Linked List
// O(N)xO(1)
int pairSum(ListNode* head) {
    if(!head) return 0;
    ListNode* cur = head, *fast = head;

    while(fast && fast->next){
        cur = cur->next;
        fast = fast->next->next;
    }

    cur = reverseList(cur);
    int max_val = INT_MIN;
    while(cur){
        max_val = max(max_val, head->val+cur->val);
        cur = cur->next;
        head = head->next;
    }

    return max_val;
}


// 02/12/2022 LC2130-Medium: Maximum Twin Sum of a Linked List
// O(N)xO(N) Recursive solution uses pointer reference
int pairSum_r(ListNode* cur, ListNode* &start){
    if(!cur) return 0;
    int curMax = pairSum_r(cur->next, start);
    if(!start) return curMax;

    curMax = max(curMax, start->val+cur->val);
    if(start->next == cur){
        start = nullptr;
    }
    else start = start->next;
    return curMax;
}


int pairSum_r(ListNode* head){
    ListNode* start = head;
    return pairSum_r(head, start);
}


// 03/12/2022 LC1472-Medium: Design Browser History
// If you want all O(1) use vector & not care about deleting forward history.
// if you are ok with visit not being O(1) then use vector & delete forward history on each visit.
// Or you can use list & iterate with iterators => same complexity as this soln.
class BrowserHistory {
    stack<string> backSk, frontSk;
public:
    BrowserHistory(string homepage) {
        backSk.push(homepage);
    }

    void visit(string url) {
        backSk.push(url);
        frontSk = stack<string>();
    }

    string back(int steps) {
        steps = backSk.size()>steps?steps:backSk.size()-1;
        while(steps--){
            frontSk.push(backSk.top());
            backSk.pop();
        }
        return backSk.top();
    }

    string forward(int steps) {
        steps = frontSk.size()>=steps?steps:frontSk.size();
        while(steps--){
            backSk.push(frontSk.top());
            frontSk.pop();
        }
        return backSk.top();
    }
};


// 03/12/2022 LC2326-Medium: Spiral Matrix
// O(N)xO(N)
vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {
    vector<vector<int>> mat(m, vector<int>(n, -1));
    int i=0, j=-1, num_x=m, num_y=n, counter;

    while(head){
        //left
        counter=num_y;
        while(head && counter--){
            mat[i][++j]=head->val;
            head = head->next;
        }
        num_x--;

        //down
        counter=num_x;
        while(head && counter--){
            mat[++i][j]=head->val;
            head = head->next;
        }
        num_y--;

        //right
        counter=num_y;
        while(head && counter--){
            mat[i][--j]=head->val;
            head = head->next;
        }
        num_x--;

        //up
        counter=num_x;
        while(head && counter--){
            mat[--i][j]=head->val;
            head = head->next;
        }
        num_y--;
    }
    return mat;
}


// Merges two lists starting with left, right & ends with null
ListNode* mergeLL(ListNode* left, ListNode *right){
    ListNode *prev = new ListNode, *result = prev;

    while(left && right){
        if(left->val < right-> val){
            prev->next = left;
            left = left->next;
        }
        else{
            prev->next = right;
            right = right->next;
        }
        prev = prev->next;
    }

    if(left){
        prev->next = left;
    }
    else{
        prev->next = right;
    }
    prev = result;
    result = result->next;
    delete prev;
    return result;
}

// 03/12/2022 LC148-Medium: Sort List
// O(nlogn)xO(logn) mergeSort impl for linked list. O(N) is auxilliary stack space.
ListNode* mergeSortLL(ListNode *head){
    if(!head || !head->next) return head;
    
    ListNode *fast=head, *slow=head;
    ListNode *temp;
    while(fast && fast->next){
        temp = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    temp->next = nullptr;
    
    ListNode* left = mergeSortLL(head);
    ListNode* right = mergeSortLL(slow);

    return mergeLL(left, right);
}


// 03/12/2022 Alt
// O(nlogn)xO(1) bottom up iterative merge sort impl
ListNode* mergeSortLL_i(ListNode* head){
    if(!head || !head->next) return head;
    ListNode* prev = new ListNode, *left = head, *right, *next;
    ListNode *result = prev;
    prev->next = head;

    int step = 1, counter = 1;
    bool complete = false;

    while(!complete){

        while(left){
            right = left;
            counter = step;
            ListNode *temp;
            while(right && counter--){
                temp = right;
                right = right->next;
            }
            temp->next = nullptr;
            if(left==result->next && right==nullptr){
                complete = true;
                break;
            }
            if(right==nullptr){
                prev->next = left;
                break;
            }

            next = right;
            counter = step;
            while(next && counter--){
                temp = next;
                next = next->next;
            }
            temp->next = nullptr;
            prev->next = mergeLL(left, right);
            while(prev->next){
                prev = prev->next;
            }
            left = next;
        }
        left = result->next;
        prev = result;
        step <<=1;
    }

    prev = result;
    result = result->next;
    delete prev;
    return result;
}


int main(int argc, char const *argv[])
{
    ListNode *head = makeList({-1, 3, 0, 4, 5});
    // printList(sortList(head));
    printList(mergeSortLL(head));
    // printList(reverseKGroup_r(head, 3));
/*     BrowserHistory bh("esgriv");
    bh.visit("cgrt");
    bh.visit("tip");
    cout << bh.back(9)<<endl;
    bh.visit("ktt");
    cout << bh.forward(7)<<endl;
    bh.visit("crq");
    bh.visit("iyb");
    cout << bh.forward(5)<<endl;
    bh.visit("unn");
    cout << bh.back(10)<<endl;
    bh.visit("hci");
    bh.visit("whula");
    cout << bh.forward(10)<<endl; */


    return 0;
}
