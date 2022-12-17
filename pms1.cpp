#include <bits/stdc++.h>
#define f(i,n) for(int i=0; i<n; i++)

using namespace std;


// O(nk)xO(n). There is better O(n) solution.
// Alt: circular array using mod. Same complexity.
int josephus(int n, int k){
    list<int> l;
    f(i,n){
        l.push_back(i);
    }

    auto it = l.begin();
    while(l.size()>1){
        int num=k-1;
        while(num--){
            if(++it==l.end()){
                it = l.begin();
            }
        }
        it=l.erase(it);
        if(it==l.end()){
            it = l.begin();
        }
    }
    return *it;
}

/// @brief Print max of all sub-arrays of size k
/// O(n)xO(k). Since every element is added/removed at most once i.e 2n ops 
/// Naive is O(nk)xO(1)
void print_maxsubk(vector<int> &v, int k){
    deque<int> dq;
    f(i, k){
        while(!dq.empty() && v[dq.back()]<=v[i])
            dq.pop_back();
        dq.push_back(i);
    }

    for(int i=k;i<v.size();i++){
        cout << v[dq.front()]<<" ";

        if(!dq.empty() && dq.front()<=i-k)
            dq.pop_front();

        while(!dq.empty() && v[dq.back()]<=v[i])
            dq.pop_back();
        dq.push_back(i);
    }
    cout <<v[dq.front()]<<endl;
}


int partition(vector<int> &v, int start, int end){
    if(start==end) return start;
    swap(v[start+rand()%(end-start+1)], v[end]);
    int i=start-1;
    for(int j=start;j<end;j++){
        if(v[j]<v[end]){
            swap(v[++i], v[j]);
        }
    }
    swap(v[i+1], v[end]);
    return i+1;
}

// Naive: O(nlogn)
// MaxHeap: O(n + klogn) => O(n) for builHeap + klogn for extracting k largest. For small k O(n+logn) for large k O(n+nlogn)
// MinHeap: O(k + (n-k)logk)
// O(n) average b/o QuickSelect type approach.
void kLargestNums(vector<int> &v, int k, int start, int end){
    if(start>end) return;
    int pivot_idx = partition(v, start, end);
    if(pivot_idx==v.size()-k){
        for(int i=pivot_idx;i<v.size();i++) cout << v[i]<<" ";
        cout << endl;
    }
    else if(pivot_idx<v.size()-k){
        kLargestNums(v, k, pivot_idx+1, end);
    }
    else{
        kLargestNums(v, k, start, pivot_idx-1);
    }
}

// MinHeap based soln: O(k + (n-k)logk). When k=n-1 => O(n+logn) and when k is small O(n)
// Technically here we are assuming print all k elements of minheap is O(k) since no need to extract and order
// doesn't matter. But cpp doesn't allow it.
// O(k+nlogk)
void kLargestNums(vector<int> &v, int k){
    if(v.size()<k) return;

    priority_queue<int, vector<int>, greater<int>> pq(v.begin(), v.begin()+k);
    for(int i=k;i<v.size();i++){
        if(v[i]>pq.top()){
            pq.pop();
            pq.push(v[i]);
        }
    }

    while(!pq.empty()){
        cout << pq.top()<<" ";
        pq.pop();
    }
    cout <<endl;    
}

// Max unique elements you can buy from a sum
// O(count x logn)
int purchaseMaxUnique(vector<int> &v, int sum){
    priority_queue<int, vector<int>, greater<int>> pq(v.begin(), v.end());
    int count=0;
    while(sum>0 && !pq.empty() && pq.top()<=sum){
        count++;
        sum-=pq.top();
        pq.pop();
    }
    return count;
}

// maxheap with max element based on p.second and if equal smallest element based on p.first on the top
struct myComp{
    bool operator()(pair<int, int> &p1, pair<int, int> &p2){
        if(p1.second==p2.second) return p1.first>p2.first;
        return p1.second< p2.second;
    }
};

// O(n +klogn) using hashmap & pq.
// O(n) using freq indexing
void kMostFrequent(vector<int> &v, int k){
    unordered_map<int, int> ump;
    //O(n)
    for(int i=0;i<v.size();i++){
        ump[v[i]]++;
    }
/* 
    // O(n)
    priority_queue<pair<int, int>, vector<pair<int, int>>, myComp> pq(ump.begin(), ump.end());

    //O(klogn)
    while(!pq.empty() && k-->0){
        cout << pq.top().first << " ";
        pq.pop();
    }
    cout << endl;
 */
    //Freq indexing solution. Prints in any order if same freq
/*     vector<int> freqIdx[v.size()+1];
    for(auto &x:ump){
        freqIdx[x.second].push_back(x.first);
    } */

    //Freq indexing solution. Prints in the order of apperance of original array
    vector<int> freqIdx[v.size()+1];
    for(int i=0;i<v.size();i++){
        if(ump[v[i]]){
            freqIdx[ump[v[i]]].push_back(v[i]);
            ump[v[i]]=0;
        }
    }

    for(int i=v.size();i>=0 && k>0; i--){
        for(int j=0;j<freqIdx[i].size() && k>0;j++){
            cout <<freqIdx[i][j]<<" ";
            k--;
        }
    }
    cout << endl;
}

//O(nlogn)xtheta(n)
// YOu can't sort b/o order changes.
void printCeilOnRight(vector<int> &v){
    stack<int> sk;
    set<int> st;
    for(int i=v.size()-1;i>=0;i--){
        auto it = st.lower_bound(v[i]);
        if(it == st.end()){
            sk.push(-1);
        }
        else{
            sk.push(*it);
        }
        st.emplace(v[i]);
    }

    while(!sk.empty()){
        cout << sk.top()<<" ";
        sk.pop();
    }
    cout << endl;
}

// O(nlogn)xO(n)
void printGreater(vector<int> &v){
    map<int, int> mp;
    for(auto &x:v) mp[x]++;
    int freq=0, sum_freq=0;
    for(auto it=mp.rbegin();it!=mp.rend();it++){
        freq = it->second;
        it->second = sum_freq;
        sum_freq+=freq;
    }

    for(auto &x: v){
        cout << mp[x]<<" ";
    }
    cout << endl;

    //sort & BS approach
    vector<int> sorted_v(v);
    sort(sorted_v.begin(), sorted_v.end());
    for(auto &x:v){
        auto it = upper_bound(sorted_v.begin(), sorted_v.end(), x);
        cout << sorted_v.end()-it<<" ";
    }
    cout << endl;
}

// Naive sorting O(mnlogmn) x O(mn) - to make another 1D array
// O(mnlogm) x O(m) use priority_queue in merge k lists style. Stop popping when you pop the median (mn/2+1)th element.
// Do quickselect O(mn) avg x O(mn) to get median.
// Best: O(mlog(maxElem-minElem)logn) x O(1) => uses the already sorted property of rows.
// Assuming odd sized matrix but similar logic for even sized (avg of two). Odd sized => unique median.
int medianRowSortedMatrix(int **mat, int m, int n){
    int min=mat[0][0], max = mat[0][n-1];
    f(i,m) {
        min = std::min(min, mat[i][0]);
        max = std::max(max, mat[i][n-1]);
    }

    int medPos = (m*n+1)/2;
    // While loop runs for O(log(max-min)) times.
    while(min<max){
        int mid = (min+max)/2;
        int midPos = 0;
        // takes O(mlogn);
        f(i,m){
            midPos += upper_bound(mat[i], mat[i]+n, mid)-mat[i];
        }

        // Ensures that we don't miss any element and median if present must be b/w [min, mid].
        // But odd sized matrix must have a median. So when min==max it must be median present in the matrix.
        if(midPos<medPos) min = mid+1;
        else max = mid;
    }
    return min;
}

// O(nlogn)xO(1) assuming sort space complexity is O(1)
// Given the capacity you have to pickup maximum value of items.
// The items are divisible i.e you can collect fractional weight
int fractionalKnapsack(vector<pair<int, int>> &weightNValues, int capacity){
    sort(weightNValues.begin(), weightNValues.end(), [](auto &x, auto &y){return (float(x.second)/x.first)>(float(y.second)/y.first);});
    int valueCollected=0;
    for(int i=0;i<weightNValues.size() && capacity>0;i++){
        int capacityCollected = min(capacity, weightNValues[i].first);
        valueCollected+=capacityCollected*(float(weightNValues[i].second)/weightNValues[i].first);
        capacity-=capacityCollected;
    }
    return valueCollected;
}

// O(nlogn)xO(1). Each child should get 1 chocolate bag. Diff b/w max and min chocolates obtained
// by children should be minimum.
int chocolateDistribution(vector<int> &chocolateBags, int children){
    if(!children || !chocolateBags.size()) return 0;
    sort(chocolateBags.begin(), chocolateBags.end());
    int minDiff=INT_MAX;
    for(int i=0, j=children-1;j<chocolateBags.size();i++, j++){
        minDiff = min(minDiff, chocolateBags[j]-chocolateBags[i]);
    }
    if(minDiff==INT_MAX) return chocolateBags[chocolateBags.size()-1];
    return minDiff;
}

// O(nlogn)xO(n)
vector<int> sortElembyFreq(vector<int> &v){
    unordered_map<int, int> mp;
    for(int x:v)mp[x]++;
    vector<pair<int, int>> vp(mp.begin(), mp.end());
    sort(vp.begin(), vp.end(), [](auto &x, auto &y){return x.second==y.second?x.first<y.first:x.second > y.second;});
    int i=0;
    for(auto &x:vp){
        while(x.second--) v[i++]=x.first;
    }
    return v;
}

int main(int argc, char const *argv[])
{
    srand(time(nullptr));
    /* int n;
    cin >> n;
    vector<int> v(n);
    f(i,n) cin>>v[i];
    sortElembyFreq(v);
    
    f(i,n)cout << v[i]<<" ";
    cout << endl; */

    // cout << chocolateDistribution(v, 5)<<endl;

/*     int n, k;
    cin >> n >> k;
    vector<pair<int, int>> weightNValues;
    f(i,n){
        int x, y;
        cin >> x >> y;
        weightNValues.push_back({x, y});
    }
    cout << fractionalKnapsack(weightNValues, k)<<endl;; */
    
    int m,n;
    cin >> m >> n;
    int *arr[m];
    for(int i=0;i<m;i++) arr[i] = new int[n];
    f(i,m)f(j,n)cin >> arr[i][j];

    cout << medianRowSortedMatrix(arr, m, n)<<endl;;

    
    // printGreater(v);
    // printCeilOnRight(v);
    // kLargestNums(v, 3, 0, n-1);
    // kLargestNums(v, 3);
    // cout << purchaseMaxUnique(v, 10) << endl;
    // kMostFrequent(v, 2);
    // stock_span(v);
    // cout << balanced_paranthesis("([])")<<endl;
    // print_maxsubk(v, 3);
    // cout << josephus(7, 3)<<endl;

    return 0;
}
