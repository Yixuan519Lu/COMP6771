#ifndef COMP6771_WORD_LADDER_H
#define COMP6771_WORD_LADDER_H

#include <string>
#include <unordered_set>
#include <cstddef>
#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>
#include <cstdio>

namespace word_ladder {
    // Given a file path to a newline-separated list of words...
    // Loads those words into an unordered set and returns it.
    auto read_lexicon(const std::string& path) -> std::unordered_set<std::string>;

    // Given a start word and destination word, returns all the shortest possible paths from the
    // start word to the destination, where each word in an individual path is a valid word per the
    // provided lexicon.
    // Preconditions:
    // - from.size() == to.size()
    // - lexicon.contains(from)
    // - lexicon.contains(to)
    void myDfs(const std::string from, std::vector<std::string> &seq);
    auto generate(
        const std::string& from,
        const std::string& to,
        const std::unordered_set<std::string>& lexicon) -> std::vector<std::vector<std::string>>;

    namespace {
        std::vector<std::vector<std::string>> ans; // final answer
        std::unordered_map<std::string, int> wordSteps; // record word steps
        std::string startWord; // record from
    }

} // namespace word_ladder

#endif // COMP6771_WORD_LADDER_H
