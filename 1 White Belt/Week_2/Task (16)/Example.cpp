set<string> BuildMapValuesSet(const map<int, string> & map)
{
    set<string> values;

    for (auto & value : map)
    {
        values.insert(value.second);
    }
    return values;
}