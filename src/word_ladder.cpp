#include "word_ladder.h"
#include <vector>

auto word_ladder::read_lexicon(const std::string &path) -> std::unordered_set<std::string> {
	std::ifstream inFile;
	std::string word;
	std::unordered_set<std::string> lexicon;
	inFile.open(path);
	if (!inFile) {
    	exit(1);  
	}
	while(inFile>>word){
		lexicon.insert(word);
	}
	inFile.close();

	return lexicon;
}

/*
find all possible words in current level
*/
auto word_ladder::find_neighbors(const std::string &word, const std::unordered_set<std::string> &lexicon, const std::set<std::string> &visited) -> std::vector<std::string> {
    std::vector<std::string> neighbors;
    for (size_t i = 0; i < word.size(); i++) {
        auto new_word = word;
        for (char c = 'a'; c <= 'z'; ++c) {
            new_word[i] = c;
            if (new_word != word && lexicon.find(new_word) != lexicon.end() && visited.find(new_word) == visited.end()) {
                neighbors.push_back(new_word);
            }
        }
    }
    return neighbors;
}

auto word_ladder::generate(
	const std::string &from,
	const std::string &to,
	const std::unordered_set<std::string> &lexicon
) -> std::vector<std::vector<std::string>> {
	//(void)from;
	(void)to;
	(void)lexicon;
	std::set<std::string> visited;
	std::queue<std::vector<std::string>> myqueue;
	myqueue.push({from});
	visited.insert(from);
	while(!myqueue.empty()){
		std::vector<std::string> curPath = myqueue.front();
		myqueue.pop();
	}
	return {};
}