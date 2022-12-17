#include<bits/stdc++.h>
#include "leetcode.h"
using namespace std;

/* STACK */
/* GFG */

// 14/12/2022 
// Closest (position wise) greater element for each element
// Naive: O(n^2)xO(1)
// We have Monotonic Stack (decreasing).
// O(n)xO(n). O(n)xO(n) since every element is pushed & popped atmost once.
vector<int> prevGreater(vector<int> &v){
    stack<int> sk;
    vector<int> result(v.size());
    for(int i=0;i<v.size();i++){
        while(!sk.empty() && v[i]>=sk.top()) sk.pop();
        if(sk.empty()) result[i]=-1;
        else result[i] = sk.top();
        sk.push(v[i]);
    }

    return result;
}

// 14/12/2022 
// Naive: O(n^2)xO(1)
// Span on a day is the count of days just before & including itself having value <= itself.
// Which is basically no. of elements in (prevGreater, curElement]
// O(n)xO(n). Monotonic Stack (decreasing) of values corresponding to indices stored in stack.
vector<int> stockSpan(vector<int> &v){
    stack<int> sk;
    vector<int> result(v.size());
    for(int i=0;i<v.size();i++){
        while(!sk.empty() && v[i]>=v[sk.top()]) sk.pop();

        if(sk.empty()) result[i] = i+1;
        else result[i] = i-sk.top();
        sk.push(i);
    }
    return result;
}

// 14/12/2022 
// Naive: O(n^2)xO(n)
// Iterating from right to left the problem is similar to prevGreater element
// O(n) x O(n). Monotonic Stack (decreasing).
vector<int> nextGreater(vector<int> &v){
    stack<int> sk;
    vector<int> result(v.size());
    for(int i=v.size()-1;i>=0;i--){
        while(!sk.empty() && v[i]>=sk.top()) sk.pop();

        if(sk.empty()) result[i] = -1;
        else result[i] = sk.top();
        sk.push(v[i]);
    }
    return result;
}

// 14/12/2022 
// Whenever cur element is > sk.top() we update nextGreater for all such v[sk.top()] to cur element.
// O(n)xO(n). Monotonic Stack (decreasing);
vector<int> nextGreater_alt(vector<int> &v){
    stack<int> sk;
    vector<int> result(v.size(), -1);
    for(int i=0;i<v.size();i++){
        // Observe strict '>'
        while(!sk.empty() && v[i]>v[sk.top()]){
            result[sk.top()] = v[i];
            sk.pop();
        }
        sk.push(i);
    }

    // Elements left in stack have no nextGreater. Defaulted anyway to zero.
    return result;
}


/* 
    Operator precdence  |   Associativity
    ^ (exponent)        |   Right to Left
    *, /                |   Left to Right
    +, -                |   Left to right

 */

// 16/12/2022 
// We use monotonic operator stack (increasing) here. So operator you popped first has highest precedence
// and thus comes first/left in postfix thus evaluated first.
// theta(n)xtheta(n)
string infixToPostFix(string infix){
    string postfix;
    stack<char> optr_sk; 
    unordered_map<char, short> precedence = {
        {'(', 0}, // Here only to ensure it don't get popped when pushing operators.
        {'+', 1}, {'-', 1}, 
        {'*', 2}, {'/', 2}, 
        {'^', 3}
    };

    for(auto c:infix){
        if(c == '(') optr_sk.push(c);
        else if(c == ')') {
            while(optr_sk.top()!='('){
                postfix.push_back(optr_sk.top());
                optr_sk.pop();
            }
            optr_sk.pop(); // pop '('
        }
        else if(precedence.count(c)){
            if(c == '^'){ // '^' is right-associative
                optr_sk.push(c);
                continue;
            }

            while(!optr_sk.empty() && precedence[c]<=precedence[optr_sk.top()]){
                postfix.push_back(optr_sk.top());
                optr_sk.pop();
            }
            optr_sk.push(c);
        }
        else postfix.push_back(c); // Adding all operands directly to postfix expression.
    }

    while(!optr_sk.empty()){
        postfix.push_back(optr_sk.top());
        optr_sk.pop();
    }
    return postfix;
}

// Postfix evaluation uses operand stack (see LC150 evalRPN problem).

// 16/12/2022 
// NOTE: Reverse of a postfix expression is not prefix and vice-versa. 
// Mono ⬆ operator stack. We always want to pop the highest precedence operator first.
// theta(n)xtheta(n). 
string infixToPrefix(string infix){
    string prefix;
    stack<char> optr_sk;
    unordered_map<char, short> precedence = {
        {')', 0}, // Here only to ensure it don't get popped when pushing operators in mono ⬆ stack.
        {'+', 1}, {'-', 1}, 
        {'*', 2}, {'/', 2}, 
        {'^', 3}
    };
    for(int i=infix.size()-1; i>=0; i--){
        char c = infix[i];
        if(c==')') optr_sk.push(c);
        else if(c=='('){
            while(optr_sk.top()!=')'){
                prefix.push_back(optr_sk.top());
                optr_sk.pop();
            }
            optr_sk.pop();
        }
        else if(precedence.count(c)){
            while(!optr_sk.empty() && precedence[c]<precedence[optr_sk.top()]){
                prefix.push_back(optr_sk.top());
                optr_sk.pop();
            }

            // '^' is right to left associative so if already in stack then it's higher precedence hence pop
            while(!optr_sk.empty() && optr_sk.top()=='^'){
                prefix.push_back(optr_sk.top());
                optr_sk.pop();
            }

            optr_sk.push(c);
        }
        else prefix.push_back(c);
    }
    
    while(!optr_sk.empty()){
        prefix.push_back(optr_sk.top()); 
        optr_sk.pop();
    }

    reverse(prefix.begin(), prefix.end());
    return prefix;
}


// 16/12/2022 Evaluate Prefix Expression. postfix eval see LC150 RPN
// theta(n)xtheta(n)
int evalPrefix(vector<string> &tokens){
    stack<long long> opnd_sk;
    for(int i=tokens.size()-1;i>=0;i--){
        string &s = tokens[i];
        if(isdigit(s[0]) || s.length()>1){
            opnd_sk.push(stoi(s));
            continue;
        }

        // This will be op2 & then op2 for postfix evaluation where you start from left to right
        long long op1 = opnd_sk.top();
        opnd_sk.pop();
        long long op2 = opnd_sk.top();
        opnd_sk.pop();

        switch (s[0])
        {
        case '+':
            opnd_sk.push(op1+op2);
            break;
        case '-':
            opnd_sk.push(op1-op2);
            break;
        case '*':
            opnd_sk.push(op1*op2);
            break;
        case '/':
            opnd_sk.push(op1/op2);
            break;
        case '^':
            opnd_sk.push(pow(op1, op2));
        }
    }
    return opnd_sk.top();
}


// 16/12/2022 Two Stacks in an array
// One from the left and the other from the right.
class TwoStacks{

    int *arr;
    int capacity, i1, i2;
    
    public:

    TwoStacks(int capacity):capacity(capacity), arr(new int[capacity]){
        i1 = -1;
        i2 = capacity;
    }

    void push1(int x){
        if(i1==i2-1) return; // array full
        arr[++i1]=x;
    }

    void push2(int x){
        if(i1==i2-1) return;
        arr[--i2]=x;
    }

    int pop1(){
        if(i1==-1) return -1; // stack empty
        return arr[i1--];
    }

    int pop2(){
        if(i2==capacity) return -1; // stack empty
        return arr[i2++];
    }

    int top1(){
        return arr[i1];
    }

    int top2(){
        return arr[i2];
    }

    int size1(){
        return i1+1;
    }

    int size2(){
        return capacity-i2;
    }

};


// 16/12/2022 K Stacks in an array
// This approach makes sense when object to be stored are huge Student/Employees objects etc., But we need to 
// create only small sized top/next integer arrays as extra.
class KStacks{

    int n, k, freeTop;
    int *arr, *next, *_top, *_size;

    public:
    KStacks(int n, int k):n(n), k(k){
        arr = new int[n];
        next = new int[n];
        _size = new int[k](); // the brackets initalizes array to zero
        _top = new int[k];

        fill(_top, _top+k, -1);
        freeTop = 0;
        iota(next, next+n, 1);
        next[n-1] = -1;
    }

    void push(int x, int sk){
        if(freeTop == -1) return;
        int temp = freeTop;
        freeTop = next[freeTop];
        next[temp] = _top[sk];
        _top[sk] = temp;
        arr[temp] = x;
        _size[sk]++;
    }

    int pop(int sk){
        if(_top[sk]==-1) return INT_MIN;
        int temp = _top[sk];
        _top[sk] = next[temp];
        next[temp] = freeTop;
        freeTop = temp;
        _size[sk]--;
        return arr[temp];
    }

    int top(int sk){
        if(_top[sk]==-1) return INT_MIN;
        return arr[_top[sk]];
    }

    bool empty(int sk){
        return _top[sk]==-1;
    }

    int size(int sk){
        return _size[sk];
    }
};


// 17/12/2022 LC84-Hard: Largest Rectangle in Histogram
// O(n) x O(n). Single traversal. No separate arrays for previousSmaller & nextSmaller.
int largestRectangleArea_alt(vector<int>& heights) {
    stack<int> sk;
    int result = INT_MIN;

    for(int i=0;i<heights.size();i++){
        // Case when top val is equal to cur val then while popping next smaller of that elem is not i.
        // But this approach still works as max area will be obtained by cur val since it's prev smaller will be
        // the element before top val & thus it will get the max area possible.
        while(!sk.empty() && heights[sk.top()]>=heights[i]){
            int top = sk.top();
            sk.pop();
            int prevSmaller = sk.empty()?-1:sk.top();
            result = max(result, heights[top]*(i-prevSmaller-1));
        }
        sk.push(i);
    }

    while(!sk.empty()){
        int top = sk.top();
        sk.pop();
        int prevSmaller = sk.empty()?-1:sk.top();
        result = max(result, heights[top]*(int(heights.size())-prevSmaller-1));
    }
    return result;
}


// 17/12/2022 LC85-Hard: Maximal Rectangle
// theta(mn)xtheta(n) => theta(n) space since if given bool matrix or asked to not modify input then you 
// need current row in integer values i.e theta(n). Also largestRect takes O(n) space. Hence total theta(n).
int maximalRectangle(vector<vector<int>>& matrix){
    int result = largestRectangleArea_alt(matrix[0]);
    for(int i=1;i<matrix.size();i++){
        for(int j=0;j<matrix[i].size();j++){
            matrix[i][j]+= matrix[i][j]?matrix[i-1][j]:0;
        }
        result = max(result, largestRectangleArea_alt(matrix[i]));
    }
    return result;
}



int main(int argc, char const *argv[])
{
    // vector<int> v = {15, 10, 18, 12, 4, 6, 2, 8};
    // vector<int> v = {5, 15, 10, 8, 6, 12, 3, 18};
    // printContainer(prevGreater(v));
    // printContainer(stockSpan(v));
    // printContainer(nextGreater(v));
    // printContainer(nextGreater_alt(v));

    // string infix; 
    // cin >> infix;
    // cout << infixToPostFix(infix)<<endl;
    // cout << infixToPrefix(infix)<<endl;

    // vector<string> v = {"^", "10", "^", "2", "3"};
    // cout << evalPrefix(v);
    
    // TwoStacks ts(10);
    KStacks ks(10, 3);
    vector<vector<int>> v(200, vector<int>(200, 1));
    cout << maximalRectangle(v);
    return 0;
}
