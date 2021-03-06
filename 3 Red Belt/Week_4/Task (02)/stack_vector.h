#pragma once

#include <stdexcept>
#include <array>

using namespace std;

template<typename T, size_t N>
class StackVector {
public:
    explicit StackVector(size_t a_size = 0);

    T &operator[](size_t index);

    const T &operator[](size_t index) const;

    T *begin();

    T *end();

    const T *begin() const;

    const T *end() const;

    size_t Size() const;

    size_t Capacity() const;

    void PushBack(const T &value);

    T PopBack();

private:
    array<T, N> data;
    size_t size_ = 0;
};

template<typename T, size_t N>
StackVector<T, N>::StackVector(size_t a_size) : size_(a_size) {
    if (size_ > N) {
        throw invalid_argument("Error! Large size!");
    }
}

template<typename T, size_t N>
T &StackVector<T, N>::operator[](size_t index) {
    return data[index];
}

template<typename T, size_t N>
const T &StackVector<T, N>::operator[](size_t index) const {
    return data[index];
}

template<typename T, size_t N>
T *StackVector<T, N>::begin() {
    return begin(data);
}

template<typename T, size_t N>
T *StackVector<T, N>::end() {
    return begin(data) + size_;
}

template<typename T, size_t N>
const T *StackVector<T, N>::begin() const {
    return begin(data);
}

template<typename T, size_t N>
const T *StackVector<T, N>::end() const {
    return begin(data) + size_;
}

template<typename T, size_t N>
size_t StackVector<T, N>::Size() const {
    return size_;
}

template<typename T, size_t N>
size_t StackVector<T, N>::Capacity() const {
    return N;
}

template<typename T, size_t N>
void StackVector<T, N>::PushBack(const T &value) {
    if (size_ >= N) {
        throw overflow_error("Error! Vector overflow!");
    }

    data[size_++] = value;
}

template<typename T, size_t N>
T StackVector<T, N>::PopBack() {
    if (size_ == 0) {
        throw underflow_error("Error! Vector full!");
    }

    return data[--size_];
}


