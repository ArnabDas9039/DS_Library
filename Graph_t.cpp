#include<bits/stdc++.h>
// This program contains an abstraction layer. Do check Graphpointer.cpp for a better program without any abstraction
using namespace std;
class Graph{
public:
    map<int, list<int> > adj;
    int v, top = -1;
    map<int, bool> visit;
    stack<int> s;
    queue<int> q;

    // constructor
    Graph(int v){
        this->v = v;
    }

    void addedge(int src, int dest){
        adj[src].push_back(dest);
    }

    void dfs_rec(int index);
    void dfs(int index);
    void bfs(int index);
    void display(){
        for(int index = 0; index < v; index++){
            cout << index << " => ";
            for(int i : adj[index]){
                cout << i << " => ";
            }
            cout << endl;
        }
    }
};
void Graph::dfs_rec(int index){
    if(visit[index] == true){
        return;
    }
    cout << index << " ";
    visit[index] = true;
    for(int i : adj[index]){
        dfs_rec(i);
    }
}
void Graph::dfs(int index){
    s.push(index);
    while(!s.empty()){
        int value = s.top();
        s.pop();
        if(visit[value] == false){
            cout << value << " ";
            visit[value] = true;
            for(int i : adj[value]){
                s.push(i);
            }
        }
    }
}
void Graph::bfs(int index){
    q.push(index);
    while(!q.empty()){
        int value = q.front();
        q.pop();
        if(visit[value] == false){
            cout << value << " ";
            visit[value] = true;
            for(int i : adj[value]){
                q.push(i);
            }
        }
    }
}
int main(){
    Graph g(7);
    //0
    g.addedge(0, 1);
    g.addedge(0, 2);
    //1
    g.addedge(1, 0);
    g.addedge(1, 3);
    //2
    g.addedge(2, 0);
    g.addedge(2, 4);
    //3
    g.addedge(3, 1);
    g.addedge(3, 4);
    g.addedge(3, 5);
    //4
    g.addedge(4, 2);
    g.addedge(4, 3);
    g.addedge(4, 5);
    //5
    g.addedge(5, 3);
    g.addedge(5, 4);
    g.addedge(5, 6);
    //6
    g.addedge(6, 5);
    g.display();
    // g.dfs_rec(0);
    g.dfs(0);
    // g.bfs(0);
}