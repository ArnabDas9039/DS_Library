// #include<bits/stdc++.h>
#include<iostream>
#include<map>
#include<list>
#include<queue>
#include<stack>
using namespace std;


class Graph{
public:
    class Node{
    public:
        int data;
    };

    class Edge{
    public:
        Node* src;
        Node* dest;
        int weight;

        Edge(Node* s, Node* d, int weight){
            this->src = s;
            this->dest = d;
            this->weight = weight;
        }
    };

    struct CompareW{
        bool operator()(Edge* a, Edge* b){
            return a->weight > b->weight;
        }
    };

    map<Node*, list<Edge*> > adj;

    int graphsize(){
        return adj.size();
    }

    void createVertex(Node n){
        Node* vertex = new Node(n);
        adj.insert({ vertex, list<Edge*>() });
    }

    Node* getVertex(Node n){
        for(auto i : adj){
            if(i.first->data == n.data){
                return i.first;
            }
        }
    }

    void addedges(int src, int dest, int weight){
        Node* s, * d;
        for(auto i : adj){
            if(i.first->data == src){
                s = i.first;
            }
            if(i.first->data == dest){
                d = i.first;
            }
        }
        Edge* e1 = new Edge(s, d, weight);
        Edge* e2 = new Edge(d, s, weight);
        adj[s].push_back(e1);
        adj[d].push_back(e2);
    }

    void adddirection(int src, int dest, int weight){
        Node* s, * d;
        for(auto i : adj){
            if(i.first->data == src){
                s = i.first;
            }
            if(i.first->data == dest){
                d = i.first;
            }
        }
        Edge* e = new Edge(s, d, weight);
        adj[s].push_back(e);
    }

    void display(){
        for(auto i : adj){
            cout << i.first->data << " -> ";
            for(auto x : i.second){
                cout << x->dest->data << "(" << x->weight << ") => ";
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
                    StackFrontier.push(i->dest);
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
                    QueueFrontier.push(i->dest);
                }
            }
        }
        // cout << "States explored: " << size << endl;
    }

    void shortest_path_queue(Node* start){
        priority_queue<Edge*, vector<Edge*>, CompareW> QueueFrontier;
        map<Node*, bool> visit;
        map<Node*, unsigned int> distance;
        for(auto i : adj){
            distance[i.first] = UINT32_MAX;
        }

        distance[start] = 0;
        Edge* e0 = new Edge(start, start, 0);

        QueueFrontier.push(e0);
        while(!QueueFrontier.empty()){
            Edge* value = QueueFrontier.top();
            QueueFrontier.pop();
            if(!visit[value->dest]){
                visit[value->dest] = true;
                for(auto i : adj[value->dest]){
                    if(distance[value->dest] + i->weight < distance[i->dest]){
                        distance[i->dest] = distance[value->dest] + i->weight;
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
                    if(distance[i.first] + value->weight < distance[value->dest] && distance[i.first] != INT32_MAX){
                        distance[value->dest] = distance[i.first] + value->weight;
                    }
                }
            }
        }

        for(auto i : adj){
            cout << "(" << distance[i.first] << ") ";
        }
    }

    void Prim_Tree(Node* start){
        priority_queue<Edge*, vector<Edge*>, CompareW> QueueFrontier;
        map<Node*, bool> visit;
        list<Node*> MST;

        Edge* e0 = new Edge(start, start, 0);
        QueueFrontier.push(e0);
        while(!QueueFrontier.empty()){
            Edge* value = QueueFrontier.top();
            QueueFrontier.pop();
            if(!visit[value->dest]){
                MST.push_back(value->dest);
                // cout << "(" << value->src->data << ", " << value->dest->data << ", " << value->weight << ") ";
                visit[value->dest] = true;
                for(auto i : adj[value->dest]){
                    QueueFrontier.push(i);
                }
            }
        }

        for(auto i : MST){

        }
    }

    void Kruskal_Tree(Node* start){

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

    // Edges
    g1.addedges(0, 1, 2);
    g1.addedges(0, 2, 4);
    g1.addedges(1, 3, 7);
    g1.addedges(2, 4, 1);
    g1.addedges(3, 4, 2);
    g1.addedges(3, 5, 1);
    g1.addedges(4, 5, 5);
    g1.addedges(5, 6, 1);

    // Calls to check
    cout << g1.graphsize() << endl;
    g1.display();
    cout << endl;
    g1.dfs(g1.getVertex({ 0 }));
    cout << endl;
    g1.bfs(g1.getVertex({ 0 }));
    cout << endl;
    g1.shortest_path_queue(g1.getVertex({ 0 }));
    cout << endl;
    g1.shortest_path_negative(g1.getVertex({ 0 }));
    cout << endl;
    g1.Prim_Tree(g1.getVertex({ 0 }));

    return 0;
}