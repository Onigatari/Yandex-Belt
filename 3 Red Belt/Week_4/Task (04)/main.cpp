#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

template<typename TAirport>
class AirportCounter {
public:
    AirportCounter() {
        data.fill(0);
    }

    template<typename TIterator>
    AirportCounter(TIterator begin, TIterator end)
            : AirportCounter() {
        for (; begin != end; ++begin) {
            Insert(*begin);
        }
    }

    size_t Get(TAirport airport) const {
        return data[static_cast<size_t>(airport)];
    }

    void Insert(TAirport airport) {
        ++data[static_cast<size_t>(airport)];
    }

    void EraseOne(TAirport airport) {
        --data[static_cast<size_t>(airport)];
    }

    void EraseAll(TAirport airport) {
        data[static_cast<size_t>(airport)] = 0;
    }

    static const size_t SIZE = static_cast<size_t>(TAirport::Last_);
    using Item = pair<TAirport, size_t>;
    using Items = array<Item, SIZE>;

    Items GetItems() const {
        Items items;
        for (size_t airport_idx = 0; airport_idx < SIZE; ++airport_idx) {
            items[airport_idx] = {static_cast<TAirport>(airport_idx), data[airport_idx]};
        }
        return items;
    }

private:
    array<size_t, SIZE> data;
};