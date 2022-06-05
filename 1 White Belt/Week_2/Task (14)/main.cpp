#include <iostream>
#include <map>
#include <string>
#include <vector>

int main()
{
    size_t q = 0;
    cin >> q;

    map<vector<string>, size_t> buses;

    for (size_t i = 0; i < q; i++)
    {
        size_t number = 0;
        cin >> number;

        vector<string> stops(number);

        for (auto & stop : stops)
        {
            cin >> stop;
        }

        if (buses.count(stops) == 0)
        {
            const int new_number = buses.size() + 1;
            buses[stops] = new_number;

            cout << "New bus " << new_number << endl;
        }
        else
        {
            cout << "Already exists for " << buses[stops] << endl;
        }
    }
    return 0;
}