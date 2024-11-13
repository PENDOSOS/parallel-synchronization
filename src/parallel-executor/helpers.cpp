#include "helpers.h"

size_t randomNumber(size_t start, size_t end)
{
  std::random_device randomDevice;
  std::mt19937 generator(randomDevice());
  std::uniform_int_distribution<> distribution(start, end);

  return distribution(generator);
}

std::string randomString(size_t length)
{
  const std::string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  std::string randomString;

  for (size_t i = 0; i < length; ++i)
  {
    randomString += characters[randomNumber(0, characters.size() - 1)];
  }

  return randomString;
}
