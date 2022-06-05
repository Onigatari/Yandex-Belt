#include <cstdint>
#include <algorithm>

using namespace std;

// Реализуйте SimpleVector в этом файле
// и отправьте его на проверку

template<typename T>
class SimpleVector {
public:
    SimpleVector() = default;

    explicit SimpleVector(size_t size);

    SimpleVector(const SimpleVector &sv);

    SimpleVector(SimpleVector &&sv);

    ~SimpleVector();

    T &operator[](size_t index);

    T *begin();

    T *end();

    const T *begin() const;

    const T *end() const;

    size_t Size() const;

    size_t Capacity() const;

    void PushBack(const T &value);

    void PushBack(T &&value);

private:
    T *data = nullptr;
    size_t size = 0;
    size_t capacity = 0;
};
template <typename T>
SimpleVector<T>::SimpleVector(size_t size) : size(size), capacity(size * 2), data(new T[capacity]{})
{

}

template <typename T>
SimpleVector<T>::SimpleVector(const SimpleVector& sv) : size(sv.size), capacity(sv.capacity), data(new T[sv.capacity]{})
{
    copy(sv.begin(), sv.end(), begin());
}

template <typename T>
SimpleVector<T>::SimpleVector(SimpleVector&& sv) : size(sv.size), capacity(sv.capacity), data(sv.data)
{
    sv.size = 0;
    sv.capacity = 0;
    sv.data = nullptr;
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
T *SimpleVector<T>::begin() {
    return data;
}

template<typename T>
T *SimpleVector<T>::end() {
    return data + size;
}

template<typename T>
const T *SimpleVector<T>::begin() const {
    return data;
}

template<typename T>
const T *SimpleVector<T>::end() const {
    return data + size;
}

template<typename T>
size_t SimpleVector<T>::Size() const {
    return size;
}

template<typename T>
size_t SimpleVector<T>::Capacity() const {
    return capacity;
}

template<typename T>
void SimpleVector<T>::PushBack(const T &value) {
    if (size == capacity) {
        auto temp = new T[(capacity += 1) *= 2];

        for (size_t i = 0; i < size; ++i) {
            temp[i] = data[i];
        }

        delete[] data;
        data = temp;
    }
    data[++size - 1] = value;
}

template<typename T>
void SimpleVector<T>::PushBack(T &&value) {
    if (size == capacity) {
        auto temp = new T[(capacity += 1) *= 2];

        for (size_t i = 0; i < size; ++i) {
            temp[i] = move(data[i]);
        }

        delete[] data;
        data = move(temp);
    }
    data[++size - 1] = move(value);
}