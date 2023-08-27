#include "leetcode.h"
using namespace std;


/* STACK */
/* NEETCODE.IO */


// 13/12/2022 LC20-Easy: Valid Paranthesis
// Balanced paranthesis? #open=#close. Opened latest = closed first. Closed after opened. same type close.
// O(l)xO(l) Basically we need to always know the last unmatched open bracket whenever a closed bracket is encountered
// Thus a stack/vector to store all the open brackets where the last element is automatically the last open bracket.
// Alt: If only one type of paran then w/o stack: balance-- on each pop & if balance<0 anytime return false. Finally ret balance==0.
bool isValidParenthesis(string s) {
    stack<char> sk;
    unordered_map<char, char> mp = {
        {')', '('}, 
        {'}', '{'}, 
        {']', '['}
    };

    for(char c:s){
        if(c=='(' || c== '{' || c=='[') sk.push(c);
        else if(sk.empty() || sk.top()!=mp[c]) return false;
        else sk.pop();
    }
    return sk.empty();
}


// 13/12/2022 LC155-Medium: Min Stack
// Overall O(n) extra space. 
// O(1)xO(1) for all operations. getMin & insert & del are all O(1) which is impossible with any other DS only
// because we are able to delete only the last inserted element not any random element.
class MinStack {
    stack<int> sk;
    stack<int> minSk;
public:
    MinStack() {

    }
    
    void push(int val) {
        sk.push(val);
        if(minSk.empty() || minSk.top()>=val){
            minSk.push(val);
        }
    }
    
    void pop() {
        if(sk.top()==minSk.top()) minSk.pop();
        sk.pop();
    }
    
    int top() {
        return sk.top();
    }
    
    int getMin() {
        return minSk.top();
    }
};


// 13/12/2022 LC155-Medium: Min Stack
// O(1) overall extra space & O(1)xO(1) for all ops.
// Here instead of storing elements we are storing cur_value-min_value.
// Alt: push 2val-min whenever new push val <=min else just push val. if pop val<=min then update min to 2min-val.
class MinStack_alt {
    stack<long> sk;
    long cur_min;
public:
    MinStack_alt() {

    }
    
    void push(int val) {
        if(sk.empty()){
            cur_min = val;
            sk.push(0);
            return;
        }
        
        sk.push(val-cur_min);
        if(val < cur_min) cur_min = val;
    }
    
    void pop() {

        if(sk.top() < 0){
            cur_min = cur_min-sk.top();
        }
        sk.pop();
    }
    
    int top() {
        if(sk.top()<0) return cur_min;
        return sk.top()+cur_min;
    }
    
    int getMin() {
        return cur_min;
    }
};


// 13/12/2022 LC150-Medium: Evaluate Reverse Polish Notation aka postfix evaluation
// We use operand stack because each encounter of an operator requires most recent two values to operate. Similar
// to that of valid paranthesis where you only need most recent value.
// O(n)xO(n)
int evalRPN(vector<string>& tokens) {
    stack<long long> sk;
    for(auto &s:tokens){
        // take care of -ve numbers
        if(isdigit(s[0]) || s.length() > 1){
            sk.push(stoi(s));
            continue;
        }
        
        long long op2 = sk.top();
        sk.pop();
        long long op1 = sk.top();
        sk.pop();
        switch(s[0]){
            case '+':
                sk.push(op1+op2);
                break;
            case '-':
                sk.push(op1-op2);
                break;
            case '*':
                sk.push(op1*op2);
                break;
            case '/':
                sk.push(op1/op2);
        }
    }
    return sk.top();
}


// Naive: O(n * 2^n) => generate all possible strings then in the base condition i.e open==close==n check
// if it's a valid paranthesis. 2^n for all possible strings * O(n) for checking validity of each such string.

// Backtracking: Collect required values at leaves generated as we move along down from head. But explore only those
// paths which would generate a valid leaf. Here when close < open & open < n conditions does that.

/* 
                                                   "("
                                    "(("                       "()"
                            "((("          "(()"               "()("
                            "((()"    "(())"  "(()("      "()()"  "()(("
                            "((())"   "(())(" "(()()"     "()()(" "()(()"
                            "((()))"  "(())()" "(()())"   "()()()" "()(())"

 */

void generateParenthesis(int n, string &s, vector<string> &res, int open=0, int close=0){
    // We are collecting all the leaves into a reference param res.
    // We could also return vector<string> but merge such vector<strings after the two recursive calls and return merged vector<string> but extra ops
    if(open == n && close == n) return res.push_back(s);

    if(open < n){
        s.push_back('(');
        generateParenthesis(n, s, res, open+1, close);
        // backtrack
        s.pop_back();
    }

    if(close<open){
        s.push_back(')');
        generateParenthesis(n, s, res, open, close+1);
        // backtrack
        s.pop_back();
    }
}

// 13/12/2022 LC22-Medium: Generate Paranthesis
vector<string> generateParenthesis(int n){
    vector<string> res;
    string s;
    generateParenthesis(n, s, res);
    return res;
}


// 14/12/2022 LC739-Medium: Daily Temperatures
// Equivalent to finding next Greater Element. You have Monotonic decreasing stack.
// Alt: You can do it from left to right also.
// Naive: O(n^2)xO(1)
// O(n)xO(n)
vector<int> dailyTemperatures(vector<int>& temperatures) {
    stack<int> sk;
    vector<int> nextGreaterTemp(temperatures.size());
    for(int i=temperatures.size()-1;i>=0;i--){

        while(!sk.empty() && temperatures[i]>=temperatures[sk.top()]) sk.pop();
        
        if(sk.empty())  nextGreaterTemp[i]=0;
        else    nextGreaterTemp[i] = sk.top()-i;
        sk.push(i);
    }

    return nextGreaterTemp;
}


// 14/12/2022 LC853-Medium: Car Fleet
// Alt: Soln commented below. Equivalent to prevGreaterElement.
// Each element in the stack is a car fleet. All elements going together i.e time <=sk.top() are 
// represented by sk.top() hance not pushed. time > sk.top() arrives later and is pushed.
// O(nlogn)xO(n). Monotonic Stack (INCREASING)!!!
int carFleet(int target, vector<int>& position, vector<int>& speed) {
    vector<pair<int, int>> mp(position.size());
    for(int i=0;i<position.size();i++){
        mp[i].first = position[i];
        mp[i].second = speed[i];
    }

    // transform(position.begin(), position.end(), speed.begin(), mp.begin(), [](int x, int y)->pair<int, int>{return {x, y};});

    sort(mp.begin(), mp.end());
    stack<float> sk;         
    
    for(int i=position.size()-1;i>=0;i--){
        float time = float(target-mp[i].first)/mp[i].second;
    
        // last element is always pushed i.e when stack is empty.
        // You could do it outside for loop and start from i=n-2 pos.
        if(sk.empty() || time>sk.top()) sk.push(time);

        
        /* Decreasing Monotonic stack implementation. Iterate from left to right. Replace above if with below
        while(!sk.empty() && time>=sk.top()) sk.pop();
        sk.push(time);
         */
    }

    return sk.size();   
}


// 17/12/2022 LC84-Hard: Largest Rectangle in Histogram
// O(n)xO(n) find (previousSmaller, nextSmaller) as width of each element find area.
int largestRectangleArea(vector<int>& heights) {
    int prevSmaller[heights.size()], nextSmaller[heights.size()];
    stack<int> sk;

    for(int i=0;i<heights.size();i++){
        while(!sk.empty() && heights[sk.top()]>=heights[i]) sk.pop();
        if(sk.empty()) prevSmaller[i]=-1;
        else prevSmaller[i] = sk.top();
        sk.push(i);
    }

    sk = stack<int>();

    for(int i=heights.size()-1; i>=0;i--){
        while(!sk.empty() && heights[sk.top()]>=heights[i]) sk.pop();
        if(sk.empty()) nextSmaller[i]=heights.size();
        else nextSmaller[i] = sk.top();
        sk.push(i);
    }

    int result = INT_MIN;
    for(int i=0;i<heights.size();i++){
        result = max(result, heights[i]*(nextSmaller[i]-prevSmaller[i]-1));
    }
    return result;
}

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


int main(int argc, char const *argv[])
{
    // cout << isValidParenthesis("]");

    // vector<int> temperatures = {73,74,75,71,69,72,76,73};
    // printContainer(dailyTemperatures(temperatures));

    vector<int> heights = {2, 1, 5, 5, 6, 2, 3};
    cout << largestRectangleArea_alt(heights);
    return 0;
}
