#include <iostream>
#include <string>
#include <vector>

using namespace std;

const vector<int> MONTH_LENGTHS =
  {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const int MONTH_COUNT = MONTH_LENGTHS.size();

int main() {
    const vector<int> days_in_month =
            { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    const int month_count = days_in_month.size();

    size_t month = 0;

    size_t q = 0;
    cin >> q;

    vector<vector<string>> days_concerns(days_in_month[month]);

    for (size_t i = 0; i < q; i++)
    {
        string operation;
        cin >> operation;

        if (operation == "ADD")
        {
            size_t day = 0;
            cin >> day;

            string concern;
            cin >> concern;

            days_concerns[--day].push_back(concern);
        }
        else
        if (operation == "NEXT")
        {
            const size_t old_month_lng = days_in_month[month];

            month = (month + 1) % month_count;

            const size_t new_month_lng = days_in_month[month];

            if (new_month_lng < old_month_lng)
            {
                vector<string> & last_day_concerns =
                        days_concerns[new_month_lng - 1];

                for (size_t i = new_month_lng; i < old_month_lng; i++)
                {
                    last_day_concerns.insert(end(last_day_concerns),
                                             begin(days_concerns[i]), end(days_concerns[i]));
                }
            }
            days_concerns.resize(new_month_lng);
        }
        else
        if (operation == "DUMP")
        {
            size_t day = 0;
            cin >> day;

            cout << days_concerns[--day].size() << " ";

            for (const string & concern : days_concerns[day])
            {
                cout << concern << " ";
            }
            cout << endl;
        }
    }
    return 0;
}