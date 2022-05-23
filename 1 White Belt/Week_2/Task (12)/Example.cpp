#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    size_t q = 0;
    cin >> q;

    map<string, string> country_to_capital;

    for (size_t i = 0; i < q; i++)
    {
        string operation;
        cin >> operation;

        if (operation == "CHANGE_CAPITAL")
        {
            string country;
            cin >> country;

            string new_capital;
            cin >> new_capital;

            if (country_to_capital.count(country) == 0)
            {
                cout << "Introduce new country " << country;
                cout << " with capital " << new_capital;
                cout << endl;
            }
            else
            {
                const string & old_capital = country_to_capital[country];

                if (old_capital == new_capital)
                {
                    cout << "Country " << country;
                    cout << " hasn't changed its capital";
                    cout << endl;
                }
                else
                {
                    cout << "Country " << country;
                    cout << " has changed its capital from ";
                    cout << old_capital << " to " << new_capital;
                    cout << endl;
                }
            }
            country_to_capital[country] = new_capital;
        }
        else
        if (operation == "RENAME")
        {
            string old_country_name;
            cin >> old_country_name;

            string new_country_name;
            cin >> new_country_name;

            if (old_country_name == new_country_name ||
                country_to_capital.count(old_country_name) == 0 ||
                country_to_capital.count(new_country_name) == 1)
            {
                cout << "Incorrect rename, skip" << endl;
            }
            else
            {
                cout << "Country " << old_country_name << " with capital ";
                cout << country_to_capital[old_country_name];
                cout << " has been renamed to " << new_country_name;
                cout << endl;

                country_to_capital[new_country_name] = country_to_capital[old_country_name];
                country_to_capital.erase(old_country_name);
            }
        }
        else
        if (operation == "ABOUT")
        {
            string country;
            cin >> country;

            if (country_to_capital.count(country) == 0)
            {
                cout << "Country " << country << " doesn't exist" << endl;
            }
            else
            {
                cout << "Country " << country << " has capital ";
                cout << country_to_capital[country] << endl;
            }
        }
        else
        if(operation == "DUMP")
        {
            if (country_to_capital.empty())
            {
                cout << "There are no countries in the world" << endl;
            }
            else
            {
                for (auto & cntry : country_to_capital)
                {
                    cout << cntry.first << "/" << cntry.second << " ";
                }
                cout << endl;
            }
        }
    }
    return 0;
}