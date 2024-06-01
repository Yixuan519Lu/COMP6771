#include "word_ladder.h"

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
	return {};
}