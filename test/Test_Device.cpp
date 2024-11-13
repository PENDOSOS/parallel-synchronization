#include "../src/parallel-executor/Hierarchy.h"

#include <gtest/gtest.h>

#include <memory>

TEST(DeviceATest, GetNameTest)
{
  std::shared_ptr<Device> device = std::make_shared<DeviceA>();
  ASSERT_EQ(device->getName(), "Device A");
}

TEST(DeviceBTest, GetNameTest)
{
  std::shared_ptr<Device> device = std::make_shared<DeviceB>();
  ASSERT_EQ(device->getName(), "Device B");
}
