#include "word_ladder.h"

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

void word_ladder::my_dfs(std::string from, std::vector<std::string>& seq) {
	if (from == startWord) {
		reverse(seq.begin(), seq.end());
		ans.push_back(seq);
		reverse(seq.begin(), seq.end());
		return;
	}
	const int steps = wordSteps[from];
	for (char& c : from) { 
		const char original = c;
		for (char ch = 'a'; ch <= 'z'; ++ch) {
			c = ch;
			if (wordSteps.find(from) != wordSteps.end() && wordSteps[from] + 1 == steps) {
				seq.push_back(from);
				my_dfs(from, seq);
				seq.pop_back();
			}
		}
		c = original;
	}
}

void word_ladder::my_bfs(const std::string& from, const std::string& to, std::unordered_set<std::string>& lexicon) {
	std::queue<std::string> myQueue;
	myQueue.push({from});
	lexicon.erase(from);
	wordSteps[from] = 1;
	startWord = from;
	while (not myQueue.empty()) {
		std::string word = myQueue.front();
		int steps = wordSteps[word];
		myQueue.pop();
		if (word == to)
			break;
		transform_word(word, lexicon, myQueue, steps);
	}
}

void word_ladder::transform_word(std::string& word,
                                std::unordered_set<std::string>& lexicon,
                                std::queue<std::string>& myQueue,
                                int steps) {
	for (char& c : word) {
		const char original = c;
		for (char ch = 'a'; ch <= 'z'; ch++) {
			c = ch;
			if (lexicon.find(word) != lexicon.end()) {
				myQueue.push({word});
				lexicon.erase(word);
				wordSteps[word] = steps + 1;
			}
		}
		c = original;
	}
}

void word_ladder::clear_state() {
	ans.clear();
	wordSteps.clear();
	startWord.clear();
}

auto word_ladder::generate(const std::string& from, const std::string& to, const std::unordered_set<std::string>& lexicon)
    -> std::vector<std::vector<std::string>> {
	clear_state();
	if (lexicon.find(from) == lexicon.end() or lexicon.find(to) == lexicon.end()) {
		return {};
	}
	std::unordered_set<std::string> mylex(lexicon.begin(), lexicon.end());
	my_bfs(from, to, mylex);
	if (wordSteps.find(to) != wordSteps.end()) {
		std::vector<std::string> seq;
		seq.push_back(to);
		my_dfs(to, seq);
		std::sort(ans.begin(), ans.end());
	}
	return ans;
}