#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main() {
    const int COUNT = 100'000;

    int pair_count = 0;
    cin >> pair_count;

    list<int> queue;
    vector<list<int>::iterator> positions(COUNT, end(queue));

    int newSportsman, nextSportsman;
    for (int i = 0; i < pair_count; ++i) {
        cin >> newSportsman >> nextSportsman;
        positions[newSportsman] = queue.insert(positions[nextSportsman], newSportsman);
    }

    for (int x: queue) {
        cout << x << endl;
    }

    return 0;
}