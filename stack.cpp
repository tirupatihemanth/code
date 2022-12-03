#include<bits/stdc++.h>
#define f(i,n) for(int i=0; i<n; i++)


using namespace std;

/// @brief All time complexities O(1)
/// @tparam T 
template<typename T>
class StackLL{
    class Node{
        
        public:
        T data;
        Node *next;
        Node(T data):data(data), next(nullptr){
        }
    };

    Node *head;
    int mSize;


    void insert_start(T data){
        Node* new_node = new Node(data);
        new_node->next = head;
        head = new_node;
    }

    void delete_start(){
        if(!head) return;
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    public:
    StackLL():head(nullptr), mSize(0){

    }

    void push(T data){
        insert_start(data);
        mSize++;
    }

    void pop(){
        if(mSize){
            delete_start();
            mSize--;
        }
        else{
            cout << "Empty stack" <<endl;
        }
    }

    T top(){
        if(mSize) return head->data;
        cout << "Empty Stack"<<endl;
        return mSize;
    }

    int size(){
        return mSize;
    }

    bool empty(){
        return mSize==0;
    }


};

/// @brief amortized/average time complexity of push/pop is O(n)
/// @tparam T 
template<typename T>
class Stack{
    vector<T> v;
    
    public:
    Stack(){

    }

    Stack(int size){
        v.reserve(size);
    }

    void push(T data){
        v.push_back(data);
    }

    void pop(){
        if(v.size()) v.pop_back();
        else cout << "Empty stack" <<endl;
    }

    T top(){
        if(v.size()) return v.back();
        cout << "Empty Stack"<<endl;
        return v.size();
    }

    int size(){
        return v.size();
    }

    bool empty(){
        return v.empty();
    }
};

/// @brief Circular Linked list impl of queue or you can use SLL with both head & tail ptrs.
/// @tparam T 
template<typename T>
class Queue{
    struct Node{
        T data;
        Node* next;
        Node(T data):data(data), next(nullptr){

        }
    };

    Node* tail;
    int mSize;


    public:
    Queue():tail(nullptr), mSize(0){

    }

    void enqueue(T data){
        mSize++;
        Node* new_node = new Node(data);
        if(!tail){
            new_node->next = new_node;
            tail=new_node;
            return;
        }
        new_node->next = tail->next;
        tail->next = new_node;
        tail = new_node;
    }

    void dequeue(){
        if(!tail){
            cout << "Empty Queue!!!"<<endl;
            return;
        }
        mSize--;
        if(tail->next==tail){
            delete tail;
            tail=nullptr;
            return;
        }

        Node * temp = tail->next;
        tail->next = tail->next->next;
        delete temp;
    }

    T front(){
        if(mSize) return tail->next->data;
        else {
            cout << "Empty Queue"<<endl;
            return mSize;
        }
    }

    T back(){
        if(mSize) return tail->data;
        else{
            cout << "Empty Queue"<<endl;
            return mSize;
        }
    }

    int size(){
        return mSize;
    }

    bool empty(){
        return mSize==0;
    }

};

/// @brief circular array implementation of queue
/// @tparam T 
template<typename T>
class QueueCA{

    protected:
    T *arr;
    int capacity;
    int _size, _front;

    public:
    QueueCA(int c):capacity(c), arr(new T[c]), _size(0), _front(0){
    }

    void enqueue(T data){
        if(full()){
            cout<<"Queue Full"<<endl;
            return;
        }
        arr[(_front+_size)%capacity]=data;
        _size++;
    }

    void dequeue(){
        if(empty()){
            cout<<"Queue Empty"<<endl;
            return;
        }
        _front = (_front+1)%capacity;
        _size--;
    }

    T front(){
        if(empty()){
            cout<<"Queue Empty"<<endl;
            return 0;
        }
        return arr[_front%capacity];
    }

    T back(){
        if(empty()){
            cout<<"Queue Empty"<<endl;
            return 0;
        }
        return arr[(_front+_size-1)%capacity];
    }

    int size(){
        return _size;
    }

    bool empty(){
        return _size==0;
    }

    bool full(){
        return _size==capacity;
    }

};

template<typename T>
class DequeCA:public QueueCA<T>{

    public:
    DequeCA(int capacity):QueueCA<T>(capacity){

    }

    void insertFront(T data){
        if(this->full()){
            cout<<"Queue Full"<<endl;
            return;
        }
        this->_front = (this->_front-1)%this->capacity;
        this->arr[this->_front]=data;
        this->_size++;
    }

    void deleteBack(){
        if(this->empty()){
            cout<<"Queue Empty"<<endl;
            return;
        }
        this->_size--;
    }

};

int main(){
    
    // Queue<int> q;
    // QueueCA<int> q(4);
    DequeCA<int> q(4);
    q.enqueue(10);
    q.enqueue(20);
    q.dequeue();
    q.insertFront(30);
    q.insertFront(40);
    q.insertFront(50);
    cout<<q.front()<< " "<<q.back()<<endl;
    q.deleteBack();
    cout<<q.front()<< " "<<q.back()<<endl;
    q.deleteBack();
    cout<<q.front()<< " "<<q.back()<<endl;
    q.dequeue();
    cout<<q.front()<< " "<<q.back()<<endl;
    cout<<q.size()<<" "<<q.empty()<<endl;
    /* StackLL<int> stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);

    cout << stack.top()<<endl;
    stack.pop();
    cout << stack.top()<<endl;
    stack.pop();
    cout << stack.top()<<endl;
    stack.pop();
    cout << stack.size()<<endl;
    cout << stack.empty()<<endl;
    cout << stack.top()<<endl; */

    
    return 0;
}