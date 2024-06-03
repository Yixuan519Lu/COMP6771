#include "word_ladder.h"
#include <cstddef>

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

/*
use DFS backtrack paths
*/
void word_ladder::myDfs(std::string from, std::vector<std::string>& seq) {
    if (from == startWord) {
        reverse(seq.begin(), seq.end());
        ans.push_back(seq);
        reverse(seq.begin(), seq.end());
        return;
    }
    std::size_t n = from.size();  
    int steps = wordSteps[from];  
    for (std::size_t i = 0; i < n; i++) {  
        char original = from[i];
        for (char ch = 'a'; ch <= 'z'; ch++) {
            from[i] = ch;
            if (wordSteps.find(from) != wordSteps.end() && wordSteps[from] + 1 == steps) {
                seq.push_back(from);
                myDfs(from, seq);
                seq.pop_back();
            }
        }
        from[i] = original;
    }
}

auto word_ladder::generate(const std::string& from,
                           const std::string& to,
                           const std::unordered_set<std::string>& lexicon) -> std::vector<std::vector<std::string>> {
	std::unordered_set<std::string> mylex(lexicon.begin(), lexicon.end());
	std::queue<std::string> myQueue;
	myQueue.push({from});
	mylex.erase(from);
	wordSteps[from] = 1;
	startWord = from;
	std::size_t wordSize = from.size();
	while (!myQueue.empty()) {
		std::string word = myQueue.front();
		int steps = wordSteps[word];
		myQueue.pop();
		if (word == to)
			break;
		for (std::size_t i = 0; i < wordSize; i++) {
			char original = word[i];
			for (char ch = 'a'; ch <= 'z'; ch++) {
				word[i] = ch;
				if (mylex.find(word) != mylex.end()) {
					myQueue.push({word});
					mylex.erase(word);
					wordSteps[word] = steps + 1;
				}
			}
			word[i] = original;
		}
	}
	std::vector<std::string> seq;
	seq.push_back(to);
	myDfs(to, seq);
	std::sort(ans.begin(), ans.end());
	return ans;
}