#include <iostream>
#include <string>

using namespace std;

int main() {
    string str;
    cin >> str;

    size_t count = 0;

    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] == 'f') {
            count++;
            if (count == 2) {
                cout << i << endl;
                break;
            }
        }
    }

    if (count == 1) {
        cout << -1 << endl;
    }
    else if (count == 0) {
        cout << -2 << endl;
    }

    return 0;
}