#pragma once

#include <chrono>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class LogDuration {
public:
    explicit LogDuration(const string &msg = "") :
            message(msg + "\t| "),
            start(chrono::steady_clock::now()) {

    }

    ~LogDuration() {
        auto finish = chrono::steady_clock::now();
        auto duration = finish - start;

        auto seconds = chrono::duration_cast<chrono::seconds>(duration);
        duration -= seconds;
        auto milliseconds = chrono::duration_cast<chrono::milliseconds>(duration);
        duration -= milliseconds;
        auto microseconds = chrono::duration_cast<chrono::microseconds>(duration);
        duration -= microseconds;
        auto nanoseconds = chrono::duration_cast<chrono::nanoseconds>(duration);
        duration -= nanoseconds;

        cerr
                << message
                << seconds.count() << " sec "
                << milliseconds.count() << " mils "
                << microseconds.count() << " mics "
                << nanoseconds.count() << " nans " << endl;
    }

private:
    string message;
    chrono::steady_clock::time_point start;
};

#define UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
#define UNIQ_ID(lineno) UNIQ_ID_IMPL(lineno)

#define LOG_DURATION(message) LogDuration UNIQ_ID(__LINE__) {message};

struct TotalDuration {
    string message;
    chrono::steady_clock::duration value;

    explicit TotalDuration(const string &msg = "") : message(msg + ": "), value(0) {

    }

    ~TotalDuration() {
        ostringstream os;
        os << message
           << chrono::duration_cast<chrono::milliseconds>(value).count()
           << " ms" << endl;
        cerr << os.str();
    }
};

class AddDuration {
public:
    explicit AddDuration(chrono::steady_clock::duration &dest) : add_to(dest),
                                                                 start(chrono::steady_clock::now()) {}

    explicit AddDuration(TotalDuration &dest) : AddDuration(dest.value) {}

    ~AddDuration() {
        add_to += chrono::steady_clock::now() - start;
    }

private:
    chrono::steady_clock::duration &add_to;
    chrono::steady_clock::time_point start;
};

#define ADD_DURATION(value) AddDuration UNIQ_ID(__LINE__){value};