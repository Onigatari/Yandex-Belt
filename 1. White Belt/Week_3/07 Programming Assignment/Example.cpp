#include <iostream>
#include <string>
#include <vector>
#include <map>

string FindNameByYear(int year, const map<int, string> & names)
{
    string name;

    for (const auto & item : names)
    {
        if (item.first <= year)
        {
            name = item.second;
        }
        else
        {
            break;
        }
    }
    return name;
}

string GetHistory(int year, const map<int, string> & names)
{
    vector<string> names_history;
    string current_name = "";

    for (const auto& item : names)
    {
        if (item.first <= year)
        {
            if (item.second != current_name)
            {
                vector<string> v = { item.second };
                names_history.insert(begin(names_history), begin(v), end(v));
                current_name = item.second;
            }
        }
        else
        {
            break;
        }
    }

    string history = "";

    for (size_t i = 1; i < names_history.size(); ++i)
    {
        if (history.size() == 0)
        {
            history += names_history[i];
        }
        else
        {
            history = history + ", " + names_history[i];
        }
    }
    return history;
}

class Person
{
public:
    Person(const string & first_name, const string & last_name, int year)
    {
        first_names[year] = first_name;
        last_names[year] = last_name;

        year_of_birth = year;
    }

    void ChangeFirstName(int year, const string & first_name)
    {
        if (year >= year_of_birth)
        {
            first_names[year] = first_name;
        }
    }

    void ChangeLastName(int year, const string & last_name)
    {
        if (year >= year_of_birth)
        {
            last_names[year] = last_name;
        }
    }

    string GetFullName(int year) const
    {
        if (year < year_of_birth)
        {
            return "No person";
        }

        const string first_name = FindNameByYear(year, first_names);
        const string last_name = FindNameByYear(year, last_names);

        string full_name = first_name + " " + last_name;

        if (first_name.size() == 0 && last_name.size() == 0)
        {
            full_name = "Incognito";
            return full_name;
        }
        else
        if (first_name.size() == 0)
        {
            full_name = last_name + " with unknown first name";
            return full_name;
        }
        else
        if (last_name.size() == 0)
        {
            full_name = first_name + " with unknown last name";
            return full_name;
        }
        return full_name;
    }

    string GetFullNameWithHistory(int year) const
    {
        if (year < year_of_birth)
        {
            return "No person";
        }

        const string first_name = FindNameByYear(year, first_names);
        const string last_name = FindNameByYear(year, last_names);
        const string history_first_name = GetHistory(year, first_names);
        const string history_last_name = GetHistory(year, last_names);

        string full_name = first_name + " (" + history_first_name + ")" + " " + last_name + " (" + history_last_name + ")";

        if (first_name.size() == 0 && last_name.size() == 0)
        {
            full_name = "Incognito";
            return full_name;
        }
        else
        if (first_name.size() == 0)
        {
            if (history_last_name.size() == 0)
            {
                full_name = last_name + " with unknown first name";
                return full_name;
            }
            else
            {
                full_name = last_name + " (" + history_last_name + ")" + " with unknown first name";
                return full_name;
            }
        }
        else
        if (last_name.size() == 0)
        {
            if (history_first_name.size() == 0)
            {
                full_name = first_name + " with unknown last name";
                return full_name;
            }
            else
            {
                full_name = first_name + " (" + history_first_name + ")" + " with unknown last name";
                return full_name;
            }
        }
        else
        if (history_first_name.size() == 0 && history_last_name.size() == 0)
        {
            full_name = first_name + " " + last_name;
            return full_name;
        }
        else
        if (history_first_name.size() == 0)
        {
            full_name = first_name + " " + last_name + " (" + history_last_name + ")";
            return full_name;
        }
        else
        if (history_last_name.size() == 0)
        {
            full_name = first_name + " (" + history_first_name + ") " + last_name;
            return full_name;
        }
        return full_name;
    }
private:
    map<int, string> first_names;
    map<int, string> last_names;
    int year_of_birth;
};

int main()
{
    Person person("Polina", "Sergeeva", 1960);
    for (int year : {1959, 1960})
    {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1965, "Appolinaria");
    person.ChangeLastName(1967, "Ivanova");
    for (int year : {1965, 1967})
    {
        cout << person.GetFullNameWithHistory(year) << endl;
    }
    return 0;
}
//-------------------------------------------------------------------------------------------------