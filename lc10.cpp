#include "leetcode.h"
using namespace std;

/* HEAP */
/* NEETCODE.IO */


// 02/01/2023 LC703-Easy: Kth largest element in a stream
// can improve by using make_heap to O(1) space but not worth it & you are modifying input. Don't overengineer.
// O(logn) for add. O(k+(n-k)logk) for the constructor. O(k) space.
class KthLargest {
    int k;
    // pq can't be reference becaue you can't bind reference to a temporary object.
    priority_queue<int, vector<int>, greater<int>> pq;
public:
    KthLargest(int k, vector<int>& nums) : k(k){
        // CPP move semantics in action as RHS is an rvalue. move constructor will be called instead of copy constructor.
        pq = priority_queue<int, vector<int>, greater<int>>(nums.begin(), nums.begin()+min(k, (int)nums.size()));

        for(int i=k;i<nums.size();i++){
            pq.push(nums[i]);
            pq.pop();
        }
    }
    
    int add(int val) {
        pq.push(val);
        if(pq.size()>k) pq.pop();
        return pq.top();
    }
};


// 02/01/2023 LC1046-Easy: Last Stone Weight
// TODO: LC1049-Medium: Last Stone Weight II
// O(nlogn)xO(n)
int lastStoneWeight(vector<int>& stones) {
    priority_queue<int> pq(stones.begin(), stones.end());
    while(pq.size()>1){
        int y = pq.top();
        pq.pop();
        int x = pq.top();
        pq.pop();

        if(x<y) pq.push(y-x);
    }
    return pq.empty()?0:pq.top();
}


// 02/01/2023 LC973-Medium: K Closest Points to Origin
// K smallest element aproach
// Alt: partial_sort(begin, begin+k, end, cmp) => gives all the k smallest elements [begin, begin+k)
// in sorted order in O(nlogk) time.
// If you don't want to modify input then copy it first => O(n) space
// O(n) avg x O(1). Because of quick select algorithm using kth element/k-1th index as pivot.  
vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
    auto cmp = [](const auto &p1, const auto &p2){return p1[0]*p1[0]+p1[1]*p1[1] < p2[0]*p2[0]+p2[1]*p2[1];};

    nth_element(points.begin(), points.begin()+k-1, points.end(), cmp);

    // Alt
    // partial_sort(points.begin(), points.begin()+k, points.end(), cmp);
    points.resize(k);
    return points;
}


// 02/01/2023 LC973-Medium: K Closest Points to Origin
// Maxheap based approach. No input changed.
// You can't use priority_queue or else you will have to O(klogk) pops at the end to return k elements then
// complexity is O(k+nlogk)
// O(k+(n-k)logk) x O(k). O(1) space if input is modified.
vector<vector<int>> kClosest_MH(vector<vector<int>>& points, int k) {
    auto cmp = [](const auto &p1, const auto &p2){return p1[0]*p1[0]+p1[1]*p1[1] < p2[0]*p2[0]+p2[1]*p2[1];};

    // O(k)
    vector<vector<int>> result(points.begin(), points.begin()+k);

    // O(k)
    make_heap(result.begin(), result.end(), cmp);

    // O((n-k)*logn)
    for(int i=k;i<points.size();i++){
        if(cmp(points[i], result[0])){
            pop_heap(begin(result), end(result), cmp);
            result.back() = points[i];
            push_heap(begin(result), end(result), cmp);
        }
    }
    
    return result;
}


// 02/01/2023 LC973-Medium: K Closest Points to Origin
// Minheap based approach. No input change.
// O(n+klogn)xO(n)
vector<vector<int>> kClosest_mh(vector<vector<int>>& points, int k) {
    auto cmp = [](const auto &p1, const auto &p2){return p1[0]*p1[0]+p1[1]*p1[1] > p2[0]*p2[0]+p2[1]*p2[1];};

    // O(n)xO(n)
    priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> pq(points.begin(), points.end(), cmp);

    vector<vector<int>> result(k);

    // O(klogn)
    for(int i=0;i<k;i++){
        result[i] = move(pq.top());
        pq.pop();
    }
    
    return result;
}




// 02/01/2023 LC215-Medium: Kth Largest Element in an array
// O(n+klogn)xO(n). If modification of input is allowed used make_heap() => O(n+klogn)xO(1) space.
// Better than sorting (nlogn) when k is small.
int findKthLargest(vector<int>& nums, int k) {

    // Alt: O(n) avg x O(1). Quick Select approach. Modifies input    
    // nth_element(nums.begin(), nums.begin()+k-1, nums.end(), greater());
    
    // Alt: O(nlogk)xO(1). First k elements are sorted. Modifies input
    // partial_sort(nums.begin(), nums.begin()+k, nums.end(), greater());

    priority_queue<int, vector<int>> pq(nums.begin(), nums.end());

    while(k-->1){
        pq.pop();
    }

    return pq.top();
}


int partition(vector<int> &nums, int start, int end){
    if(start==end) return start;
    int idx = start + rand()%(end-start+1);
    swap(nums[idx], nums[end]);
    int j=start-1;
    for(int i=start;i<end;i++){
        // make it > for kth largest. Here we are doing (n-k)idx smallest element
        if(nums[i]<nums[end]) swap(nums[i], nums[++j]);
    }
    swap(nums[++j], nums[end]);
    return j;
}

// 02/01/2023 LC215-Medium: Kth Largest Element in an array
// Like quick sort you don't recurse on both sides of pivot. Hence iterative is easy.
// O(N) avg x O(1). O(N) becaues assuming pivot at the half => N + N/2 + N/4... summation is utmost 2N.
// For random pivot you have uneven splists & say you have your k elements in larger split say (3N/4 & not N/4)
// That will also be GP which will converge to some O(N) like 3N or 4N etc.,
// Worst case is N + N-1 + N-2 + .... => O(N^2) when pivot always leaves behind N-1 elements.
int findKthLargest_qs(vector<int>& nums, int k) {
    srand(time(NULL));
    // passing the n-k is the index of the kth largest element
    k = nums.size()-k;

    int start=0, end = nums.size()-1;
    while(start < end){
        int pivot = partition(nums, start, end);
        if(pivot == k) return nums[k];
        else if(pivot>k) end = pivot-1;
        else start = pivot+1;
    }    

    return nums[k]; // start == end == k.
}


// 03/01/2023 LC621-Medium: Task Scheduler
// Alt: you can also simulate by keeping a cur_time counter
// O(m)xO(1). where m is size of tasks. Heap space/time are O(log26)xO(26)~O(1)xO(1)
int leastInterval(vector<char>& tasks, int n) {
    int freq[26] = {};
    int ans=0;
    for(char c:tasks){
        freq[c-'A']++;
    }

    // Choose most frequent task greedily among the ready tasks.
    // Each push & pop is O(log(26)) i.e O(1)
    priority_queue<int> pq;
    queue<int> q;

    for(int i=0;i<26;i++){
        if(freq[i]) pq.push(freq[i]);
    }

    while(pq.size()){
        int k = n+1;
        while(pq.size() && k){
            if(pq.top()>1) q.push(pq.top()-1);
            pq.pop();
            ans++;
            k--;
        }
        while(q.size()){
            pq.push(q.front());
            q.pop();
        }
        
        if(pq.size()) ans+=k;
    }
    return ans;
}


// 03/01/2023 LC621-Medium: Task Scheduler
// Doesn't simulate just directly calculates value.
// O(m)xO(1)
int leastInterval_alt(vector<char>& tasks, int n) {
    int freq[26] = {};
    int ans=0, max=0, maxCount=0;
    for(char c:tasks){
        freq[c-'A']++;
        if(freq[c-'A']>max){
            max = freq[c-'A'];
            maxCount=1;
        }
        else if(freq[c-'A']==max){
            maxCount++;
        }
    }

    // Think of max freq element partitioning the time. 
    // And if there are multiple elements with same max frequency they can be put adjancent but it will eat
    // up 1 empty slot in every partition.
    int emptySlots = (max-1)*(n-(maxCount-1));
    int availableTasks = int(tasks.size()) - max*maxCount;
    int idle = std::max(0, emptySlots-availableTasks);
    // if idle<0 it means all the extra tasks can be inserted in each partition since
    // freq of all those elemnts are < max they fit by inserting one per each partition
    // since there are max-1 partitions. No more idle time.
    return tasks.size()+idle;
}


// 03/01/2023 LC355-Medium: Design Twitter
// Alt: You can store tweets as ump<userId, vector<tweetId, time>> then in pq insert <tweetId, time, followeeId, nextIdx>
class Twitter {

    struct TweetNode{
        int tweetId, time;
        TweetNode* next;
        TweetNode(int tweetId, int time):tweetId(tweetId), time(time), next(nullptr){
            
        }
    };

    unordered_map<int, unordered_set<int>> graph;
    unordered_map<int, TweetNode*> tweets;
    int time;

public:
    Twitter() {
        time=0;
    }
    
    // O(1)
    void postTweet(int userId, int tweetId) {
        TweetNode *node = new TweetNode(tweetId, ++time);
        node->next = tweets[userId];
        tweets[userId] = node;
    }
    
    // O(k + 10logk) where k be # of people userId is following
    vector<int> getNewsFeed(int userId) {

        auto cmp = [](auto &x, auto &y){return x->time<y->time;};
        
        vector<TweetNode*> maxHeap;
        if(tweets[userId]) maxHeap.push_back(tweets[userId]);        
        for(int v: graph[userId]){
            if(tweets[v]) maxHeap.push_back(tweets[v]);
        }
        
        vector<int> result;
        auto start = maxHeap.begin();
        int n = maxHeap.size();

        // O(k)
        make_heap(start, start+n, cmp);

        // O(10logK)
        for(int i=0;i<10 && n>0;i++){
            result.push_back(maxHeap[0]->tweetId);
            pop_heap(start, start+n, cmp);
            if(maxHeap[n-1]->next){
                maxHeap[n-1] = maxHeap[n-1]->next;
                push_heap(start, start+n, cmp);
            }
            else n--;
        }
        return result;
    }
    
    // O(1)
    void follow(int followerId, int followeeId) {
        graph[followerId].insert(followeeId);
    }
    
    // O(1)
    void unfollow(int followerId, int followeeId) {
        graph[followerId].erase(followeeId);
    }
};


// 03/01/2023 LC295-Hard: Find median from data stream
// TODO: FOLLOWUP
// O(logn) for addNum. O(1) for find Median.
class MedianFinder {

    priority_queue<int> pq1;
    priority_queue<int, vector<int>, greater<int>> pq2;
    
public:
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        if(pq1.empty() || pq1.top()>num){
            pq1.push(num);
            if(pq1.size()-pq2.size()>1){
                pq2.push(pq1.top());
                pq1.pop();
            }
        }
        else{
            pq2.push(num);
            if(pq2.size()>pq1.size()){
                pq1.push(pq2.top());
                pq2.pop();
            }
        }
    }
    
    double findMedian() {
        if(pq1.size()>pq2.size()) return pq1.top();
        else return (pq1.top()+pq2.top())/2.0;
    }
};


int main(int argc, char const *argv[])
{

    vector<char> tasks = {'A', 'A', 'A', 'B', 'B', 'B'};
    cout << leastInterval(tasks, 2) << endl;
    return 0;
}