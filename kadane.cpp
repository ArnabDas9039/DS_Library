#include<iostream>
using namespace std;
int max(int x, int y){
    return x > y ? x : y;
}
int main(void){
    int n = 7;
    // cin >> n;
    int a[n] = { 2, 3, -8, 7, -1, 2, 3 };
    int max_end = a[0], max_sum = a[0];
    int rstart = 0, rend = 0, curr = 0;
    for(int i = 1; i < n; i += 1){
        max_end = max(a[i], max_end + a[i]);
        curr = a[i] + max_end < a[i] ? i : curr;
        if(max_end > max_sum){
            rstart = curr;
            rend = i;
        }
        max_sum = max(max_sum, max_end);
    }
    for(int i = rstart + 1; i <= rend; i += 1){
        cout << a[i] << ", ";
    }

    cout << endl;
    return 0;
}