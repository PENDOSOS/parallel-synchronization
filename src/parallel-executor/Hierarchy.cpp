#include "Hierarchy.h"

std::string DeviceB::getDataAsString()
{
  std::string returnData = "";
  for (auto elem: this->data)
  {
    returnData += std::to_string(elem) + " ";
  }
  return returnData;
}