#include<iostream>
#include "Array.h"
#include<vector>
using namespace std;

class Color{
public:
    char* color_name;
    // char *color_hex;
    int R_val, G_val, B_val;

    Color(int r, int g = 0, int b = 0) : R_val(r), G_val(g), B_val(b){}

    ~Color(){}

    friend ostream& operator<<(ostream& os, const Color& c){
        os << "(" << c.R_val << ", " << c.G_val << ", " << c.B_val << ")";
    }
    friend ostream& operator<<(ostream& os, const Color* c){
        os << "(" << c->R_val << ", " << c->G_val << ", " << c->B_val << ")";
    }
};
int main(){
    Array<int> a(1, 2, 4, 3, 2, 4, 3, 2, 4, 3, 2, 4, 3, 2, 4, 3, 2, 4, 3, 2, 4, 3);

    // a.push_back(1);
    // a.push_back(2);
    // a.push_back(21);
    // a.push_back(4);

    for(int i : a){
        // a.pop_back();
        // cout << i << ", ";
    }
    // cout << endl;

    a[7] = 10;

    cout << a;
    cout << endl;
    // cout << a[7];

    Color* red = new Color(255);
    Color* pink = new Color(120);
    Color* blue = new Color(0);

    Array<Color*> colors(red, pink, blue);

    cout << colors;
}