#include<bits/stdc++.h>
// This program needs an exclusive review by the author
using namespace std;
class node{
public:
    // attributes
    int number;
    
    // constructor
    node(int n){
        this->number = n;
    }

    // Node *create_node(int n){
    //     Node *ptr = new Node(n);
    //     return ptr;
    // }
};
class Graph{
public:
    map<node*, list<node*> > adj;
    int v, top = -1;
    map<int, bool> visit;
    Graph(int v){
        this->v = v;
    }
    node* addvertex(int n){
        node* ptr = new node(n);
        return ptr;
    }
    void addedge(node* src, node* dest){
        adj[src].push_back(dest);
    }
    void dfs(node* index);
    void bfs(int index);
    void display(){
        for(auto index = adj.begin(); index != adj.end(); index++){
            node* src = index->first;
            cout<<src->number<<"[] => ";
            for(node* i : adj[src]){
                cout<<i->number<<" => ";
            }
            cout<<endl;
        }
        // for(int index=0; index<v; index++){
        //     cout<<index<<" => ";
        //     for(node i : adj[index]){
        //         cout<<i->number<<" => ";
        //     }
        //     cout<<endl;
        // }
    }
};
void Graph ::dfs(node* index){
    if(visit[index->number] == true){
        return;
    }
    cout << index->number << " ";
    visit[index->number] = true;
    // list<int> ::iterator i;
    // for(i = adj[index].begin(); i != adj[index].end(); i++){
    //     dfs(*i);
    // }
    for(node* i : adj[index]){
        dfs(i);
    }
}
int main(){
    Graph g(7);
    //0
    node* ptr0 = g.addvertex(0);
    node* ptr1 = g.addvertex(1);
    node* ptr2 = g.addvertex(2);
    g.addedge(ptr0, ptr1);
    g.addedge(ptr0, ptr2);
    // //1
    // g.addedge(1, 0);
    // g.addedge(1, 3);
    // //2
    // g.addedge(2, 0);
    // g.addedge(2, 4);
    // //3
    // g.addedge(3, 1);
    // g.addedge(3, 4);
    // g.addedge(3, 5);
    // //4
    // g.addedge(4, 2);
    // g.addedge(4, 3);
    // g.addedge(4, 5);
    // //5
    // g.addedge(5, 3);
    // g.addedge(5, 4);
    // g.addedge(5, 6);
    // //6
    // g.addedge(6, 5);
    g.display();
}