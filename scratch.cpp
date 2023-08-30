#include "leetcode.h"

#define f(i,n) for(int i=0;i<n;i++)
using namespace std;

template<typename T>
T myMax(T x, T y){
    return x > y?x:y;
}

class Test{
    
    
    public:
    int x, y;

    Test(){
        x=0;
        y=0;
    }

    Test(int x, int y):x(x), y(y){

    }
};

template <typename Comp>
bool myFunc(int x, int y, Comp comp){
    return comp(x,y);
}

struct Add10{
    int m, n;
    int operator ()(int x){
        return x+10;
    }
};

int add10(int x){
    return x+10;
}

int main(int argc, char const *argv[])
{
    cout << INT_MAX << endl;
    cout << LONG_MAX << endl;
    // cout << LONG_LONG_MAX << endl; string hey; 

    array<int, 3> ar = {1};
    auto [a1, a2, a3] = ar;
    cout << a1 << a2 << a3 << endl;
/* 
    int b[5] = {1,2,3,4,5};
    int mat[2][3] = {{1,2, 3}, {3, 4, 5}};
    int (*arpr)[3] = mat;
    int *ptr = b;
    int (*a)[5] = &b;
    cout << ptr<<" "<<a<<endl;
    cout << sizeof(ptr)<<" "<<sizeof(a[0])<<" "<<sizeof(b)<<endl;
    cout <<ptr[1]<<" "<<a[0][1]<<endl;
    cout << arpr <<" "<<mat<<endl;
    cout << *(arpr+1)<<" "<<*(mat+1)<<" "<<&mat[1][0]<<endl;
    cout <<arpr[1][1] << " "<< mat[1][1]<<endl;
     */
    
    set<int> seh;
    seh.insert(10);
    seh.insert(5);
    seh.insert(15);
    seh.emplace_hint(seh.begin(), 20);
    for(int x:seh){
        cout << x << " ";
    }
    cout << endl;
    Add10 ad = {.m=10, .n=20};
    cout << ad.m<<" "<< ad.n<<endl;
    int arr[10]{1,2,3};
    vector<int> v{1,2,3,4,5};
    do{
        f(i,v.size()) cout << v[i]<<" ";
        cout << endl;    
    }while(next_permutation(v.begin(), v.end()));
    vector<int> v_2(v.rbegin(), v.rend());
    swap(v, v_2);
    // rotate(v.begin(), v.begin()+2, v.end());
    f(i,v.size()) cout << v[i]<<" ";
    cout << endl;
    sort(v.begin(), v.end(), greater<int>());
    int init_res=1;
    cout << accumulate(v.begin(), v.end(), init_res, multiplies<int>())<<endl;
    pair<int, int> p{1,2};
    auto [x,y] = p;
    forward_list<int> fl(5, 10), fl2(10, 5);
    list<int>l(10);
    deque<int> dq(3, -1);
    queue<int> q;
    stack<int> s;
    auto cmp1 = [](int x, int y){return x>y;};
    priority_queue<int, vector<int>, decltype(cmp1)> pq(v.begin(), v.end(), cmp1);
    set<int, greater<int>> st;
    st.insert(st.find(2), 3);
    multiset<int> mst;
    pair<set<int>::iterator, bool> pr0 = st.insert(1);
    multiset<int>::iterator pr = mst.insert(1);
    cout << *pr <<endl;
    st.insert(20);
    st.insert(30);
    cout << (st.lower_bound(0)==st.end()) << endl;
    cout << *st.erase(st.begin(), ++(++st.begin()))<<endl;
    cout << *st.begin()<<endl;
    unordered_set<int> ust;
    cout << "Unordered Multiset"<<endl;
    struct myComp{
        bool operator() (string &s1, string &s2){
            return s1.length() == s2.length();
        }
    };
    struct myIntComp{
        bool operator()(int x, int y) const {
            return x%2==y%2;
        }
    };

    auto cmp = [](string &s1, string &s2){return s1.length() == s2.length();};
    // unordered_multiset<string, hash<string>, myComp> umst;
    unordered_set<int, hash<int>, myIntComp> umst1;
    // umst.insert("Hello");
    // umst.insert("Bello");
    // umst.insert("Hi");
    umst1.insert(1);
    umst1.insert(2);
    umst1.insert(8);
    umst1.insert(9);
    for(auto &x:umst1){
        cout << x << " ";
    }
    cout << endl;
    
    
    pair<unordered_set<int>::iterator, bool> pr2 = ust.insert(1);
    

    map<int, int> m;
    multimap<int, int, greater<int>> mm{{5, 10}, {1, 2}, {1, 3}, {2, 5}};
    cout << mm.find(1)->second<<endl; 
    pair<map<int, int>::iterator, bool> pr4 = m.insert({1,2});
    cout << pr4.first ->second<<" "<<pr4.second<<" hey\n";
    multimap<int, int>::iterator pr5 = mm.insert({1,2});
    cout << pr5->second <<" hey\n"<<endl;
    for(auto &x:mm) cout << x.first<<" "<<x.second<< endl;
    cout << endl;
    unordered_map<int, int> um;
    unordered_multimap<int, int> umm;

    um.emplace(2,3);
    cout << pq.top()<<endl;
    cout << um[2]<<endl;
    Test t(2,3);
    cout << t.x<<" "<<t.y<<endl;
    cout << dq[2]<<endl;



    
    // cout << myFunc(1, 2, greater<int>())<< " hey"<<endl;
    
    //  transform(v.begin(), v.end(), v.begin(), negate());
    // transform(v.begin(), v.end(), v.begin(), Add10());
    // transform(v.begin(), v.end(), arr, v.begin(), plus());
    // sort(fl.begin(), fl.end());
    // reverse(fl.begin(), fl.end()); 
    
    cout << "vector insert" << endl;
    v.assign({1,2,3});
    cout << *(v.insert(v.begin()+1, 3, 7)-1)<<endl;
    
    fl2=fl;
    for(int x:fl2) cout << x<<" ";
    cout <<endl;
    for(int x:v) cout << x<<" ";
    cout <<endl;
/*     f(i,10){
        cout<<v.size()<<" "<<v.capacity()<<endl;
        v.push_back(i);
    } */
    //auto it1 = next(l.begin(), 2);
    cout << v[1]<<endl;
    v.insert(v.begin(), 2, 10);
    sort(v.begin(), v.end(), less<int>());
    for(int x:v) cout <<x<<" ";
    cout <<endl;
    cout << arr[3]<<endl;

    cout << p.first<<" "<<p.second<<endl;
    cout << myMax(1000, 300)<<endl;
    cout << myMax<char>('b', 'a')<<endl;
    auto it1 = fl.begin();
    advance(it1, 2);
    cout << *(it1)<<endl;
    *find(v.begin(), v.end(), 4);
    vector<int>::iterator it = v.begin();
    cout <<*(it+1)<<endl;

    vector<int> v1{1,2,3,4};
    vector<int> v2{4,3,2,5,1,6};string s1;
    cout << is_permutation(v1.begin(), v1.end(), v2.begin());
    cout <<endl;

    cout << "string" <<endl;
    string sg ="hey";
    cout << (sg+" hello").length()<<endl;
    // getline(cin, sg, '$');
    cout << sg<<endl;

    string str, pat; char car[10];
    cin >> str;
    stringstream ss;
    ss << "3*4-5";
    int x1, y1, z1;
    ss>>x1>>y1>>z1;
    bool val = "1110000" < "111000";
    cout <<  val <<endl;
    str = "111000";
    cout << str.compare("1110000")<<endl;
    str = "100";
    cout << str.compare("10")<<endl;
    cout << ("100" < "10") <<endl; 
    cout << ("1110"<"111")<<endl;
    cout << "xyz: "<<x1<<y1<<z1<<endl;
    getline(cin, str, '$');
    cout << "str:"<<str<<endl;

    
    getline(ss, str, '$');
    cout << "str:"<<str<<endl;
    getline(ss, str, '$');
    cout << "str:"<<str<<endl;
    
 /*    getline(cin, str);
    cin >> pat;
    int pos = str.find(pat);
    while(pos!=string::npos){
        cout << pos<<" ";
        pos = str.find(pat, pos+1);
    }
    cout << endl;
    long long int z=-1;
    cout << __builtin_popcountll(z)<<endl;
    tuple<string, int, string> tp = make_tuple("gfg", 3, "hey");
    tuple<string, int> tp2("hello", 3);
    cout << get<0>(tp)<<endl;
    cout << tuple_size<decltype(tp)>::value<<endl;
    string xx; int yy; string zz;
    tie(xx, ignore, zz) = tp;
    cout <<xx<<" "<<yy<<" "<<zz<<endl; */
    return 0;
}
