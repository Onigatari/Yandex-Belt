#include <iostream>
#include <map>
#include <string>
#include <vector>

//-------------------------------------------------------------------------------------------------
int main()
{
    size_t q = 0;
    cin >> q;

    map<string, vector<string>> buses_to_stops;
    map<string, vector<string>> stops_to_buses;

    for (size_t i = 0; i < q; i++)
    {
        string operation;
        cin >> operation;

        if (operation == "NEW_BUS")
        {
            string bus;
            cin >> bus;

            size_t stop_count = 0;
            cin >> stop_count;

            vector<string> & stops = buses_to_stops[bus];
            stops.resize(stop_count);

            for (auto & stop : stops)
            {
                cin >> stop;
                stops_to_buses[stop].push_back(bus);
            }
        }
        else
        if (operation == "BUSES_FOR_STOP")
        {
            string stop_name;
            cin >> stop_name;

            if (stops_to_buses.count(stop_name) == 0)
            {
                cout << "No stop" << endl;
            }
            else
            {
                for (const auto bus : stops_to_buses[stop_name])
                {
                    cout << bus << " ";
                }
                cout << endl;
            }
        }
        else
        if (operation == "STOPS_FOR_BUS")
        {
            string bus_name;
            cin >> bus_name;

            if (buses_to_stops.count(bus_name) == 0)
            {
                cout << "No bus" << endl;
            }
            else
            {
                for (const auto & stop : buses_to_stops[bus_name])
                {
                    cout << "Stop " << stop << ": ";

                    if (stops_to_buses[stop].size() == 1)
                    {
                        cout << "no interchange" << endl;
                    }
                    else
                    {
                        for (const auto & other_bus : stops_to_buses[stop])
                        {
                            if (bus_name != other_bus)
                            {
                                cout << other_bus << " ";
                            }
                        }
                        cout << endl;
                    }
                }
            }
        }
        else
        if (operation == "ALL_BUSES")
        {
            if (buses_to_stops.empty())
            {
                cout << "No buses" << endl;
            }
            else
            {
                for (const auto & bus_item : buses_to_stops)
                {
                    cout << "Bus " << bus_item.first << ": ";

                    for (const auto & stop : bus_item.second)
                    {
                        cout << stop << " ";
                    }
                    cout << endl;
                }
            }
        }
    }
    return 0;
}
//-------------------------------------------------------------------------------------------------