#include "gtest/gtest.h"
#include "../src/parallel-executor/ReadLibrary.h"
#include "../src/parallel-executor/Hierarchy.h"
#include <memory>
#include <chrono>

class ReadFunctionsTest : public ::testing::Test 
{
protected:
  std::shared_ptr<EventQueue> queue;
  std::shared_ptr<Device> deviceA;
  std::shared_ptr<Device> deviceB;

  void SetUp() override 
  {
    queue = std::make_shared<EventQueue>();
    deviceA = std::make_shared<DeviceA>();
    deviceB = std::make_shared<DeviceB>();
  }
};

TEST_F(ReadFunctionsTest, ReadA_PositiveCallCount) 
{
  int callCount = 5;
  readA(queue, deviceA, callCount);
  int eventCount = 0;
  while (auto event = queue->pop(std::chrono::seconds(0))) 
  {
    eventCount++;
  }
  EXPECT_EQ(callCount * 3, eventCount);
}

TEST_F(ReadFunctionsTest, ReadA_InfiniteCallCount) 
{
  int callCount = -1;
  readA(queue, deviceA, callCount);
  auto start = std::chrono::high_resolution_clock::now();
  int eventCount = 0;
  while (auto event = queue->pop(std::chrono::seconds(1))) 
  {
    eventCount++;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    if (duration.count() > 10)
    {
      break;
    }
  }
  EXPECT_GT(eventCount, 0);
}

TEST_F(ReadFunctionsTest, ReadB_PositiveCallCount) 
{
  int callCount = 5;
  readB(queue, deviceB, callCount);
  int eventCount = 0;
  while (auto event = queue->pop(std::chrono::seconds(0))) 
  {
    eventCount++;
  }
  EXPECT_EQ(callCount * 3, eventCount);
}

TEST_F(ReadFunctionsTest, ReadB_InfiniteCallCount) 
{
  int callCount = -1;
  readB(queue, deviceB, callCount);
  auto start = std::chrono::high_resolution_clock::now();
  int eventCount = 0;
  while (auto event = queue->pop(std::chrono::seconds(1))) 
  {
    eventCount++;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    if (duration.count() > 10) 
    {
      break;
    }
  }
  EXPECT_GT(eventCount, 0);
}
