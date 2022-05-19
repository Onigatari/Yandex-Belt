#include <iostream>
#include <vector>

int main()
{
    size_t size = 0;
    cin >> size;

    int sum = 0;
    vector<int> temperatures(size);
    for (auto & temperature : temperatures)
    {
        cin >> temperature;
        sum += temperature;
    }

    int avg = sum / size;
    vector<int> result;
    for (size_t i = 0; i < size; i++)
    {
        if (temperatures[i] > avg)
        {
            result.push_back(i);
        }
    }

    cout << result.size() << std::endl;

    for (const auto result_index : result)
    {
        cout << result_index << " ";
    }
    cout << std::endl;
    return 0;
}