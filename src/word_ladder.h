#ifndef COMP6771_WORD_LADDER_H
#define COMP6771_WORD_LADDER_H

#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>

namespace word_ladder {
	// Given a file path to a newline-separated list of words,
	// loads those words into an unordered set and returns it.
	auto read_lexicon(const std::string& path) -> std::unordered_set<std::string>;

	// Given a start word and destination word, returns all the shortest possible paths from the
	// start word to the destination, where each word in an individual path is a valid word per the
	// provided lexicon.
	// Preconditions:
	// - from.size() == to.size()
	// - lexicon.contains(from)
	// - lexicon.contains(to)

	// Uses DFS to backtrack paths.
	void my_dfs(const std::string from, std::vector<std::string>& seq);

	// Uses BFS to find the step count to reach each possible word.
	void my_bfs(const std::string& from, const std::string& to, std::unordered_set<std::string>& lexicon);

	// Tries all possible words.
	void transform_word(std::string& word,
	                    std::unordered_set<std::string>& lexicon,
	                    std::queue<std::string>& myQueue,
	                    int steps);

	// Clears the state including ans, wordSteps, and startWord.
	void clear_state();

	// Generates all shortest paths from start word to destination word using the provided lexicon.
	// Returns a vector of vectors containing all shortest paths.
	auto generate(const std::string& from, const std::string& to, const std::unordered_set<std::string>& lexicon)
	    -> std::vector<std::vector<std::string>>;

	namespace {
		std::vector<std::vector<std::string>> ans; // Stores the final answer
		std::unordered_map<std::string, int> wordSteps; // Records the word steps
		std::string startWord; // Records the starting word
	} // namespace

} // namespace word_ladder

#endif // COMP6771_WORD_LADDER_H
