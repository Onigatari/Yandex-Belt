#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double a, b, c;
    cin >> a >> b >> c;

    double D = pow(b, 2) - 4 * a * c;

    if (a == 0) {
        if (b != 0) {
            cout << -c / b << endl;
        }
    }
    else if (D == 0) {
        cout << -b / (2 * a) << endl;
    }
    else if (D > 0) {
        double x1 = (-b + sqrt(D)) / (2 * a);
        double x2 = (-b - sqrt(D)) / (2 * a);
        cout << x1 << " " << x2 << endl;
    }

    return 0;
}