/*
Given a word and a list of possible anagrams, select the correct sublist.

Given "listen" and a list of candidates like "enlists" "google" "inlets" "banana" the program should return a list containing "inlets".

_from http://exercism.io/_
*/
#include <gtest/gtest.h>

#include <string>
#include <vector>

using String_vt = std::vector<std::string>;

String_vt GetAnagrams(const std::string& word,
                      const String_vt& wordList)
{
    return String_vt({wordList});
}

TEST(GetAnagrams, GiveOnlyOneWord_word_ReturnIt)
{
    const std::string word("word");

    String_vt expectedAnagrams({word});
    String_vt givenWords = expectedAnagrams;

    EXPECT_EQ(expectedAnagrams, GetAnagrams(word, givenWords));
}

TEST(GetAnagrams, GiveOnlyOneWord_hello_ReturnIt)
{
    const std::string word("hello");

    String_vt expectedAnagrams({word});
    String_vt givenWords = expectedAnagrams;

    EXPECT_EQ(expectedAnagrams, GetAnagrams(word, givenWords));
}

TEST(GetAnagrams, GiveTwoAnagrams_ReturnThem)
{
    const std::string word("word");
    const std::string anagram("rowd");

    String_vt expectedAnagrams({word, anagram});
    String_vt givenWords = expectedAnagrams;

    EXPECT_EQ(expectedAnagrams, GetAnagrams(word, givenWords));
}

