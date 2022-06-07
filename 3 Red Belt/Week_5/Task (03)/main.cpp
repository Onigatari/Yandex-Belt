#include "test_runner.h"
#include "profile.h"

#include <numeric>
#include <vector>
#include <tuple>
#include <cstdlib>
#include <algorithm>

using namespace std;

template<typename T>
class SimpleVector {
public:
    SimpleVector() = default;

    explicit SimpleVector(size_t size);

    SimpleVector(const SimpleVector &rhs);

    ~SimpleVector();

    void operator=(const SimpleVector &rhs) {
        if (rhs.size <= capacity) {
            copy(rhs.begin(), rhs.end(), begin());
            size = rhs.size;
        } else {
            SimpleVector<T> tmp(rhs);
            swap(tmp.data, data);
            swap(tmp.size, size);
            swap(tmp.capacity, capacity);
        }
    }

    T &operator[](size_t index);

    T *begin();

    T *end();

    const T *begin() const;

    const T *end() const;

    size_t Size() const;

    size_t Capacity() const;

    void PushBack(const T &value);

private:
    T *data = nullptr;
    size_t size = 0;
    size_t capacity = 0;
};
