#include "word_ladder.h"
#include <cstddef>
#include <vector>

auto word_ladder::read_lexicon(const std::string& path) -> std::unordered_set<std::string> {
	std::ifstream inFile;
	std::string word;
	std::unordered_set<std::string> lexicon;
	inFile.open(path);
	if (!inFile) {
		exit(1);
	}
	while (inFile >> word) {
		lexicon.insert(word);
	}
	inFile.close();

	return lexicon;
}

auto word_ladder::build_buckets(const std::unordered_set<std::string>& lexicon) -> std::unordered_map<std::string, std::vector<std::string>> {
    std::unordered_map<std::string, std::vector<std::string>> buckets;
    for (const auto& word : lexicon) {
        for (size_t i = 0; i < word.size(); ++i) {
            std::string bucket = word.substr(0, i) + "_" + word.substr(i + 1);
            buckets[bucket].push_back(word);
        }
    }
    return buckets;
}

/*
find all possible words in current level
*/
auto word_ladder::find_neighbors(const std::string& word,
                    const std::unordered_map<std::string, std::vector<std::string>>& buckets,
                    const std::unordered_set<std::string>& visited) -> std::vector<std::string> {
    std::vector<std::string> neighbors;
    for (size_t i = 0; i < word.size(); ++i) {
        std::string bucket = word.substr(0, i) + "_" + word.substr(i + 1);
        if (buckets.find(bucket) != buckets.end()) {
            for (const auto& neighbor : buckets.at(bucket)) {
                if (visited.find(neighbor) == visited.end()) {
                    neighbors.push_back(neighbor);
                }
            }
        }
    }
    return neighbors;
}

auto word_ladder::generate(const std::string& from,
                           const std::string& to,
                           const std::unordered_set<std::string>& lexicon) -> std::vector<std::vector<std::string>> {
    bool isfound = false;
    std::vector<std::vector<std::string>> result;
    std::unordered_set<std::string> visited;
    std::queue<std::vector<std::string>> myqueue;
    auto buckets = word_ladder::build_buckets(lexicon);  
    myqueue.push({from});
    visited.insert(from);

    while (!myqueue.empty() && !isfound) {
        std::unordered_set<std::string> curStageVisited;
        std::size_t curStageSize = myqueue.size();
        for (std::size_t i = 0; i < curStageSize; i++) {
            std::vector<std::string> curPath = myqueue.front();
            myqueue.pop();
            std::string changedWord = curPath.back();
            auto neighbors = word_ladder::find_neighbors(changedWord, buckets, visited);
            for (const auto& neighbor : neighbors) {
                std::vector<std::string> newPath = curPath;
                newPath.push_back(neighbor);
                if (neighbor == to) {
                    result.push_back(newPath);
                    isfound = true;
                } else {
                    myqueue.push(newPath);
                }
                curStageVisited.insert(neighbor);
            }
        }
        visited.insert(curStageVisited.begin(), curStageVisited.end());
    }
    std::sort(result.begin(), result.end());
    return result;
}