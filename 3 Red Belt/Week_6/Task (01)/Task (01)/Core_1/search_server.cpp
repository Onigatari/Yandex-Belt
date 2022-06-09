#include "search_server.h"
#include "profile.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>

vector<string_view> SplitIntoWords(string_view line) {
    vector<string_view> result;
    size_t temp = line.find_first_not_of(' ', 0);
    do {
        auto space = line.find(' ', temp);
        result.emplace_back(line.substr(temp, space - temp));

        if (space == line.npos) {
            break;
        } else {
            temp = line.find_first_not_of(' ', space);
        }

    } while(temp != line.npos);
    return result;
}

SearchServer::SearchServer(istream &document_input) {
    UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream &document_input) {
    LOG_DURATION("UpdateDocumentBase")
    InvertedIndex new_index;
    for (string current_document; getline(document_input, current_document);) {
        new_index.Add(move(current_document));
    }
    index = move(new_index);
}

void SearchServer::AddQueriesStream(istream &query_input, ostream &search_results_output) {
    LOG_DURATION("AddQueriesStream")

    vector<size_t> docs(50000);
    vector<size_t> indx(50000);
    for (string current_query; getline(query_input, current_query);) {
        size_t few_ind = 0;
        for (const auto &word: SplitIntoWords(current_query)) {
            auto vec = index.Lookup(word);
            for (const auto&[docid, count]: vec) {
                if (docs[docid] == 0) {
                    indx[few_ind++] = docid;
                }
                docs[docid] += count;
            }
        }

        vector<pair<size_t, size_t>> search_result;
        for (size_t docid = 0; docid < few_ind; ++docid) {
            size_t count = 0;
            size_t id = 0;
            swap(count, docs[indx[docid]]);
            swap(id, indx[docid]);
            search_result.emplace_back(id, count);
        }

        const size_t ANSWERS_COUNT = 5;
        partial_sort(begin(search_result),
                          begin(search_result) + min<size_t>(ANSWERS_COUNT, search_result.size()),
                          end(search_result),
                          [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
                              int64_t lhs_docid = lhs.first;
                              auto lhs_hit_count = lhs.second;
                              int64_t rhs_docid = rhs.first;
                              auto rhs_hit_count = rhs.second;
                              return make_pair(lhs_hit_count, -lhs_docid) >
                                     make_pair(rhs_hit_count, -rhs_docid);
                          });

        search_results_output << current_query << ':';
        for (auto[docid, hitcount]: Head(search_result, ANSWERS_COUNT)) {
            search_results_output << " {"
                                  << "docid: " << docid << ", "
                                  << "hitcount: " << hitcount << '}';
        }
        search_results_output << endl;
    }
}

void InvertedIndex::Add(string &&document) {
    docs.push_back(move(document));
    const size_t docid = docs.size() - 1;

    for (const auto &word: SplitIntoWords(docs.back())) {
        auto &vector_pair = index[word];
        if (!vector_pair.empty() && vector_pair.back().first == docid) {
            vector_pair.back().second += 1;
        } else {
            vector_pair.emplace_back(docid, 1);
        }
    }
}

vector<pair<size_t, size_t>> InvertedIndex::Lookup(string_view word) const {
    if (auto it = index.find(word); it != index.end()) {
        return it->second;
    } else {
        return {};
    }
}
