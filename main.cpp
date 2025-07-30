#include<iostream>
#include "Array.h"
#include<vector>
#include "Map.h"
#include "Graph.h"
using namespace std;

class Color{
public:
    char* color_name;
    // char *color_hex;
    int R_val, G_val, B_val;

    Color(int r = 0, int g = 0, int b = 0) : R_val(r), G_val(g), B_val(b){}

    ~Color(){}

    friend ostream& operator<<(ostream& os, const Color& c){
        os << "(" << c.R_val << ", " << c.G_val << ", " << c.B_val << ")";
    }
    friend ostream& operator<<(ostream& os, const Color* c){
        os << "(" << c->R_val << ", " << c->G_val << ", " << c->B_val << ")";
    }
};
// int main(){
//     Array<int> a(9);

//     for(int i = 0; i < 5; i++){
//         a.push_back(i + 1);
//     }

//     cout << a;
//     for(int i = 0; i < a.size(); i++){
//         cout << a[i] << " ";
//     }
//     return 0;
// }

// int main(){
//     Map<char, int> a;

//     a['0'] = 48;
//     a['1'] = 49;

//     for(auto i : a){
//         cout << i.first << " " << i.second << endl;
//     }

//     cout << "Hello" << endl;

//     a['3'] = 51;

//     for(auto i : a){
//         cout << i.first << " " << i.second << endl;
//     }
//     return 0;
// }

// int main(){
//     Search_Tree<int> a;

//     a.insert(2);
//     a.insert(1);
//     a.insert(3);
//     a.insert(4);
//     a.insert(5);
//     a.insert(6);

//     for(auto i : a){
//         cout << i;
//     }
// }

// int main(){
//     Ordered_Map<char, int> a;

//     a['0'] = 48;
//     a['1'] = 49;

//     for(auto i : a){
//         cout << i.first << " " << i.second << endl;
//     }

//     return 0;
// }

int main(){
    Graph<int, int> g2;
    cout << "Graph Initialized" << endl;

    g2.createVertex(0);
    g2.createVertex(1);
    g2.createVertex(2);
    g2.createVertex(3);
    g2.createVertex(4);
    g2.createVertex(5);
    g2.createVertex(6);

    // Edges
    g2.addedges(g2.getVertex(0), g2.getVertex(1), 2);
    g2.addedges(g2.getVertex(0), g2.getVertex(2), 4);
    g2.addedges(g2.getVertex(1), g2.getVertex(2), 1);
    g2.addedges(g2.getVertex(1), g2.getVertex(3), 7);
    g2.addedges(g2.getVertex(2), g2.getVertex(4), 1);
    g2.addedges(g2.getVertex(3), g2.getVertex(4), 2);
    g2.addedges(g2.getVertex(3), g2.getVertex(5), 1);
    g2.addedges(g2.getVertex(4), g2.getVertex(5), 5);
    g2.addedges(g2.getVertex(5), g2.getVertex(6), 1);

    // g2.display();

    // cout << "Main display: " << endl;
    // for(auto i : g2.adj){
    //     cout << i.first->value << " -> ";
    //     for(auto j : *i.second){
    //         cout << "(" << j->src->value << ", " << j->dest->value << ", wt: " << j->weight << ") => ";
    //     }
    //     cout << endl;
    // }

    for(auto i = g2.dfsbegin(g2.getVertex(0)); i != g2.dfsend(); ++i){
        cout << *i << " -> ";
    }

    return 0;
}