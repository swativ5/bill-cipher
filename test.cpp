#include <bits/stdc++.h>
using namespace std;

int gud_mod(int a, int b) {
    int m = a % b;
    if (m < 0) {
        m = (m + abs(b));
    }
    return m;
}

int main()  {
    char c = 'a';
    int n = c;
    
    cout << c << " " << n << " wee ";
    cout << -1001 % 2 << " "; 
    cout << gud_mod(-1001, 2);
    return 0;
}