#include "gtest/gtest.h"
#include "../src/parallel-executor/EventQueue.h"

#include <memory>
#include <chrono>

class EventQueueTest : public ::testing::Test 
{
protected:
  EventQueue queue;
};

TEST_F(EventQueueTest, PushAndPop) 
{
  auto event = std::make_shared<const Event>();
  queue.push(event);
  auto poppedEvent = queue.pop(std::chrono::seconds(0));
  EXPECT_EQ(event, poppedEvent);
}

TEST_F(EventQueueTest, PopEmptyQueue) 
{
  auto poppedEvent = queue.pop(std::chrono::seconds(1));
  EXPECT_EQ(nullptr, poppedEvent);
}

TEST_F(EventQueueTest, PopWithTimeout) 
{
  auto start = std::chrono::high_resolution_clock::now();
  auto poppedEvent = queue.pop(std::chrono::seconds(1));
  auto end = std::chrono::high_resolution_clock::now();
  auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(end - start);
  EXPECT_EQ(nullptr, poppedEvent);
  EXPECT_GE(elapsedTime.count(), 1);
}

TEST_F(EventQueueTest, MultiplePushAndPop) 
{
  auto event1 = std::make_shared<const Event>();
  auto event2 = std::make_shared<const Event>();
  queue.push(event1);
  queue.push(event2);
  auto poppedEvent1 = queue.pop(std::chrono::seconds(0));
  auto poppedEvent2 = queue.pop(std::chrono::seconds(0));
  EXPECT_EQ(event1, poppedEvent1);
  EXPECT_EQ(event2, poppedEvent2);
}