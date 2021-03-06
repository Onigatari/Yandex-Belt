#include "stats.h"

Stats::Stats() {
    method_stats = {{"GET",     0},
                    {"POST",    0},
                    {"PUT",     0},
                    {"DELETE",  0},
                    {"UNKNOWN", 0}};
    uri_stats = {{"/",        0},
                 {"/order",   0},
                 {"/product", 0},
                 {"/basket",  0},
                 {"/help",    0},
                 {"unknown",  0}};
}

HttpRequest ParseRequest(string_view line) {
    HttpRequest result;
    line.remove_prefix(line.find_first_not_of(" "));

    result.method = line.substr(0, line.find(" "));
    line.remove_prefix(min(line.find(" ") + 1, line.size()));

    result.uri = line.substr(0, line.find(" "));
    line.remove_prefix(min(line.find(" ") + 1, line.size()));

    result.protocol = line.substr(0, line.find(" "));

    return result;
}

void Stats::AddMethod(string_view method) {
    if (method_stats.find(method) != method_stats.end()) {
        method_stats[method]++;
    } else {
        method_stats["UNKNOWN"]++;
    }
}

void Stats::AddUri(string_view uri) {
    if (uri_stats.find(uri) != uri_stats.end()) {
        uri_stats[uri]++;
    } else {
        uri_stats["unknown"]++;
    }
}

const map<string_view, int> &Stats::GetMethodStats() const {
    return method_stats;
}

const map<string_view, int> &Stats::GetUriStats() const {
    return uri_stats;
}