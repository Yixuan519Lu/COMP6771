#include "word_ladder.h"

#include <catch2/catch.hpp>

TEST_CASE("word_ladder::read_lexicon works as expected") {
	auto const english_lexicon = ::word_ladder::read_lexicon("./english.txt");
	CHECK(std::size(english_lexicon) == 127142);
}

// TEST_CASE("at -> it") {
// 	auto const lexicon = std::unordered_set<std::string>{
// 		"at",
// 		"it"
// 	};

// 	const auto expected = std::vector<std::vector<std::string>>{
// 		{"at", "it"}
// 	};

// 	auto const ladders = word_ladder::generate("at", "it", lexicon);

// 	CHECK(ladders == expected);
// }
