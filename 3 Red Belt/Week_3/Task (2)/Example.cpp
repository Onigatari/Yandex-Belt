//#include "lib/test_runner.h"

#include <algorithm>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

template<typename T>
void Swap(T *first, T *second) {
    auto temp = *first;
    *first = *second;
    *second = temp;
}

template<typename T>
void SortPointers(vector<T *> &pointers) {
    sort(begin(pointers), end(pointers), [](T *x, T *y) {
        return *x < *y;
    });
}

template<typename T>
void ReversedCopy(T *source, size_t count, T *destination) {
    auto source_begin = source;
    auto source_end = source + count;
    auto dest_begin = destination;

    for (size_t i = 0; i < count; i++) {
        T *source_curr = source_end - i - 1;
        T *dest_curr = dest_begin + i;

        if (dest_curr < source_begin || dest_curr >= source_end) {
            *dest_curr = *source_curr;
        } else if (dest_curr < source_curr) {
            Swap(source_curr, dest_curr);
        }
    }
}