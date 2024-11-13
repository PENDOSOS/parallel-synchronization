#pragma once

#include "includes.h"

#include <random>

int randomNumber(int start, int end)
{
  std::random_device randomDevice;
  std::mt19937 generator(randomDevice());
  std::uniform_int_distribution<> distribution(start, end);

  return distribution(generator);
}

std::string randomString(std::size_t length)
{
  const std::string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  std::string randomString;

  for (std::size_t i = 0; i < length; ++i)
  {
    randomString += characters[randomNumber(0, characters.size() - 1)];
  }

  return randomString;
}