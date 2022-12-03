#include<bits/stdc++.h>

#define f(i,n) for(int i=0;i<n;i++)

using namespace std;


struct Node{
    int data;
    Node* next;
    Node(int x):data(x), next(nullptr){

    }
};

struct DNode{
    int data;
    DNode* prev, *next;
    DNode(int x):data(x), prev(nullptr), next(nullptr){

    }
};

//DLL methods

DNode* dll_insert_start(DNode *head, int data){
    DNode *new_node = new DNode(data);
    new_node->next = head;
    if(head) head->prev = new_node;
    return new_node;
}

DNode* dll_delete_start(DNode *head){
    if(!head) return head;
    if(!head->next){
        delete head;
        return nullptr;
    }
    head = head->next;
    delete head->prev;
    head->prev=nullptr;
    return head;
}

DNode* dll_insert(DNode *head, int data, int pos=1){
    if(pos==1)return dll_insert_start(head, data);
    
    DNode *new_node = new DNode(data);
    DNode *itr = head;
    f(i, pos-1) if(itr) itr = itr->next; else break;

    if(!itr) return head;
    new_node->prev = itr->prev;
    new_node->next = itr;
    itr->prev->next = new_node;
    itr->prev = new_node;
    return head;
}

DNode* dll_delete(DNode *head, int pos=1){
    if(pos==1) return dll_delete_start(head);

    DNode* itr = head;
    f(i, pos-1) if(itr) itr = itr->next; else break;

    if(!itr) return head;
    itr->prev->next = itr->next;
    delete itr;
    return head;
}

DNode* dll_reverse(DNode* head){
    if(!head) return head;

    DNode *itr = head, *next;
    while(itr->next){
        next = itr->next;
        swap(itr->prev, itr->next);
        itr = next;
    }
    swap(itr->prev, itr->next);
    return itr;
}

DNode* print_dllist(DNode* head){
    while(head){
        cout << head->data<<" ";
        head = head->next;
    }
    cout << endl;
}


//CLL methods

Node* cll_insert_start(Node *head, int data){
    Node* new_node = new Node(data);
    if(!head){
        new_node->next = new_node;
        return new_node;
    }
    new_node->next = head->next;
    head->next = new_node;
    swap(head->data, new_node->data);
    return head;
}

Node* cll_insert_end(Node *head, int data){
    Node* new_node = new Node(data);
    if(!head){
        new_node->next = new_node;
        return new_node;
    }
    new_node->next = head->next;
    head->next = new_node;
    swap(head->data, new_node->data);
    return new_node;
}

Node* cll_del_start(Node* head){
    if(!head)return head;
    if(head->next==head){
        delete head;
        return nullptr;
    }

    swap(head->data, head->next->data);
    Node *temp = head->next;
    head->next = head->next->next;
    delete temp;
    return head;
}

/* Not useful since O(n) and we can't do O(1). So just use pos. 
Node* cll_del_end(Node *head){
    if(!head)return head;
    if(head->next==head){
        delete head;
        return nullptr;
    }

    Node* itr = head;
    while(itr->next->next != head){
        itr = itr->next;
    }

    Node* temp = itr->next;
    itr->next = head;
    delete temp;
    return head;
} */

//Assume pos <=Length
Node* cll_insert(Node * head, int data, int pos=1){
    if(pos==1) return cll_insert_start(head, data);
    if(!head)return head;
    Node * new_node = new Node(data);
    Node *itr = head;
    f(i, pos-2){
        itr = itr->next;
    }

    new_node->next = itr->next;
    itr->next = new_node;
    return head;
}

// Assume pos <=Length
Node* cll_delete(Node* head, int pos=1){
    if(!head)return head; 
    if(pos==1)return cll_del_start(head);
    Node* itr = head;
    f(i,pos-2){
        itr = itr->next;
    }
    Node * temp = itr->next;
    itr->next = itr->next->next;

    // if assume pos <=length then this is not necessary -> that is the common assumption.
    if(temp!=head){
        delete temp;
        return head;
    }else{
        delete temp;
        return itr->next;
    }
}

void print_cllist(Node * head){
    if(!head)return;
    Node *itr = head;
    do
    {
        cout << itr->data << " ";
        itr=itr->next;
    } while (itr!=head);
    cout << endl;
}


//SLL methods
Node* insert_node(Node* head, int data, int pos=1){
    Node *newNode = new Node(data);

    if(pos==1){
        newNode->next=head;
        head=newNode;
        return head;
    }

    Node *itr = head;
    while(pos>2 & itr!=nullptr){
        itr = itr->next;
        pos--;
    }

    if(pos==2 && itr!=nullptr){
        newNode->next = itr->next;
        itr->next = newNode;
    }
    
    return head;
}

Node* delete_node(Node* head, int pos=1){
    if(pos==1){
        if(head){
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        return head;
    }

    Node *itr = head;
    while(pos>2 && itr!=nullptr){
        itr = itr->next;
        pos--;
    }

    if(pos==2 && itr!=nullptr && itr->next!=nullptr){
        Node *temp = itr->next;
        itr->next = itr->next->next;
        delete temp;
    }
    return head;
}

void print_llist(Node* head){
    while(head){
        cout << head->data <<" ";
        head = head->next;
    }
    cout << endl;
}

Node* search_llist(Node* head, int key){
    while(head){
        if(head->data==key){
            return head;
        }
        head = head->next;
    }
    return nullptr;
}

Node* middle_node(Node* head){
    Node *itr1 = head, *itr2 = head;

    while(itr2 && itr2->next){
        itr1 = itr1->next;
        itr2 = itr2->next->next;
    }

    return itr1;
}

Node* nth_node_end(Node* head, int n){
    Node *itr1=head, *itr2=head;

    while(itr2 && n>1){
        itr2 = itr2->next;
        n--;
    }

    while(itr2 && itr2->next){
        itr1=itr1->next;
        itr2=itr2->next;
    }

    if(itr2)return itr1;
    return nullptr;
}

Node* insert_sorted(Node* head, int data){
    Node* new_node = new Node(data);
    if(!head || data <head->data){
        new_node->next = head;
        head=new_node;
        return head;
    }

    Node* itr = head;
    while(itr->next && data >= itr->next->data){
        itr = itr->next;
    }

    new_node->next = itr->next;
    itr->next=new_node;
    return head;
}

Node* reverse_llist(Node* head){
    // Three pointer solution
    /* Node *prev=nullptr, *cur=head, *next=nullptr;
    while(cur){
        next = cur->next;
        cur->next = prev;
        prev=cur;
        cur=next;
    }
    return prev; */

    // Two pointer solution
}

Node* reverse_llist_recursive1(Node* cur, Node *prev=nullptr){
    if(!cur) return prev;
    Node* next = cur->next;
    cur->next = prev;
    return reverse_llist_recursive1(next, cur);
}

Node* reverse_llist_recursive2(Node* cur){
    if(!cur || !cur->next){
        return cur;
    }

    Node* head = reverse_llist_recursive2(cur->next);
    Node* rev_tail = cur->next;
    rev_tail->next=cur;
    cur->next=nullptr;
    return head;
}

// From sorted LL
Node* remove_duplicates(Node* head){
    if(!head)return head;
    Node* itr = head;
    while(itr->next){
        if(itr->data==itr->next->data){
            Node* temp = itr->next->next;
            delete itr->next;
            itr->next = temp;
        }
        else itr=itr->next;
    }
    return head;
}

Node* remove_duplicates_recursive(Node* head){

    if(!head || !head->next) return head;
    Node* next = remove_duplicates_recursive(head->next);

    if(head->data==next->data){
        delete head;
        return next;
    }
    else{
        head->next = next;
        return head;
    }
}

bool loop_detection(Node* head){
    
    // O(n)xO(n) solution
    /* unordered_set<Node*> set;
    while(head){
        if(!set.emplace(head).second){
            return true;
        }
        head = head->next;
    }
    return false; */

    // O(n) x O(1). Floyd's cycle detection.
    Node *slow = head, *fast = head;

    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
        if(slow==fast)return true;
    }
    return false;
}

//kth pos from last is n-k+1th pos from 1st.
//if you do n ->next ops you will be in n+1 pos
Node* intersection_node(Node* head1, Node* head2){
    //O(n)xO(n) soln use set.
    //O(n)xO(1) soln
    int n1=0, n2=0;
    Node *itr1 = head1, *itr2 = head2;
    while(itr1){
        itr1=itr1->next;
        n1++;
    }
    while(itr2){
        itr2=itr2->next;
        n2++;
    }

    if(n1<n2){
        swap(n1, n2);
        swap(head1,head2);
    }

    f(i,n1-n2)head1=head1->next;
    while(head1!=head2){
        head1=head1->next;
        head2=head2->next;
    }
    return head1;
}

int main(){
    
    DNode *head = nullptr;
    int n;
    cin >>n;


    /// Doubly Linked Lists
    f(i,n){
        int temp;
        cin >> temp;
        head = dll_insert_start(head, temp);
    }

    print_dllist(head);
    
    head = dll_reverse(head);
    print_dllist(head);

    head = dll_delete_start(head);
    print_dllist(head);
    
    head = dll_insert(head, 10, 2);
    print_dllist(head);

    head = dll_delete(head, 2);
    print_dllist(head);

    /// Circular Linked List
/*     f(i,n){
        int temp;
        cin >> temp;
        head = cll_insert_start(head, temp);
    }
    print_cllist(head);

    head = cll_del_start(head);
    print_cllist(head);
    
    head = cll_insert_end(head, 50);
    print_cllist(head);

    head = cll_delete(head, 2);
    print_cllist(head);
    
    head = cll_insert(head, 10, 2);
    print_cllist(head);
    // Singly Linked List */

    /* f(i,n){
        int temp;
        cin >>temp;
        head = insert_node(head, temp);
    }
    print_llist(head); */

    // cout << middle_node(head)->data << endl;

    // cout << nth_node_end(head, 4)->data << endl;

    // head = insert_sorted(head, 5);
    
    // head = reverse_llist_recursive1(head);

    // head = remove_duplicates_recursive(head);
    // print_llist(head);

    /* Node* itr = head;
    while(itr && itr->next)itr = itr->next;
    itr->next = head;
    cout << loop_detection(head); */

    /* int data, pos;
    cin >> pos >> data;
    head = insert_node(head, data, pos); */

    /* int del_pos;
    cin >> del_pos;
    head = delete_node(head, del_pos);
    print_llist(head); */



    return 0;
}