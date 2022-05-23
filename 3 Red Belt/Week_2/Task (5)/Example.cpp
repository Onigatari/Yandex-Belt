#include <cstdint>
#include <iostream>
#include <map>
#include <queue>

using namespace std;

struct Booking {
    int64_t time;
    int client_id;
    int room_count;
};

class HotelInfo {
public:
    void Book(const Booking &booking) {
        last_bookings_.push(booking);
        room_count_ += booking.room_count;
        client_booking_counts_[booking.client_id]++;
    }

    int ClientCount(int64_t current_time) {
        RemoveBookings(current_time);
        return client_booking_counts_.size();
    }

    int RoomCount(int64_t current_time) {
        RemoveBookings(current_time);
        return room_count_;
    }

private:
    static const int TIME_WINDOW_SIZE = 86400;

    queue<Booking> last_bookings_;
    int room_count_ = 0;
    map<int, int> client_booking_counts_;

    void PopBooking() {
        const Booking &booking = last_bookings_.front();
        room_count_ -= booking.room_count;
        const auto client_stat_it = client_booking_counts_.find(booking.client_id);

        if (--client_stat_it->second == 0) {
            client_booking_counts_.erase(client_stat_it);
        }
        last_bookings_.pop();
    }

    void RemoveBookings(int64_t current_time) {
        while (!last_bookings_.empty() && last_bookings_.front().time <= current_time - TIME_WINDOW_SIZE) {
            PopBooking();
        }
    }
};

class HotelManager {
public:
    void Book(int64_t time, const string &hotel_name, int client_id, int room_count) {
        current_time_ = time;
        hotels_[hotel_name].Book({time, client_id, room_count});
    }

    int Clients(const string &hotel_name) {
        return hotels_[hotel_name].ClientCount(current_time_);
    }

    int Rooms(const string &hotel_name) {
        return hotels_[hotel_name].RoomCount(current_time_);
    }

private:
    int64_t current_time_ = 0;
    map<string, HotelInfo> hotels_;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    HotelManager manager;

    int q;
    cin >> q;

    for (int i = 0; i < q; i++) {
        string query_type;
        cin >> query_type;

        if (query_type == "BOOK") {
            int64_t time;
            string hotel_name;
            int client_id, room_count;

            cin >> time >> hotel_name >> client_id >> room_count;
            manager.Book(time, hotel_name, client_id, room_count);
        } else {
            string hotel_name;
            cin >> hotel_name;
            if (query_type == "CLIENTS")
                cout << manager.Clients(hotel_name) << endl;
            else if (query_type == "ROOMS")
                cout << manager.Rooms(hotel_name) << endl;
        }
    }

    return 0;
}