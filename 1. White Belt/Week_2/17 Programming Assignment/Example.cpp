#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

int main() {
    size_t q = 0;
    cin >> q;

    map<string, set<string>> words;

    for (size_t i = 0; i < q; i++)
    {
        string operation;
        cin >> operation;

        if (operation == "ADD")
        {
            string word_1;
            cin >> word_1;

            string word_2;
            cin >> word_2;

            words[word_1].insert(word_2);
            words[word_2].insert(word_1);
        }
        else
        if (operation == "COUNT")
        {
            string word;
            cin >> word;

            cout << words[word].size() << endl;
        }
        else
        if (operation == "CHECK")
        {
            string word_1;
            cin >> word_1;

            string word_2;
            cin >> word_2;

            if (words[word_1].count(word_2) > 0)
            {
                cout << "YES" << endl;
            }
            else
            {
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}
