bool IsPalindrom(string str)
{
    string conversely(str.rbegin(), str.rend());

    if (str == conversely) {
        return true;
    }

    return false;
}