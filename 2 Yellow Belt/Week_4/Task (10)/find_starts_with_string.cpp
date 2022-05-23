#include <algorithm>
#include <utility>
#include <string>


template<typename RandomIt>
pair <RandomIt, RandomIt> FindStartsWith( RandomIt range_begin, RandomIt range_end, string prefix) {

    auto left = lower_bound(range_begin, range_end, prefix);

    string upper_bound = prefix;
    ++upper_bound[upper_bound.size() - 1];

    auto right = lower_bound(range_begin, range_end, upper_bound);

    return {left, right};
}