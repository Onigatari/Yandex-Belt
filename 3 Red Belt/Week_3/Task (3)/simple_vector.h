#pragma once

#include <algorithm>

using namespace std;

template<typename T>
class SimpleVector {
public:
    SimpleVector() = default;

    explicit SimpleVector(size_t size);

    ~SimpleVector();

    T &operator[](size_t index);

    T *begin();

    T *end();

    size_t Size() const;

    size_t Capacity() const;

    void PushBack(const T &value);

private:
    T *data = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;
};

template<typename T>
SimpleVector<T>::SimpleVector(size_t size)
        : data(new T[size]), size_(size), capacity_(size) {
}

template<typename T>
SimpleVector<T>::~SimpleVector() {
    delete[] data;
}

template<typename T>
T &SimpleVector<T>::operator[](size_t index) {
    return data[index];
}

template<typename T>
size_t SimpleVector<T>::Size() const {
    return size_;
}

template<typename T>
size_t SimpleVector<T>::Capacity() const {
    return capacity_;
}

template<typename T>
void SimpleVector<T>::PushBack(const T &value) {
    if (size_ >= capacity_) {
        auto new_cap = capacity_ == 0 ? 1 : 2 * capacity_;
        auto new_data = new T[new_cap];
        copy(begin(), end(), new_data);
        delete[] data;
        data = new_data;
        capacity_ = new_cap;
    }
    data[size_++] = value;
}

template<typename T>
T *SimpleVector<T>::begin() {
    return data;
}

template<typename T>
T *SimpleVector<T>::end() {
    return data + size_;
}