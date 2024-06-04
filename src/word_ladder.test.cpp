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

TEST_CASE("word_ladder::generate two paths") {
	auto const lexicon = std::unordered_set<std::string>{"hit", "hot", "dot", "dog", "cog", "lot", "log"};

	const auto expected =
	    std::vector<std::vector<std::string>>{{"hit", "hot", "dot", "dog", "cog"}, {"hit", "hot", "lot", "log", "cog"}};

	auto ladders = word_ladder::generate("hit", "cog", lexicon);

	std::sort(ladders.begin(), ladders.end());
	CHECK(ladders == expected);
}

TEST_CASE("word_ladder::generate with starting word not in lexicon") {
	auto const lexicon = std::unordered_set<std::string>{"hot", "dot", "dog", "cog", "lot", "log"};

	const auto expected = std::vector<std::vector<std::string>>{};

	auto ladders = word_ladder::generate("hit", "cog", lexicon);

	CHECK(ladders == expected);
}

TEST_CASE("word_ladder::generate from awake to sleep") {
	auto const english_words = ::word_ladder::read_lexicon("english.txt");

	const auto expected = std::vector<std::vector<std::string>>{
	    {"awake", "aware", "sware", "share", "sharn", "shawn", "shewn", "sheen", "sheep", "sleep"},
	    {"awake", "aware", "sware", "share", "shire", "shirr", "shier", "sheer", "sheep", "sleep"}};

	auto ladders = word_ladder::generate("awake", "sleep", english_words);

	std::sort(ladders.begin(), ladders.end());
	CHECK(ladders == expected);
}

TEST_CASE("word_ladder::generate from airplane to tricycle") {
	auto const english_words = ::word_ladder::read_lexicon("english.txt");

	const auto expected = std::vector<std::vector<std::string>>{};

	auto ladders = word_ladder::generate("airplane", "tricycle", english_words);

	CHECK(ladders == expected);
}