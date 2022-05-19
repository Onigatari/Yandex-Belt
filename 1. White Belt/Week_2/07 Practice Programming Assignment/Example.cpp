vector<int> Reversed(const vector<int> & input)
{
    vector<int> temp;
    for (auto it = input.rbegin(); it != input.rend(); ++it) {
        temp.push_back(*it);
    }
    return temp;
}