/*
Given a phrase, count the occurrences of each word in that phrase.

For example for the input "olly olly in come free"

olly: 2
in: 1
come: 1
free: 1

*/

#include <gtest/gtest.h>
#include <map>
#include <string>

using MyMap = std::map<std::string, int>;

MyMap WordsCount(const std::string& str)
{
    return MyMap();
}


TEST(WordsCount, empty_line)
{
    EXPECT_TRUE(WordsCount("").empty());
}

TEST(WordsCount, single_word)
{
    MyMap expected {std::make_pair("singleWord", 1)};
    EXPECT_EQ(expected, WordsCount("singleWord"));
}