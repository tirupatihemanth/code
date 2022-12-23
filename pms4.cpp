#include<bits/stdc++.h>
using namespace std;

/* GRAPHS */
/* GFG */

// 17/12/2022 BFS of an undirected connected graph given a source(s)
// O(V+E)xO(V). You go through adj list of all vertices i.e Σdegree(v) = E + push/pop every vertex i.e O(V)
void bfs(const vector<int> adj[], int n, int s){
    bool visited[n] = {};
    queue<int> q;
    q.push(s);
    visited[s]=true;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        cout << u << " ";
        for(auto &v: adj[u]){
            if(!visited[v]){
                visited[v]=true;
                q.push(v);
            }
        }
    }
    cout << endl;
}


// 18/12/2022 Breadth First Search of a disconnected undirected graph
// Return # of islands in a graph aka # of connected components in a graph.
// O(V+E)xO(V).
int bfs_dis(const vector<int> adj[], int n){
    int count=0;
    queue<int> q;
    bool visited[n] = {};
    for(int s=0;s<n;s++){
        if(visited[s]) continue;
        count++;
        q.push(s);
        visited[s] = true;
        while(!q.empty()){
            int u = q.front();
            cout << u << " ";
            q.pop();
            for(int v:adj[u]){
                if(!visited[v]){
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        cout << endl;
    }
    return count;
}

// 18/12/2022 DFS of an undirected connected graph given a source
void dfs(vector<int> adj[], int s, bool visited[]){
    visited[s] = true;
    cout << s << " ";
    for(int v: adj[s]){
        if(visited[v]) continue;
        dfs(adj, v, visited);
    }
}


// 18/12/2022 DFS traversal of an undirected disconnected graph. Returns #of connected components in a graph.
// O(V+E)xO(V)
int dfs_dis(vector<int> adj[], int n){
    bool visited[n];
    fill(visited, visited+n, false);
    int count=0;
    for(int i=0;i<n;i++){
        if(visited[i]) continue;
        dfs(adj, i, visited);
        cout << endl;
        count++;
    }
    return count;
}


bool detectCycle(vector<int> adj[], int s, bool visited[], int parent=-1){
    visited[s]=true;
    for(int v:adj[s]){
        if(!visited[v]){
            if(detectCycle(adj, v, visited, s)) return true;
        }
        else if(v!=parent) return true;
    }
    return false;
}

// 18/12/2022 Detect cycle by dfs in an undirected graph
// O(V+E)xO(V)
bool detectCycle(vector<int> adj[], int n){
    bool visited[n];
    fill(visited, visited+n, false);
    for(int i=0;i<n;i++){
        if(visited[i]) continue;
        if(detectCycle(adj, i, visited, -1)) return true;
    }
    return false;
}


bool detectCycle_dir(vector<int> adj[], int s, bool visited[], bool recSk[]){
    visited[s]=true;
    recSk[s]=true;
    for(int v:adj[s]){
        if(recSk[v]) return true;
        if(visited[v]) continue;
        if(detectCycle_dir(adj, v, visited, recSk)) return true;
    }
    recSk[s]=false;
    return false;
}


// 19/12/2022 Detect cycle in a directed graph
// How diff from undirected? -> connected but not reachable. Ex: 0->1<-2.
// Reachable but not in same recursion stack. Ex: 0 -> 1 -> 2 & 0 -> 3 -> 2 case.
// Hence you need to count a cycle only when you detect encounter a visited node in the current recursion stack
// i.e detect back edge
// O(V+E)xO(V)
bool detectCycle_dir(vector<int> adj[], int n){
    bool visited[n]={}, recSk[n]={};
    fill(visited, visited+n, false);
    fill(recSk, recSk+n, false);
    for(int i=0;i<n;i++){
        if(visited[i]) continue;
        if(detectCycle_dir(adj, i, visited, recSk)) return true;
    }
    return false;
}


// 19/12/2022 Detect Cycle in a undirected graph using BFS.
// we'll maintain parent array instead of parent param in dfs.
// O(V+E)xO(v)
bool detectCycle_bfs(vector<int> adj[], int n){
    queue<int> q;
    bool visited[n];
    int parent[n];
    fill(visited, visited+n, false);
    for(int i=0;i<n;i++){
        if(visited[i]) continue;
        visited[i] = true;
        parent[i] = -1;
        q.push(i);
        while(!q.empty()){
            int u = q.front();
            q.pop();
            for(int v:adj[u]){
                if(!visited[v]) {
                    q.push(v);
                    visited[v] = true;
                    parent[v] = u;
                }
                else if(v!=parent[u]) return true;
            }
        }
    }
    return false;
}


// 19/12/2022 Kahn's Topological Sort Algorithm
// For Directed Acyclic Graph (DAG).
// Returns true if there's a cycle. Useful for cycle detection.
// O(V+E)xO(v)
bool topological_sort(vector<int> adj[], int n){
    int indegree[n] = {};
    int count=0;
    // O(V+E)xO(1)
    for(int i=0;i<n;i++){
        for(int v:adj[i]){
            indegree[v]++;
        }
    }

    queue<int> q;
    for(int i=0;i<n;i++){
        if(indegree[i]) continue;
        q.push(i);
    }

    while(!q.empty()){
        int u = q.front();
        q.pop();
        cout << u << " ";
        for(int v: adj[u]){
           if(--indegree[v]==0) q.push(v);
        }
        count++;
    }
    cout << endl;
    return count!=n;
}


void topologicalSort_dfs(vector<int> adj[], int s, bool visited[], stack<int> &sk){
    visited[s] = true;
    for(int v:adj[s]){
        if(visited[v]) continue;
        topologicalSort_dfs(adj, v, visited, sk);
    }

    sk.push(s);
}


// 19/12/2022 Topological Sort using DFS approach in a DAG
// current node is pushed to stack at the last => every number is printed before all it's dependencies.
// Instead you can't just print at the beginning because you wouldn't have printed all nodes at prev level in dfs.
// O(V+E)xO(V)
void topologicalSort_dfs(vector<int> adj[], int n){
    bool visited[n] = {};
    stack<int> sk;

    for(int i=0;i<n;i++){
        if(visited[i]) continue;
        topologicalSort_dfs(adj, i, visited, sk);
    }
    while(!sk.empty()){
        cout << sk.top() << " ";
        sk.pop();
    }
}


// 19/12/2022 Shortest Path from source node to all other nodes in a DAG using BFS
// Find topological sort. Then iterate [0,n) and update each of the adj[i] distances
// Modification to topological sort
// Alt: stack from topologicalSort_dfs then pop each and update it's adj vertices distance in O(V+E)
// O(V+E)xO(v)
void shortestPath_dag(vector<pair<int, int>> adj[], int n, int s){

    int minDistance[n];
    fill(minDistance, minDistance+n, INT_MAX);
    minDistance[s]=0;

    int indegree[n] = {};
    for(int i=0;i<n;i++) for(auto &v:adj[i]) indegree[v.first]++;

    queue<int> q;
    for(int i=0;i<n;i++){
        if(!indegree[i]) q.push(i);
    }

    while(!q.empty()){
        int u = q.front();
        q.pop();

        for(auto &v:adj[u]){
            // You are never going to visit the vertices you've already enqued anyway.
            if(--indegree[v.first]==0){
                q.push(v.first);
            }
            if(minDistance[u]!=INT_MAX)
                minDistance[v.first] = min(minDistance[v.first], minDistance[u]+v.second);
        }
    }
    
    for(int d:minDistance) cout << d << " ";
    cout << endl;
}


// 20/12/2022 Prim's MST Algorithm for an **undirected**, **connected**, **weighted** graph.
// There is always a unique MST
// O(V+ElogV) = O(ElogV)
int primsMST(vector<pair<int, int>> adj[], int n){
    bool inMST[n] = {};
    int parent[n], key[n]; // There is no parent/child relationship since undirected but useful to print edges in MST.
    fill(parent, parent+n, -1);
    fill(key, key+n, INT_MAX);
    key[0]=0;
    int mstWeight=0;
    auto cmp = [&key](int x, int y){return key[x]==key[y]?x<y:key[x]<key[y];};
    set<int, decltype(cmp)> set(cmp);
    set.insert(0);

    // O(V) amortized.
    for(int i=1;i<n;i++){
        // O(1) amortized since only need periodical fix-up rb tree which is O(logn) no need to search.
        set.emplace_hint(set.end(), i);
    }

    // Alt using set: Only insert 0 in the beginning. And only when you are updating INT_MAX for a 
    // node then insert it into the set for the first time directly with a new val =key[v] i.e {key[v], v}
    // Alt using pq: insert into pq w/o removing previous value. keep a flag of removed values and lazy delete
    // those when you pop if the same vertex has already been extracted.

    // O(ElogV) + (VxO(1) amortized) altogether => O(ElogV)
    while(!set.empty()){
        int u = *set.begin();
        mstWeight+=key[u];       
        set.erase(set.begin()); // O(1) amortized just rb-tree fix up periodically. (worst is O(logv)).
        inMST[u]=1;
        // O(ElogV) altogether
        for(auto &v:adj[u]){ // Runs altogether for O(E) times.
            if(!inMST[v.first] && key[v.first]>v.second){ // O(1) to check if v exist in mst.
                
                // Alt: Do this only if key[v.first]!=INT_MAX if you haven't inserted all at the beginning
                set.erase(v.first); // O(logV)
                
                key[v.first] = v.second;
                set.emplace(v.first); // O(logV)
                parent[v.first] = u;
            }
        }
    }
    for(int p:parent)   cout << p << " ";
    cout << endl;
    return mstWeight;
}

// TODO: Learn Disjoint Set DS & Union-Find Algorithms
// Takes Edge[]
int kruskalsMST(){
    return 0;
}

// 20/12/2022 Djikstra's shortest path algorithm
// Gives shortest path tree i.e min distance from source to every other node. 
// Alt: you can use the set as above
// O(ElogV) 
void shortestPath_DJ(vector<pair<int, int>> adj[], int n, int s){

    bool fin[n] = {}; // whether distance of a vertext from s is finalized or not.
    int dist[n];
    fill(dist, dist+n, INT_MAX);
    dist[s]=0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int,int>>> pq; //min_heap
    pq.push({dist[s], s});


    while(!pq.empty()){
        int u = pq.top().second;
        pq.pop(); // O(VlogV)

        // repitition of vertex whose distance from source is already finalized
        if(fin[u]) continue;
        fin[u] = true;

        for(auto &v:adj[u]){ // O(ElogV)
            if(!fin[v.first] && dist[v.first]>dist[u]+v.second){
                dist[v.first] = dist[u]+v.second;
                pq.push({dist[v.first], v.first}); // repitions could be pushed.
            }
        }
    }

    for(int d:dist) cout << d << " ";
    cout << endl;
}


struct Edge{
    int u, v, w;
};

// 22/12/2022 Bellman Ford Shotest Path algorithm for -ve weighted graphs
// Also usedful for -ve edge cycle detection.
// DP algorithm bottom up. After 1 iteration we have shortestPath of edge length==1 after 2 iterations
// we have shortest paths of edge length 2 and max there can be a shortest simple path of edge length v-1.
// O(VE)
void shortestPath_BF(int n, int s, vector<Edge> edges){
    int dist[n];
    fill(dist, dist+n, INT_MAX);
    dist[s]=0;
    while(n-->1){
        for(Edge &e:edges){
            if(dist[e.u]!=INT_MAX && dist[e.v]>dist[e.u]+e.w){
                dist[e.v] = dist[e.u]+e.w;
            }
        }
    }

    for(Edge &e:edges){
        if(dist[e.v]>dist[e.u]+e.w){
            cout << "-ve Edge cycle detected"<<endl;
            return;
        }
    }

    for(int d:dist) cout << d << " ";
    cout << endl;
}

void dfs_kosaraju(vector<int> adj[], int s, bool visited[], stack<int> &finishSk){
    visited[s]=true;
    for(int v:adj[s]){
        if(!visited[v]) dfs_kosaraju(adj, v, visited, finishSk); 
    }
    finishSk.push(s);
}

// 21/12/2022 Strongly Connected Components in a directed graph
// Every edge reachable from dfs(s) say v, now s many not be reachable from v in dfs(v). Thus dfs(v) must
// first happen before dfs(s). Like visiting sinks in the condensed DAG first before moving to sources so that
// visited doesn't get spoiled.
// O(V+E)xO(V+E) but 2 dfs traversals + 1 transpose. Alt: Tarjan's algorithm just 1 dfs traversal
void scc_kosaraju(vector<int> adj[], int n){
    stack<int> finishSk; // Similar to sk in topological sort i.e you push the current node after all it's adj are finished
    bool visited[n] = {};

    // STEP1: Gives source to sink direction from stack top to bottom i.e from last finished to first finished.
    // O(V+E)
    for(int i=0;i<n;i++){
        if(visited[i]) continue;
        dfs_kosaraju(adj, i, visited, finishSk);
    }

    // STEP2: Reverse graph i.e transpose adj matrix
    // Converts all sources to sinks and sinks to sources
    // All strongly connected components are still strongly connected after reversing but not others.
    // O(V+E)xO(V+E)
    vector<int> adjT[n];
    for(int i=0;i<n;i++){
        for(int v:adj[i])
            adjT[v].push_back(i);
    }

    fill(visited, visited+n, false);

    // STEP 3: Do dfs in the order of finish times nodes and print all reachable as connected component
    // O(V+E)
    while(!finishSk.empty()){
        int u = finishSk.top();
        finishSk.pop();
        if(visited[u]) continue;
        // Normal dfs
        dfs(adjT, u, visited);
        cout << endl;
    }
}


void dfs_tarjan(vector<int> adj[], int s, int &timer, int discTime[], int lowDiscReach[], bool inRecSk[], stack<int> &recSk){
    discTime[s] = lowDiscReach[s] = ++timer;
    inRecSk[s] = true;
    recSk.push(s);

    for(int v:adj[s]){
        if(!discTime[v]){
            dfs_tarjan(adj, v, timer, discTime, lowDiscReach, inRecSk, recSk);
            lowDiscReach[s] = min(lowDiscReach[s], lowDiscReach[v]);
        }
        else if(inRecSk[v]){
            lowDiscReach[s] = min(lowDiscReach[s], discTime[v]);
        }
    }

    // You are not popping recSk everytime
    // You are not setting inRecSk false on coming out.
    // Though you have technically come out of recursion these nodes in other branch will be in recSk hence they are not
    // technically considered cross edges. You only won't consider those edges which are visited but not in the recSk that you maintain i.e cross edges
    if(lowDiscReach[s]==discTime[s]){
        while(recSk.top()!=s){
            cout << recSk.top() << " ";
            inRecSk[recSk.top()]=false;
            recSk.pop();
        }
        cout << recSk.top() << endl;
        inRecSk[recSk.top()]=false;
        recSk.pop();
    }

    
}

// 23/12/2022 Strongly Connected Components in a dir graph - Tarjan's algo
// O(V+E)xO(V). Better than kosaraju as only 1 dfs traversal.
void scc_tarjan(vector<int> adj[], int n){
    int discTime[n] = {};
    int lowDiscReach[n];
    bool inRecSk[n] = {};
    stack<int> recSk;
    int timer=0;

    for(int i=0;i<n;i++){
        if(discTime[i]) continue;
        dfs_tarjan(adj, i, timer, discTime, lowDiscReach, inRecSk, recSk);
    }
}


void dfs_cutVertices(vector<int> adj[], int s, int parent, int &timer, int discTime[], int lowDiscReach[], bool cv[]){
    discTime[s] = ++timer;
    lowDiscReach[s] = timer; // lowest distance reachable from cur node is itself.
    int children=0;
    for(int v:adj[s]){
        if(!discTime[v]){
            if(parent==-1 && ++children==2){ // Root node is cut vertex iff it has at least two children in DFS Tree
                cv[s]=true;
            }
            dfs_cutVertices(adj, v, s, timer, discTime, lowDiscReach, cv);
            
            // Updates when cur node has a back edge (i.e not to parent but ancestors)
            lowDiscReach[s] = min(lowDiscReach[s], lowDiscReach[v]);

            // Non-root node is cut vertex if at least one child has lowest distance reachable >= cur node discover time.
            if(parent!=-1 && lowDiscReach[v]>=discTime[s]) cv[s] = true;
        }
        else if(parent!=v){
            // NOTE: You cannot use min(lowDiscReach[s], lowDiscReach[v]) becaue then it means 
            // you have back edge not from s->v but from s to lowDiscReach[v] => if v is removed we could have cut vertex but that's gone now.
            // So basically lowDiscReach is cur_node disc tiem or ancestor discovery time reachable (include children) from the current node which ever is lower.
            // is discTime[v] always less than lowDiscReach[s]? Need not be, instead of back edge 
            // it could be one of the dscendents which you hav already visited through another child.
            lowDiscReach[s] = min(lowDiscReach[s], discTime[v]);
        }        
    }
}


// 22/12/2022 Find Cut Vertices/Articulation Points in an undirected graph.
// New concepts of Discovery Time and Lowest discovery time vertex reachable from the current vertex in the DFSTree
// DFS Tree Tree edges & back edges. Ignore child to parent edges (since it's still undirected) but
// sought of treating undirected edges as Tree edges. child to ancestor edges are called back edges.
// O(V+E)
void cutVertices(vector<int> adj[], int n){
    int discTime[n] = {};
    int lowDiscReach[n];
    bool cv[n] = {};
    int timer=0;

    for(int i=0;i<n;i++){
        if(discTime[i])continue;
        dfs_cutVertices(adj, i, -1, timer, discTime, lowDiscReach, cv);
    }

    for(int i=0;i<n;i++)
        if(cv[i]) cout << i << " ";
    cout << endl;
}


void dfs_bridges(vector<int> adj[], int s, int parent, int &timer, int discTime[], int lowDiscReach[]){
    discTime[s] = ++timer;
    lowDiscReach[s] = timer;

    for(int v:adj[s]){
        if(!discTime[v]){
            dfs_bridges(adj, v, s, timer, discTime, lowDiscReach);
            lowDiscReach[s] = min(lowDiscReach[v], lowDiscReach[s]);
            if(lowDiscReach[v] > discTime[s]) cout << s <<"-"<<v<<endl;
        }
        if(parent!=v){
            lowDiscReach[s] = min(lowDiscReach[s], discTime[v]);
        }
    }
}

// 23/12/2022 Find bridge edges in an undirected graph
// O(V+E)xO(V)
void bridges(vector<int> adj[], int n){
    int discTime[n]={};
    int lowDiscReach[n];
    int timer=0;
    for(int i=0;i<n;i++){
        if(discTime[i]) continue;
        dfs_bridges(adj, i, -1, timer, discTime, lowDiscReach);
    }
}

int main(int argc, char const *argv[])
{
    int n, e;
    cin >> n >> e;
    vector<int> adjList[n];
    bool visited[n];
    fill(visited, visited+n, false);

    for(int i=0;i<e;i++){
        int u, v;
        cin >> u >> v;
        adjList[u].push_back(v);

        // undirected.
        // adjList[v].push_back(u);
    }

    // vector<pair<int, int>> adjList[n];
    // bool visited[n];
    // fill(visited, visited+n, false);

    // for(int i=0;i<e;i++){
    //     int u, v, w;
    //     cin >> u >> v >> w;
    //     adjList[u].push_back({v, w});
    //     adjList[v].push_back({u, w});
    // }

    // cout << bfs_dis(adjList, n) << endl;;
    // dfs(adjList, 0, visited);
    // cout << dfs_dis(adjList, n) << endl;
    // cout << detectCycle(adjList, n);
    // cout << detectCycle_bfs(adjList, n);
    // cout << detectCycle_dir(adjList, n) << endl;
    // cout << topological_sort(adjList, n) << endl;
    // topologicalSort_dfs(adjList, n);

    // shortestPath(adjList, n, 0);

    // cout << primsMST(adjList, n) << endl;
    // shortestPath_dj(adjList, n, 0);
    scc_kosaraju(adjList, n);
    cout << endl;
    scc_tarjan(adjList, n);

    /* int n;
    cin >> n;

    vector<Edge> edges = {{0, 1, 1}, {0, 2, 4}, {1, 3, 2}, {1, 2, -3}, {2, 3, 3}};
    shortestPath_BF(n, 0, edges); */

    // cutVertices(adjList, n);
    // bridges(adjList, n);
    return 0;
}