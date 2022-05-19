#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    size_t count = 0;
    cin >> count;

    vector<string> words(count);

    for (auto & word : words)
    {
        cin >> word;
    }

    auto compare_char = [](const char c_lft, const char c_rgh)
    {
        return tolower(c_lft) < tolower(c_rgh);
    };

    auto compare = [compare_char](const string & lft, const string & rgh)
    {
        return lexicographical_compare(begin(lft), end(lft), begin(rgh), end(rgh), compare_char);
    };

    sort(words.begin(), words.end(), compare);
    copy(words.begin(), words.end(), ostream_iterator<string>(cout, " "));
    return 0;
}