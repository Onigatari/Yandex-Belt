#include <iostream>
#include <string>
#include <map>

using namespace std;

class Person
{
public:
    void ChangeFirstName(int year, const string & first_name)
    {
        first_names[year] = first_name;
    }

    void ChangeLastName(int year, const string & last_name)
    {
        last_names[year] = last_name;
    }

    string GetFullName(int year)
    {
        const string first_name = GetFirstName(year, first_names);
        const string last_name = GetLastName(year, last_names);
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
private:
    // приватные поля
    string GetFirstName(int year, map<int, string> & firstname)
    {
        while (firstname.count(year) == 0 && year > 0)
        {
            --year;
        }
        string first = firstname[year];
        return first;
    }

    string GetLastName(int year, map<int, string> & lastname)
    {
        while (lastname.count(year) == 0 && year > 0)
        {
            --year;
        }
        string last = lastname[year];
        return last;
    }

    map<int, string> first_names;
    map<int, string> last_names;
};

int main()
{
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990})
    {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970})
    {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970})
    {
        cout << person.GetFullName(year) << endl;
    }
    return 0;
}