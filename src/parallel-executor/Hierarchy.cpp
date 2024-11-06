#include "Hierarchy.h"
#include "Helpers.h"

std::string DeviceA::getDataAsString()
{
  std::string returnData;
  returnData = randomString(randomNumber(0, 500));
  return returnData;
}

std::string DeviceB::getDataAsString()
{
  std::string returnData = "";
  for (int i = 0; i < 3; i++)
  {
    returnData += std::to_string(randomNumber(0, 198)) + " ";
  }
  return returnData;
}