#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <deque>
#include <vector>
#include <map>
#include <string>

using namespace std;

class InvertedIndex {
public:
    void Add(string &&document);

    vector<pair<size_t, size_t>> Lookup(string_view word) const;

    const string &GetDocument(size_t id) const {
        return docs[id];
    }

private:
    map<string_view, vector<pair<size_t, size_t>>> index;
    deque<string> docs;
};

class SearchServer {
public:
    SearchServer() = default;

    explicit SearchServer(istream &document_input);

    void UpdateDocumentBase(istream &document_input);

    void AddQueriesStream(istream &query_input, ostream &search_results_output);

private:
    InvertedIndex index;
};