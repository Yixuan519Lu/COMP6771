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
void word_ladder::myDfs(const std::string &word, std::vector<std::string> &seq) {
	(void) word;
	(void)	seq;
}

auto word_ladder::generate(const std::string& from,
                           const std::string& to,
                           const std::unordered_set<std::string>& lexicon) -> std::vector<std::vector<std::string>> {
	//(void)from;
	//(void)to;
	//(void)lexicon;
	std::unordered_set<std::string> mylex(lexicon.begin(), lexicon.end());
	std::queue<std::string> myqueue;
	myqueue.push({from});
	mylex.erase(from);
	wordSteps[from] = 1;
	startWord = from;
	std::size_t sizee = from.size();
	while (!myqueue.empty()) {
		std::string word = myqueue.front();
		int steps = wordSteps[word];
		myqueue.pop();
		if (word == to)
			break;
		for (std::size_t i = 0; i < sizee; i++) {
			char original = word[i];
			for (char ch = 'a'; ch <= 'z'; ch++) {
				word[i] = ch;
				if (mylex.count(word) > 0) {
					myqueue.push({word});
					mylex.erase(word);
					wordSteps[word] = steps + 1;
				}
			}
			word[i] = original;
		}
	}
	if (wordSteps.find(to) != wordSteps.end()) {
		std::vector<std::string> seq;
		seq.push_back(to);
		myDfs(to, seq);
	}
	return {};
}