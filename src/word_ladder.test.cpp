#include "word_ladder.h"

#include <catch2/catch.hpp>

TEST_CASE("word_ladder::read_lexicon works as expected") {
	std::string temp_filename = "temp_lexicon.txt";
	{
        std::ofstream temp_file(temp_filename);
        REQUIRE(temp_file.is_open());
        temp_file << "adobe\n";
        temp_file << "blender\n";
        temp_file << "clion\n";
        temp_file << "docker\n";
        temp_file << "eclipse\n";
    }
	auto const english_lexicon = ::word_ladder::read_lexicon(temp_filename);
	std::remove(temp_filename.c_str());
    REQUIRE(!english_lexicon.empty());
    CHECK(english_lexicon.size() == 5);
    CHECK(english_lexicon.find("adobe") != english_lexicon.end());
    CHECK(english_lexicon.find("blender") != english_lexicon.end());
    CHECK(english_lexicon.find("clion") != english_lexicon.end());
    CHECK(english_lexicon.find("docker") != english_lexicon.end());
    CHECK(english_lexicon.find("eclipse") != english_lexicon.end());
    CHECK(english_lexicon.find("jetbrains") == english_lexicon.end());
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
