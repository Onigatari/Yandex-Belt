#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;


template<typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    const int length = range_end - range_begin;
    if (length < 2)
        return;

    vector<typename RandomIt::value_type> elements(
            make_move_iterator(range_begin), make_move_iterator(range_end));

    auto one_third = begin(elements) + length / 3;
    auto two_third = begin(elements) + length * 2 / 3;

    MergeSort(begin(elements), one_third);
    MergeSort(one_third, two_third);
    MergeSort(two_third, end(elements));

    vector<typename RandomIt::value_type> interim_result;
    merge(make_move_iterator(begin(elements)), make_move_iterator(one_third),
          make_move_iterator(one_third), make_move_iterator(two_third),
          back_inserter(interim_result));

    merge(make_move_iterator(begin(interim_result)),
          make_move_iterator(end(interim_result)),
          make_move_iterator(two_third),
          make_move_iterator(end(elements)),
          range_begin);
}

void TestIntVector() {
    vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
    MergeSort(begin(numbers), end(numbers));
    ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    return 0;
}