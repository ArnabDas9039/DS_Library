// #include<bits/stdc++.h>
#include<iostream>
#include<algorithm>
#include<map>
#include<list>
#include<queue>
#include<stack>
#include<set>
using namespace std;

class Graph{
public:
    class Node{
    public:
        int data;
    };

    map<Node*, list<Node*> > adj;

    int graphsize(){
        return adj.size();
    }

    void createVertex(Node n){
        Node* vertex = new Node(n);
        adj.insert({ vertex, list<Node*>() });
    }

    Node* getVertex(Node n){
        for(auto i : adj){
            if(i.first->data == n.data){
                return i.first;
            }
        }
    }


    void addedges(int src, int dest){
        Node* s, * d;
        for(auto i : adj){
            if(i.first->data == src){
                s = i.first;
            }
            if(i.first->data == dest){
                d = i.first;
            }
        }
        adj[s].push_back(d);
        adj[d].push_back(s);
    }

    void adddirection(int src, int dest){
        Node* s, * d;
        for(auto i : adj){
            if(i.first->data == src){
                s = i.first;
            }
            if(i.first->data == dest){
                d = i.first;
            }
        }
        adj[s].push_back(d);
        // adj[d].push_back(s);
    }

    void display(){
        for(auto i : adj){
            cout << i.first->data << " -> ";
            for(auto x : i.second){
                cout << x->data << " => ";
            }
            cout << endl;
        }
    }

    void dfs(Node* start){
        stack<Node*> StackFrontier;
        map<Node*, bool> visit;
        // int state = 0;

        StackFrontier.push(start);
        while(!StackFrontier.empty()){
            Node* value = StackFrontier.top();
            StackFrontier.pop();
            if(!visit[value]){
                cout << "(" << value->data << ") ->";
                // state++;
                visit[value] = true;
                for(auto i : adj[value]){
                    StackFrontier.push(i);
                }
            }
        }
        // cout << "States explored: " << state << endl;
    }

    void bfs(Node* start){
        queue<Node*> QueueFrontier;
        map<Node*, bool> visit;
        // int size = 0;

        QueueFrontier.push(start);
        while(!QueueFrontier.empty()){
            Node* value = QueueFrontier.front();
            QueueFrontier.pop();
            if(!visit[value]){
                cout << "(" << value->data << ") ->";
                // size++;
                visit[value] = true;
                for(auto i : adj[value]){
                    QueueFrontier.push(i);
                }
            }
        }
        // cout << "States explored: " << size << endl;
    }

    void cycle_detection(Node* start){
        map<Node*, bool> visit;
        stack<pair<Node*, Node*>> StackFrontier;

        StackFrontier.push({ start, nullptr });
        cout << "Stack initiated with: " << start->data << endl;
        while(!StackFrontier.empty()){
            pair<Node*, Node*> current = StackFrontier.top();
            StackFrontier.pop();
            cout << "Current is: " << current.first->data << endl;
            if(!visit[current.first]){
                cout << "Visited is false" << endl;
                visit[current.first] = true;
                for(auto i : adj[current.first]){
                    cout << "Neighbour is: " << i->data << endl;
                    if(visit[i] && current.second != i){
                        cout << "cycle detected for node: " << current.first->data << " with neighbour: " << i->data << endl;
                        break;
                    }
                    StackFrontier.push({ i, current.first });
                }
            }
        }
    }

    void cycle_detection2(Node* start){
        map<Node*, bool> visit;

        for(auto i : adj){
            Node* start = i.first;
            if(!visit[start]){
                stack<pair<Node*, vector<Node*> > > StackFrontier;
                StackFrontier.push({ start, {nullptr} });
                cout << "Stack initiated with: " << start->data << endl;
                while(!StackFrontier.empty()){
                    pair<Node*, vector<Node*> > current = StackFrontier.top();
                    StackFrontier.pop();
                    cout << "Current is: " << current.first->data << endl;
                    for(auto neighbour : adj[current.first]){
                        cout << "Neighbour is: " << neighbour->data << endl;
                        if(find(current.second.begin(), current.second.end(), neighbour) != current.second.end()){
                            cout << "cycle detected for node: " << current.first->data << " with neighbour: " << neighbour->data << endl;
                            break;
                        }
                        vector<Node*> newPath = current.second;
                        newPath.push_back(neighbour);
                        StackFrontier.push({ neighbour, newPath });
                    }
                }
            }
        }
    }

    void topology(){
        map<Node*, bool> visit;
        map<Node*, bool> current;
        vector<Node*> result;

        for(auto i : adj){
            if(!visit[i.first]){
                stack<Node*> StackFrontier;

                StackFrontier.push(i.first);
                while(!StackFrontier.empty()){
                    Node* value = StackFrontier.top();
                    if(!current[value]){
                        visit[value] = true;
                        current[value] = true;
                        for(auto neighbour : adj[value]){
                            if(current[neighbour]){
                                cout << "Graph has a cycle";
                                return;
                            }
                            if(!visit[neighbour]){
                                StackFrontier.push(neighbour);
                            }
                        }
                    }
                    else{
                        StackFrontier.pop();
                        current[value] = false;
                        result.push_back(value);
                    }

                }
            }
        }

        reverse(result.begin(), result.end());

        for(auto i : result){
            cout << i->data << " -> ";
        }
        cout << endl;
    }

    void topology2(){
        map<Node*, int> inDegree;
        vector<Node*> result;
        queue<Node*> QueueFrontier;

        for(auto i : adj){
            inDegree[i.first] = 0;
        }
        for(auto i : adj){
            for(auto j : i.second){
                inDegree[j] += 1;
            }
        }

        for(auto i : inDegree){
            if(i.second == 0){
                QueueFrontier.push(i.first);
            }
        }

        while(!QueueFrontier.empty()){
            Node* value = QueueFrontier.front();
            QueueFrontier.pop();
            result.push_back(value);

            for(auto i : adj[value]){
                inDegree[i] -= 1;
                if(inDegree[i] == 0){
                    QueueFrontier.push(i);
                }
            }
        }

        if(result.size() != inDegree.size()){
            cout << "Graph has a cycle" << endl;
        }
        else{
            for(auto i : result){
                cout << i->data << " -> ";
            }
            cout << endl;
        }
    }

    void findBridgesAndAPsIterative(){
        map<Node*, int> disc;
        map<Node*, int> low;
        map<Node*, Node*> parent;
        map<Node*, int> children_count;

        set<Node*> articulation_points;
        vector<pair<Node*, Node*>> bridges;

        int time = 0;

        for(auto i : adj){
            Node* start_node = i.first;
            if(disc.find(start_node) == disc.end()){

                Node* root = start_node;
                stack<pair<Node*, list<Node*>::iterator>> s;

                s.push({ start_node, adj[start_node].begin() });
                parent[start_node] = nullptr;
                disc[start_node] = low[start_node] = ++time;
                children_count[root] = 0;

                while(!s.empty()){
                    Node* u = s.top().first;
                    list<Node*>::iterator& it = s.top().second;

                    // If we have processed all neighbors of u
                    if(it == adj[u].end()){
                        s.pop();

                        // --- Post-order processing (after children are done) ---
                        Node* p = parent[u];
                        if(p != nullptr){
                            low[p] = min(low[p], low[u]);

                            // Articulation Point Check
                            if(low[u] >= disc[p]){
                                // Exclude the root, it's handled separately
                                if(p != root || children_count[root] > 1){
                                    articulation_points.insert(p);
                                }
                            }
                            // Bridge Check
                            if(low[u] > disc[p]){
                                bridges.push_back({ p, u });
                            }
                        }
                        continue;
                    }

                    Node* v = *it;
                    it++; // Advance iterator for the next time we see u

                    if(v == parent[u]){
                        continue;
                    }

                    if(disc.find(v) != disc.end()){ // Back edge
                        low[u] = min(low[u], disc[v]);
                    }
                    else{ // Tree edge (new node)
                        parent[v] = u;
                        disc[v] = low[v] = ++time;
                        if(u == root) children_count[root]++;

                        s.push({ v, adj[v].begin() });
                    }
                }
            }
        }

        // --- Print Results ---
        cout << "Articulation Points are: ";
        for(Node* node : articulation_points){
            cout << node->data << " ";
        }
        cout << endl;

        cout << "Bridges are: ";
        for(auto const& edge : bridges){
            cout << "(" << edge.first->data << ", " << edge.second->data << ") ";
        }
        cout << endl;
    }

    void shortest_path_queue(Node* start){
        queue<Node*> QueueFrontier;
        map<Node*, bool> visit;
        map<Node*, unsigned int> distance;
        for(auto i : adj){
            distance[i.first] = UINT32_MAX;
        }
        distance[start] = 0;
        QueueFrontier.push(start);
        while(!QueueFrontier.empty()){
            Node* value = QueueFrontier.front();
            QueueFrontier.pop();
            if(!visit[value]){
                visit[value] = true;
                for(auto i : adj[value]){
                    if(distance[value] + 1 < distance[i]){
                        distance[i] = distance[value] + 1;
                        QueueFrontier.push(i);
                    }
                }
            }
        }

        for(auto i : adj){
            cout << "(" << distance[i.first] << ") ";
        }
    }

    void shortest_path_negative(Node* start){
        map<Node*, int> distance;
        for(auto i : adj){
            distance[i.first] = INT32_MAX;
        }
        distance[start] = 0;
        for(int k = 0; k < graphsize() - 1; k++){
            for(auto i : adj){
                for(auto value : i.second){
                    if(distance[i.first] + 1 < distance[value] && distance[i.first] != INT32_MAX){
                        distance[value] = distance[i.first] + 1;
                    }
                }
            }
        }

        for(auto i : adj){
            cout << "(" << distance[i.first] << ") ";
        }
    }

    void Spanning_Tree(Node* start){
        queue<Node*> QueueFrontier;
        map<Node*, bool> visit;
        list<Node*> MST;

        QueueFrontier.push(start);
        while(!QueueFrontier.empty()){
            Node* value = QueueFrontier.front();
            QueueFrontier.pop();
            if(!visit[value]){
                MST.push_back(value);
                visit[value] = true;
                for(auto i : adj[value]){
                    QueueFrontier.push(i);
                }
            }
        }

        for(auto i : MST){
            cout << "(" << i->data << ") ";
        }
    }

    void Kruskal_Tree(Node* start){

    }

    void printAllPaths(Node* src, Node* dest){
        stack<pair<Node*, vector<Node*>>> StackFrontier;

        StackFrontier.push({ src, {src} });

        while(!StackFrontier.empty()){
            pair<Node*, vector<Node*>> currentState = StackFrontier.top();
            StackFrontier.pop();

            if(currentState.first == dest){
                for(auto v : currentState.second){
                    cout << v->data << " ";
                }
                cout << endl;
                continue;
            }

            for(auto i : adj[currentState.first]){
                if(find(currentState.second.begin(), currentState.second.end(), i) == currentState.second.end()){
                    vector<Node*> newPath = currentState.second;

                    newPath.push_back(i);
                    StackFrontier.push({ i, newPath });
                }
            }
        }
    }

    // 1a. First DFS utility: Fills a stack with nodes in order of finishing times.
    void fillOrder(Node* u, map<Node*, bool>& visited, stack<Node*>& s){
        visited[u] = true;
        for(Node* v : adj[u]){
            if(!visited[v]){
                fillOrder(v, visited, s);
            }
        }
        s.push(u); // Push node to stack after all its descendants are processed
    }

    // 2. Transpose utility: Creates a new adjacency map with all edges reversed.
    map<Node*, list<Node*>> getTranspose(){
        map<Node*, list<Node*>> transposedAdj;
        for(auto i : adj){
            Node* u = i.first;
            transposedAdj[u] = {}; // Ensure all nodes exist in the new map
        }
        for(auto const& pair : adj){
            Node* u = pair.first;
            for(Node* v : pair.second){
                transposedAdj[v].push_back(u); // Reverse the edge v -> u
            }
        }
        return transposedAdj;
    }

    // 3a. Second DFS utility: Traverses a single component on the transposed graph.
    void dfsUtil(Node* u, map<Node*, bool>& visited, map<Node*, list<Node*>>& transposedAdj){
        visited[u] = true;
        for(Node* v : transposedAdj[u]){
            if(!visited[v]){
                dfsUtil(v, visited, transposedAdj);
            }
        }
    }

    // The main function that finds and counts SCCs.
    void countStronglyConnectedComponents(){
        stack<Node*> orderStack;
        map<Node*, bool> visited;

        // --- Step 1: Fill stack with nodes in order of their finishing times ---
        for(auto i : adj){
            Node* node = i.first;
            visited[node] = false;
        }
        for(auto i : adj){
            Node* node = i.first;
            if(!visited[node]){
                fillOrder(node, visited, orderStack);
            }
        }

        // --- Step 2: Create the transposed graph ---
        map<Node*, list<Node*>> transposedAdj = getTranspose();

        // --- Step 3: Process nodes from stack to find SCCs ---
        for(auto i : adj){
            Node* node = i.first;
            visited[node] = false; // Reset visited map for the second pass
        }

        int scc_count = 0;
        while(!orderStack.empty()){
            Node* u = orderStack.top();
            orderStack.pop();

            if(!visited[u]){
                // This unvisited node is the start of a new SCC.
                // Run DFS to find all nodes in this component.
                dfsUtil(u, visited, transposedAdj);
                scc_count++;
            }
        }

        cout << "Number of strongly connected components: " << scc_count << endl;
    }
};


int main(){
    Graph g1;
    // Vertex
    g1.createVertex({ 0 });
    g1.createVertex({ 1 });
    g1.createVertex({ 2 });
    g1.createVertex({ 3 });
    g1.createVertex({ 4 });
    g1.createVertex({ 5 });
    g1.createVertex({ 6 });
    g1.createVertex({ 7 });

    // Edges
    g1.addedges(0, 1);
    g1.addedges(1, 2);
    g1.addedges(1, 3);
    g1.addedges(2, 3);
    g1.addedges(3, 4);
    g1.addedges(3, 5);
    g1.addedges(5, 6);
    g1.addedges(5, 7);
    g1.addedges(6, 7);

    // g1.adddirection(0, 2);
    // g1.adddirection(0, 3);
    // g1.adddirection(1, 0);
    // g1.adddirection(2, 1);
    // g1.adddirection(2, 3);
    // g1.adddirection(3, 4);
    // g1.adddirection(4, 2);
    // g1.adddirection(3, 1);
    // g1.adddirection(4, 0);
    // g1.adddirection(4, 1);
    // g1.adddirection(5, 0);
    // g1.adddirection(5, 2);

    // Calls to check
    cout << g1.graphsize() << endl;
    g1.display();
    cout << endl;
    // g1.dfs(g1.getVertex({ 0 }));
    cout << endl;
    // g1.bfs(g1.getVertex({0}));
    // g1.cycle_detection(g1.getVertex({ 0 }));
    // cout << "Cycle Detection 2" << endl;
    // g1.cycle_detection2(g1.getVertex({ 0 }));
    // g1.printAllPaths(g1.getVertex({ 0 }), g1.getVertex({ 5 }));
    // g1.topology();
    // g1.topology2();
    // cout << endl;
    // g1.shortest_path_queue(g1.getVertex({ 0 }));
    // cout<<endl;
    // g1.shortest_path_negative(g1.getVertex({0}));
    // cout<<endl;
    // g1.Prim_Tree(g1.getVertex({0}));
    g1.findBridgesAndAPsIterative();
    g1.countStronglyConnectedComponents();
    return 0;
}