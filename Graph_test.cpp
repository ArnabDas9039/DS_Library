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
        adj[d].push_back(s);
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
    g1.addedges(0, 1);
    g1.addedges(0, 2);
    g1.addedges(1, 3);
    g1.addedges(2, 4);
    g1.addedges(3, 4);
    g1.addedges(3, 5);
    g1.addedges(4, 5);
    g1.addedges(5, 6);

    // Calls to check
    cout << g1.graphsize() << endl;
    g1.display();
    cout << endl;
    g1.dfs(g1.getVertex({ 0 }));
    // cout<<endl;
    // g1.bfs(g1.getVertex({0}));
    cout << endl;
    g1.shortest_path_queue(g1.getVertex({ 0 }));
    // cout<<endl;
    // g1.shortest_path_negative(g1.getVertex({0}));
    // cout<<endl;
    // g1.Prim_Tree(g1.getVertex({0}));
    return 0;
}