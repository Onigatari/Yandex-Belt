#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    size_t count_oper = 0;
    cin >> count_oper;

    vector<bool> queue;
    for (size_t i = 0; i < count_oper; i++) {
        string operation;
        cin >> operation;

        if (operation == "COME") {
            size_t count = 0;
            cin >> count;

            queue.resize(queue.size() + count, false);
        }
        else if (operation == "WORRY" || operation == "QUIET") {
            size_t count = 0;
            cin >> count;

            queue[count] = (operation == "WORRY");
        }
        else if (operation == "WORRY_COUNT") {
            cout << std::count(begin(queue), end(queue), true) << endl;
        }
    }

    return 0;
}