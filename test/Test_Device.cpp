#include "gtest/gtest.h"
#include "../src/parallel-executor/Hierarchy.h"

#include <string>
#include <algorithm>

TEST(DeviceATest, GetName) 
{
  DeviceA device;
  EXPECT_EQ(device.getName(), "Device A");
}

TEST(DeviceATest, GetDataAsString) 
{
  DeviceA device;
  std::string data = device.getDataAsString();
  EXPECT_GE(data.size(), 0);
  EXPECT_LE(data.size(), 500);
  const std::string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  for (char c : data) 
  {
    EXPECT_TRUE(characters.find(c) != std::string::npos);
  }
}

TEST(DeviceBTest, GetName) 
{
  DeviceB device;
  EXPECT_EQ(device.getName(), "Device B");
}

TEST(DeviceBTest, GetDataAsString) 
{
  DeviceB device;
  std::string data = device.getDataAsString();
  int count = std::count(data.begin(), data.end(), ' ');
  EXPECT_EQ(count, 2);
  std::stringstream ss(data);
  int num;
  while (ss >> num) 
  {
    EXPECT_GE(num, 0);
    EXPECT_LE(num, 198);
  }
}
