#include <iostream>

using namespace std;

int main() {
    int a = 0;
    cin >> a;

    int b = 0;
    cin >> b;

    int c = 0;
    while (b != 0)
    {
        c = a % b;
        a = b;
        b = c;
    }
    cout << a;

    return 0;
}