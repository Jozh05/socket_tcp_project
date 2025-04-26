#include <gtest/gtest.h>
#include "../src/processing/TextProcessor.hpp"

using processing::TextProcessor;

TEST(TextProcessor, EmptyInput) {
    std::string input = "";
    std::string expected = "";
    EXPECT_EQ(TextProcessor::process(input), expected);
}

TEST(TextProcessor, SingleWord) {
    std::string input = "hello";
    std::string expected = "hello";
    EXPECT_EQ(TextProcessor::process(input), expected);
}

TEST(TextProcessor, RemoveDuplicates) {
    std::string input = "a b a c b";
    std::string expected = "a b c";
    EXPECT_EQ(TextProcessor::process(input), expected);
}

TEST(TextProcessor, MultipleSpaces) {
    std::string input = "  alpha    beta alpha   gamma  beta  ";
    std::string expected = "alpha beta gamma";
    EXPECT_EQ(TextProcessor::process(input), expected);
}

TEST(TextProcessor, UnicodeWords) {
    std::string input = "привет мир привет";
    std::string expected = "привет мир";
    EXPECT_EQ(TextProcessor::process(input), expected);
}