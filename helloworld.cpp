#include <bits/stdc++.h>

#define f(i,n) for(int i=0;i<n;i++)
#define hyp(a,b) sqrt(a*a+b*b)

using namespace std;


bool find_x(int arr[], int n, int x){
    if(n<=0)return false;
    return arr[n-1] == x || find_x(arr, n-1, x);
}

bool is_palindrome(string s){
    if(s.length()<=1)return true;
    return s[0]==s[s.length()-1] && is_palindrome(s.substr(1, s.length()-2));
}

int digit_sum(int n){
    if(n<10)return n;
    return n%10 + digit_sum(n/10);
}

void tohanoi(int n, char from_rod, char aux_rod, char to_rod){
    if(n==0)return;
    tohanoi(n-1, from_rod, to_rod, aux_rod);
    cout << "Move Disk "<<n<<" from "<<from_rod<<" to rod "<<to_rod<<endl;
    tohanoi(n-1, aux_rod, from_rod, to_rod);    
}

int ropeCut(int n, int a, int b, int c){
    if(n==0) return 0;
    if(n<0) return INT_MIN;
    return max({1+ropeCut(n-a, a, b, c), 1+ropeCut(n-b, a, b, c), 1+ropeCut(n-c, a, b, c)});
}

bool subz(int arr[], int n){
    partial_sum(arr, arr+n, arr);
    unordered_set<int> set;
    f(i,n){
        if(!arr[i])return true;
        auto x = set.emplace(arr[i]);
        if(!x.second)return true;
    }
    return false;
}

bool subk(int arr[], int n, int k){
    if(arr[0]==k)return k;
    partial_sum(arr, arr+n, arr);
    unordered_set<int> set;
    for_each(arr, arr+n, [&set](int x){set.emplace(x);});
    
    f(i,n){
        auto it = set.find(arr[i]+k);
        if(it==set.end()){
            set.erase(arr[i]);
        }
        else{
            for(int j=i+1;j<n;j++){
                cout <<j<<" ";
                if(arr[j]==arr[i]+k)break;
            }
            return true;
        }
    }
    if(set.size()==0)return false;
    else return true;
}

void sub_eq01(vector<int> &v){
    //equivalent to longest zero sum
    int cur_sum=0;
    int start_idx=-1, end_idx=-1;
    int size=0;

    unordered_map<int, int> set;
    f(i, v.size()){
        if(v[i])cur_sum++;
        else cur_sum--;
        if(cur_sum==0){
            start_idx=0;
            end_idx=i;
            size = i+1;
        }
        if(!set.emplace(cur_sum, i).second){
            if(i-set[cur_sum]>size){
                start_idx = set[cur_sum]+1;
                end_idx = i;
                size = i-set[cur_sum];
            }
        }

    }
    if(size==0) cout <<"Not Found";
    else
    cout << "size: "<<size<<" "<<start_idx<<" "<<end_idx<<endl;
}

int recursive_bs(vector<int> &v, int key, int start, int end){
    if(start > end) return -1;
    int mid = (start+end)/2;
    if(v[mid]==key)return mid;
    else if(v[mid]>key) return recursive_bs(v, key, start, mid-1);
    else return recursive_bs(v, key, mid+1, end);
}

int iterative_bs(vector<int> &v, int key){
    int start = 0, end = v.size()-1, mid;
    while(true){
        if(start > end){return -1;}
        mid = (start+end)/2;
        if(v[mid]==key) return mid;
        else if(v[mid] > key){
            end = mid-1;
        }
        else if(v[mid]<key){
            start = mid+1;
        }
    }
}

int recursive_ts(vector<int> &v, int key, int start, int end){
    if(start > end)return -1;
    int mid1 = start + (end-start)/3;
    int mid2 = start + 2*(end-start)/3;
    cout << mid1 << " " << mid2<< endl;
    if(v[mid1]==key)
        return mid1;
    if(v[mid2]==key)
        return mid2;
    
    if(v[mid1]>key)return recursive_ts(v, key, start, mid1-1);
    if(v[mid2]<key)return recursive_ts(v, key, mid2+1, end);
    return recursive_ts(v, key, mid1+1, mid2-1);
}

int first_occurence(vector<int> &v, int key, int start, int end, int last=INT_MAX){
    if(start > end) return last;
    int mid = (start+end)/2;
    if(v[mid]==key){
        last = min(last, mid);
        return first_occurence(v, key, start, mid-1, last);
    }

    if(v[mid]<key){
        return first_occurence(v, key, mid+1, end, last);
    }
    else{
        return first_occurence(v, key, start, mid-1, last);
    }
}

int last_occurence(vector<int> &v, int key, int start, int end, int last=INT_MIN){
    if(start > end) return last;
    int mid = (start+end)/2;
    if(v[mid]==key){
        last = max(last, mid);
        return last_occurence(v, key, mid+1, end, last);
    }

    if(v[mid]<key){
        return last_occurence(v, key, mid+1, end, last);
    }
    else{
        return last_occurence(v, key, start, mid-1, last);
    }
}

void insertion_sort(vector<int> &v){
    for(int i=1;i<v.size();i++){
        int min = v[i];
        int j = i-1;
        // if you make v[j]>=min then it won't be stable
        while(j>=0 && v[j]>min){
            v[j+1] = v[j];
            j--;
        }
        v[j+1]=min;
    }
}

vector<int>::iterator upper_bound(vector<int>::iterator start, vector<int>::iterator end, int key){
    auto null_itr = end;
    auto it = null_itr;
    while(start<end){
        auto mid = start+(end-start-1)/2;
        if(*mid<=key){
            start = mid+1;
            continue;
        }
        else{
            if(it==null_itr)it = mid;
            else if(*it>*mid){
                it = mid;
            }
            end = mid-1;
            continue;
        }
    }
    return it;
}

void binary_insertion_sort(vector<int> &v){
    for(int i=1;i<v.size();i++){
        int insert_idx = upper_bound(v.begin(), v.begin()+i, v[i]) - v.begin();
        cout << insert_idx<<endl;
        int min = v[i];
        int j = i-1;
        while(j>=insert_idx){
            v[j+1] = v[j];
            j--;
        }
        v[j+1]=min;
    }
}

void bubble_sort(vector<int> &v){
    for(int i=0;i<v.size()-1;i++){
        for(int j=0;j<v.size()-i-1;j++){
            if(v[j]>v[j+1])swap(v[j], v[j+1]);
        }
    }
}

void selection_sort(vector<int> &v){
    int min;
    for(int i=0;i<v.size();i++){
        min = i;
        for(int j=i+1;j<v.size();j++){
            if(v[j]<v[min])min = j;
        }
        swap(v[min], v[i]);
    }
}

// O(m+n) x O(m+n)
void merge(vector<int> &v, int start, int mid, int end){
    int arr[end-start+1];
    int i=start, j=mid+1, idx=0;
    while(i<=mid && j<=end){
        if(v[i]<v[j]){
            arr[idx++]=v[i++];
        }
        else{
            arr[idx++]=v[j++];
        }
    }

    while(i<=mid){
        arr[idx++]=v[i++];
    }

    while(j<=end){
        arr[idx++]=v[j++];
    }

    for(int i=0; i<=end-start;i++){
        v[start+i]=arr[i];
    }
}

//O(nlogn)xO(n)
void merge_sort(vector<int>& v, int start, int end){
    if(start==end){
        return;
    }
    int mid = (start+end)/2;
    merge_sort(v, start, mid);
    merge_sort(v, mid+1, end);
    merge(v, start, mid, end);
}

//Bottom up iterative implementation of merge_sort. Just call-stack optimized. O(1) space for LL.
// O(nlogn) x O(n) 
void merge_sort_i(vector<int> &v){
    int step = 1, left=0, mid, right;
    while(step<v.size()){

        while(left<v.size()){
            mid = left+step;
            if(mid>=v.size()) break;

            right = mid+step-1;
            if(right>=v.size()) right = v.size()-1;

            merge(v, left, mid-1, right); //mid-1 b/o reusing merge function which takes [0,mid] (mid, right]

            left = right+1;
        }

        left=0;
        step = step<<1;
    }
}

int partition(vector<int>& v, int start, int end){
    int pivot = v[end];

    int j=start-1;
    for(int i = start; i<end; i++){
        // all elements >=pivot are partitioned to be after pivot.
        if(v[i]<pivot){
            swap(v[++j], v[i]);
        }
    }

    swap(v[j+1], v[end]);
    return j+1;
}

int partition_hoare(vector<int>& v, int start, int end){
    int pivot = v[start];
    int i=start, j=end;
    while(true){
        while(v[i]<pivot){
            i++;
        }
        while(v[j]>pivot){
            j--;
        }
        if(i>=j)return j;
        swap(v[i++], v[j--]);
    }

    return j;
}

// O(nlogn) avg x O(1)
void quick_sort(vector<int>& v, int start, int end){
    if(start >= end)return;
    // int part_idx = partition(v, start, end);
    // quick_sort(v, start, part_idx-1);
    // quick_sort(v, part_idx+1, end);
    int part_hoare = partition_hoare(v, start, end);
    quick_sort(v, start, part_hoare);
    quick_sort(v, part_hoare+1, end);
}

void counting_sort(vector<int>& v){
    int max = *max_element(v.begin(), v.end()), min = *min_element(v.begin(), v.end()); 
    int count[max-min+1]={0};
    int output[v.size()];
    for(int a:v)count[a-min]++;
    partial_sum(count, count+(max-min+1), count);

    for(int i=v.size()-1;i>=0;i--){
        output[--count[v[i]-min]]=v[i];
    }

    copy(output, output+v.size(), v.begin());
}

void radix_sort(vector<int>& v){
    int max_digits = log10(*max_element(v.begin(), v.end()))+1;

    for(int place=1;place<pow(10, max_digits);place*=10){
        int count[10] = {0};
        int output[v.size()];
        for(int a:v){
            count[(a/place)%10]++;
        }
        partial_sum(count, count+10, count);
        for(int i=v.size()-1;i>=0;i--){
            output[--count[(v[i]/place)%10]]=v[i];
        }
        copy(output, output+v.size(), v.begin());
    }
}

void bucket_sort(vector<int>& v, int num){
    vector<int> buckets[num];
    int max = *max_element(v.begin(), v.end())+1;
    for(int a:v){
        buckets[(num*a)/max].push_back(a);
    }
    for(auto &a:buckets){
        sort(a.begin(), a.end());
    }
    int idx=0;
    for(auto &a:buckets){
        copy(a.begin(), a.end(), v.begin()+idx);
        idx+=a.size();
    }
}

// O(N) x O(1)
void deduplicate(vector<int>& v){
    int j=-1;
    for(int i=1;i<v.size();i++){
        if(v[i]!=v[i-1]){
            v[++j]=v[i-1];
        }
    }
    v[++j] = v[v.size()-1];
    v.resize(j+1);
}

void union_sorted(vector<int>& v1, vector<int>& v2){
    
    //O(n1+n2) avg x O(n1+n2)
    /* unordered_set<int> u(v1.begin(), v1.end());
    u.insert(v2.begin(), v2.end());
    for(int a:u)cout <<a << " ";
    cout << endl;
     */

    //O(n1+n2) x O(1);
    int i=0, j=0;
    // deduplicate(v1);
    // deduplicate(v2);
    while(i<v1.size() && j<v2.size()){
        if(v1[i]<v2[j]){
            cout << v1[i++]<<" ";
            while(v1[i]==v1[i-1] && i<v1.size())i++;
        }
        else if(v2[j]<v1[i]){
            cout << v2[j++]<<" ";
            while(v2[j]==v2[j-1] && j<v2.size())j++;
        }
        else{
            i++;
        }
    }

    while(i<v1.size()){
         while( i > 0 && v1[i]==v1[i-1] && i<v1.size())i++;
        cout << v1[i++]<< " ";
    }

    while (j<v2.size()){
        while(j>0 && v2[j]==v2[j-1] && j<v2.size())j++;
        cout << v2[j++]<< " ";
    }
    cout <<endl;
}

void intersect_sorted(vector<int>& v1, vector<int>& v2){
    
    // O(n1+n2) avg x O(n1+n2) 
    /* unordered_set<int> u(v1.begin(), v1.end()), v(v2.begin(), v2.end());
    for(int a:v){
        if(!u.insert(a).second){
            cout << a << " ";
        }
    }
    cout << endl; */

    //O(n1+n2) x O(1);
    int i=0, j=0;
    deduplicate(v1);
    deduplicate(v2);
    while(i<v1.size() && j<v2.size()){
        if(v1[i]<v2[j]){
            i++;
        }
        else if(v2[j]<v1[i]){
            j++;
        }
        else{
            cout << v1[i]<<" ";
            i++; j++;
        }
    }
    cout << endl;
}

int merge_inversions(vector<int>& v, int start, int end, int mid){
    int i=start, j=mid+1, k=0, inv=0;
    int output[end-start+1];
    while(i<=mid && j<=end){
        if(v[i]>v[j]){
            output[k++]=v[j++];
            inv+=(mid-i+1);
        }
        else{
            output[k++]=v[i++];
        }
    }
    while(i<=mid)output[k++]=v[i++];
    while(j<=mid)output[k++]=v[j++];
    copy(output, output+(end-start+1), v.begin()+start);
    return inv;
}

int count_inversions(vector<int>& v, int start, int end){
    if(start>=end)return 0;

    int mid = (start+end)/2, inv=0;
    inv+=count_inversions(v, start, mid);
    inv+=count_inversions(v, mid+1, end);
    inv+=merge_inversions(v, start, end, mid);
    return inv;
}

int partition_k(vector<int>& v, int start, int end){
    if(start==end) return start;
    int part_idx = start + rand()%(end-start+1);
    swap(v[part_idx], v[end]);
    
    int pivot = v[end];

    int j=start-1;
    for(int i=start; i<end; i++){
        if(v[i]<pivot){
            swap(v[++j], v[i]);
        }
    }
    swap(v[j+1], v[end]);
    return j+1;
}

//iterative is also simple
int quickselect(vector<int>& v, int start, int end, int k){
    if(start>end) return -1;
    int part_idx = partition_k(v, start, end);
    if(part_idx==k-1) return v[part_idx];
    else if(part_idx<k-1){
        return quickselect(v, part_idx+1, end, k);
    }
    else{
        return quickselect(v, start, part_idx-1, k);
    }
}

void sort012(vector<int>& v){
    int type0=0, type1=0, type2=v.size()-1;
    while(type1<type2){
        if(v[type0]==2){
            swap(v[type0], v[type2]);
            type2--;
        }
        else if(v[type0]==1){
            swap(v[type1+1], v[type0]);
            type1++;
        }
        else{
            type0++;
        }
    }
}


void merge_intervals(vector<pair<int, int>>& v){
    if(v.empty())return;
    sort(v.begin(), v.end(), [](pair<int, int> x, pair<int, int> y){return x.first < y.first;});

    int merge_idx = 0;
    for(int i=1;i<v.size();i++){
        if(v[merge_idx].second >= v[i].first){
            v[merge_idx].second = max(v[merge_idx].second, v[i].second);
        }
        else{
            v[++merge_idx] = v[i];
        }
    }
    f(i, merge_idx+1)
    cout << "{"<<v[i].first<<","<<v[i].second<<"} ";
}

void max_guests(vector<int>& entry, vector<int>& exit){
    if(entry.size()!=exit.size() || exit.size()==0) return;
    
    //O(nlogn)xO(1)
    /* sort(entry.begin(), entry.end());
    sort(exit.begin(), exit.end());
    int time=0, cur_guests=0, max_guests=0, i=0, j=0;
    while(i<entry.size()){
        if(entry[i]<=exit[j]){
            cur_guests++;
            if(cur_guests>max_guests){
                max_guests = cur_guests;
                time = entry[i];
            }
            i++;
        }
        else{
            cur_guests--;
            j++;
        }
    }
    cout << time << endl; */

    //O(max_depart_time)xO(max_depart_time)
    int max = *max_element(exit.begin(), exit.end());
    int arr[max+1]={0};
    f(i,entry.size()){
        arr[entry[i]]++;
        arr[exit[i]]--;
    }
    int cur_guests=0, max_guests=0, time=0;
    f(i,max+1){
        cur_guests+=arr[i];
        if(cur_guests>max_guests){
            max_guests=cur_guests;
            time = i;
        }
    }
    cout << time<<endl;
}

int main(){
    int n;
    cin >>n;
    vector<int> v(n);
    f(i,n)cin>> v[i];

    srand(time(nullptr));
    /* int n1, n2;
    cin >> n1 >> n2;
    vector<int> v1(n1), v2(n2);
    f(i,n1)cin >> v1[i];
    f(i,n2)cin >> v2[i];  */
    
    /* int n;
    cin >> n;
    vector<pair<int, int>> v(n);
    f(i,n)cin >> v[i].first >> v[i].second; */

    /* int n;
    cin >> n;
    vector<int> entry(n), exit(n);
    f(i,n) cin >> entry[i];
    f(i,n) cin >> exit[i]; */
    // insertion_sort(v);
    // bubble_sort(v);
    // selection_sort(v);
    // binary_insertion_sort(v);
     merge_sort(v, 0, v.size()-1);
    // quick_sort(v, 0, n-1);
    // counting_sort(v);
    // radix_sort(v);
    // bucket_sort(v, 5);
    // merge_sort_i(v);
    f(i,n)cout <<v[i]<<" ";
    cout << endl;

    /* vector<int> un, in;
    union_sorted(v1, v2);
    intersect_sorted(v1, v2); */

    // cout << count_inversions(v, 0, n-1);

    // cout << quickselect(v, 0, v.size()-1, 4);
    // sort012(v);

    // merge_intervals(v);

    //max_guests(entry, exit);



    // f(i,n)cout<<v[i]<<" ";
}