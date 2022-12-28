#include <bits/stdc++.h>
#include "leetcode.h"

using namespace std;

/* RECURSION */

// 27/11/2022 LC509-Easy
// O(n)xO(1) classic DP problem you can create arr[n] and keep filling values
// But as you need only prev1 & prev2 to get current val just store only those two 
// as you virtually build dp array bottom up.
int fib(int n) {
    if(!n || n==1) return n;
    // return fib(n-1)+fib(n-2);
    int prev1=0, prev2=1, sum=0;
    while(n-->=2){
        sum=prev2+prev1;
        prev1=prev2;
        prev2=sum;
    }
    return sum;
}

vector<TreeNode*> allPossibleFBT(unordered_map<int, vector<TreeNode*>> &fbts, int n) {
    if(n%2==0){
        return vector<TreeNode*>();
    }

    if(fbts.find(n)!=fbts.end()){
        return fbts[n];
    }

    if(n==1){
        if(fbts.find(n)==fbts.end()) fbts[n]=vector<TreeNode*>{new TreeNode};
        return fbts[n];
    }

    vector<TreeNode*> result;
    for(int i=2;i<=n-1;i+=2){
        auto leftTrees = allPossibleFBT(fbts, i-1);
        auto rightTrees = allPossibleFBT(fbts, n-i);
        for(auto &leftTree:leftTrees){
            for(auto &rightTree:rightTrees){
                TreeNode *root = new TreeNode;
                root->left = leftTree;
                root->right = rightTree;
                result.push_back(root);
            }
        }
    }
    fbts[n] = result;
    return fbts[n];
}

// 27/11/2022 LC894-Medium
/// @attention (2^n) x O(2^n) complexity. How? - Too tired to think now.
/// Since all nodes are 0 we are reusing the sub FBTs in bigger trees. So essential we built a graph.
/// If there are different elements then do deep copy while creating bigger sized FBT using smaller sized FBT.
vector<TreeNode*> allPossibleFBT(int n){
    unordered_map<int, vector<TreeNode*>> fbts;
    return allPossibleFBT(fbts, n);
}


// O(n)xO(n)
// 28/11/2022 LC24-Medium
ListNode* swapPairs(ListNode* head) {
    if(!head || !head->next) return head;
    ListNode* next = head->next->next;
    head->next->next = head;
    ListNode *result = head->next;
    head->next = swapPairs(next);
    return result;
}

// 28/11/2022 LC24-Medium
// O(n)xO(1)
ListNode* swapPairs_iter(ListNode* head) {
    ListNode *result = new ListNode;
    ListNode *tail = result;
    while(head && head->next){
        ListNode* next = head->next->next;
        tail->next = head->next;
        head->next->next = head;
        tail = head;
        head = next;
    }
    tail->next=head;
    return result->next;
}

// Aux function
int compute(int x, int y, char op){
    switch(op){
        case '+':
            return x+y;
        case '-':
            return x-y;
        case '*':
            return x*y;
        default:
            cout << "Incompatible op"<<endl;
            return INT_MIN;
    }
}

// 30/11/2022 LC241-Medium
// Add parenthesis to given math expression and find all the possible results
vector<int> diffWaysToCompute(string expression) {
    const static string ops = "+-*";
    //With memoization
    static unordered_map<string, vector<int>> memo;
    if(memo.count(expression)) return memo[expression];
    //

    int prev=0, pos=expression.find_first_of(ops);
    if(pos==string::npos) return memo[expression] = {stoi(expression)};
    vector<int> computes;
    do{
        vector<int> left_computes = diffWaysToCompute(expression.substr(0, pos));
        vector<int> right_computes = diffWaysToCompute(expression.substr(pos+1));
        for(auto x: left_computes)
            for(auto y: right_computes)
                computes.push_back(compute(x, y, expression[pos]));
        prev=pos+1;
    } while((pos = expression.find_first_of(ops, prev))!=string::npos);

    //memoization code
    memo[expression] = computes;
    //
    return computes;
}

// 30/11/2022 LC2487-Medium
// Remove all nodes which have a greater value anywhere to the rightside
ListNode* removeNodes(ListNode* head) {
    if(!head || !head->next) return head;
    head->next = removeNodes(head->next);
    if(head->val < head->next->val) return head->next;
    return head;
}

// 01/12/2022 LC761-Hard
//Special string is like valid paranthesis. i.e 1s=0s. any prefix has at least as many 1s as 0s.
string makeLargestSpecial(string s) {
    static unordered_map<string, string> memo;
    //Since given string is special you don't need stack just keep count to see all the top level sub special strings.
    // stack<char> sk;
    int count=0;
    vector<string> substrs;
    int start=0;
    for(int i=0;i<s.length();i++){
        if(s[i]=='1'){
            count++;
        }
        else{
            count--;
        }

        if(!count){
            substrs.push_back(s.substr(start,i-start+1));
            start=i+1;
        }
    }

    for(string &x:substrs){
        x = '1' + makeLargestSpecial(x.substr(1, x.length()-2)) + '0';
    }

    sort(substrs.begin(), substrs.end(), greater<string>());
    return memo[s] = accumulate(substrs.begin(), substrs.end(), string(""), plus<string>());
}

// 01/12/2022 LC761-Hard
// Alternate sol
string makeLargestSpecial(string &s, int &i){
    vector<string> subSpecials;
    bool closing=false;
    while(i<s.length() & !closing){
        if(s[i++]=='1')
            subSpecials.push_back(makeLargestSpecial(s, i));
        else closing=true;
    }

    sort(subSpecials.begin(), subSpecials.end(), greater<string>());
    string res = accumulate(subSpecials.begin(), subSpecials.end(), string(""), plus<string>());
    if(closing){
        return "1" + res + "0";    
    }
    return res;
}

vector<string> getSubExps(string exp){
    vector<string> subexps;
    int balance=0;
    int start=2;
    bool flag=true;
    for(int i=2;i<exp.length()-1;i++){
        if(flag && (exp[i]=='t' || exp[i]=='f')){
            subexps.push_back(string(1,exp[i]));
            i++;
            start=i+1;
            continue;
        }
        flag = false;
        if(exp[i]=='(') balance++;
        if(exp[i]==')'){
            balance--;
            if(balance==0){
                subexps.push_back(exp.substr(start, i-start+1));
                i++;
                start=i+1;
                flag=true;
            }
        }
    }
    return subexps;
}

// 01/12/2022 LC1106-Hard
bool parseBoolExpr(string exp) {
    if(exp[0]=='t') return true;
    if(exp[0]=='f') return false;
    if(exp[0]=='!') return !parseBoolExpr(exp.substr(2, exp.length()-3));
    
    vector<string> subexps = getSubExps(exp);
    
    if(exp[0]=='&')
        return accumulate(subexps.begin(), subexps.end(), true, [](bool res, string &s){return res && parseBoolExpr(s);});

    if(exp[0]=='|')
        return accumulate(subexps.begin(), subexps.end(), false, [](bool res, string &s){return res || parseBoolExpr(s);});

    return false;
}

char findKthBit(int start, int end, int k){
    if(start == end){
        return '0';
    }

    int mid = (start+end)/2;
    if(k==mid) return '1';
    if(k>mid) return findKthBit(start, mid-1, mid - (k-mid)) == '1'?'0':'1';
    if(k<mid) return findKthBit(start, mid-1, k);

    return '0';
}

// 01/12/2022 LC1545-Medium
// Si = Si - 1 + "1" + reverse(invert(Si - 1)). Give S1=1. Naive Find Sn and return kth element.
char findKthBit(int n, int k) {
        return findKthBit(0, (1<<n)-2, k-1);
}

// 01/12/2022 LC394-Medium
// Pattern where by outerlayer is evaluated and inner layer is called recursively.
// Used in evaluate bool expression quesiton also LC1106
string decodeString(string s){
    string decodedString, curString;
    int level=0, pos, val;

    for(int i=0;i<s.length();i++){
        if(isalpha(s[i]) && level==0){
                decodedString.push_back(s[i]);
        }

        if(isdigit(s[i])){
            if(level==0){
                pos=i;
            }
            while(isdigit(s[i])) i++;
            level++;
        }

        if(s[i]=='[' && level==1){
            val = stoi(s.substr(pos, i-pos));
            pos=i+1;
        }

        if(s[i]==']'){
            if(level==1){
                curString = decodeString(s.substr(pos, i-pos));
                while(val--) decodedString += curString;
            }
            level--;
        }
    }

    return decodedString;
}

// 01/12/2022 LC394-Medium
// Alt paradigm of solving these questions where instead of using levels we do dfs.
string decodeString(string &s, int &i){
    string res;
    while(i<s.length() && s[i]!=']'){
        if(!isdigit(s[i])){
            res.push_back(s[i++]);
        }
        else{
            int n=0;
            while(isdigit(s[i])) n = n*10 + s[i++]-'0';
            i++; //'['
            string cur = decodeString(s, i);
            i++; //']'
            while(n--) res+=cur;
        }
    }
    return res;
}

int main(int argc, char const *argv[])
{
    /* ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head = reverseList_TailRecur(head);
 */
    // allPossibleFBT(3);
    // printContainer(diffWaysToCompute("2*3-4*5"));
    
    // cout << makeLargestSpecial("10");
    // cout << parseBoolExpr("|(&(t,f,t),t)")<<endl;
    // cout << findKthBit(3, 1)<<endl;
    // cout << decodeString("2[abc]3[cd]ef")<<endl;
    return 0;
}
