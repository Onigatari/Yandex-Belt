#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
    ifstream input("input.txt");

    size_t row = 0;
    size_t col = 0;

    if (input.is_open())
    {
        input >> row;
        input >> col;
        input.ignore(1);

        for (size_t i = 0; i < row; i++)
        {
            for (size_t j = 0; j <= (col * 2 - 1); j++)
            {
                int number = 0;
                cout << setw(10) << fixed;
                if (j % 2 == 0 && j < (col * 2 - 2))
                {
                    input >> number;
                    cout << number << " ";
                }
                else
                if (j % 2 == 0 && j == (col *2 - 2))
                {
                    input >> number;
                    cout << number;
                }
                else
                {
                    input.ignore(1);
                }
            }
            cout << endl;
        }
    }
    return 0;
}