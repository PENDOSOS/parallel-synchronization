#include "../src/parallel-executor/helpers.h"

#include <gtest/gtest.h>

#include <string>
#include <algorithm>

TEST(RandomNumberTest, GeneratesNumberInRange) 
{
  int start = 10;
  int end = 20;
  int num = randomNumber(start, end);
  EXPECT_GE(num, start);
  EXPECT_LE(num, end);
}

TEST(RandomNumberTest, GeneratesDifferentNumbers) 
{
  int start = 1;
  int end = 500;
  int num1 = randomNumber(start, end);
  int num2 = randomNumber(start, end);
  EXPECT_NE(num1, num2);
}

TEST(RandomStringTest, GeneratesStringOfCorrectLength) 
{
  std::size_t length = 10;
  std::string str = randomString(length);
  EXPECT_EQ(str.size(), length);
}

TEST(RandomStringTest, GeneratesStringWithValidCharacters) 
{
  std::size_t length = 10;
  std::string str = randomString(length);
  const std::string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  for (char c : str) 
  {
    EXPECT_TRUE(characters.find(c) != std::string::npos);
  }
}

TEST(RandomStringTest, GeneratesDifferentStrings) 
{
  std::size_t length = 10;
  std::string str1 = randomString(length);
  std::string str2 = randomString(length);
  EXPECT_NE(str1, str2);
}
