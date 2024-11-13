#include "../src/parallel-executor/Hierarchy.h"

#include <gtest/gtest.h>

#include <memory>

TEST(Events, StartedEventTest)
{
  std::shared_ptr<Device> A = std::make_shared<DeviceA>();
  std::shared_ptr<Device> B = std::make_shared<DeviceB>();

  EXPECT_EQ(StartedEvent(std::move(A)).toString(), "Started work with Device A");
  EXPECT_EQ(StartedEvent(std::move(B)).toString(), "Started work with Device B");
}

TEST(Events, DataEventTest)
{
  std::shared_ptr<Device> A = std::make_shared<DeviceA>();
  std::shared_ptr<Device> B = std::make_shared<DeviceB>();

  std::string stringA = DataEvent(std::move(A)).toString();
  std::string stringB = DataEvent(std::move(B)).toString();

  std::string headA = "Data from Device A is: ";
  std::string headB = "Data from Device B is: ";

  EXPECT_TRUE(stringA.substr(headA.size()).size() <= 500);
  EXPECT_TRUE(stringB.substr(headB.size()).size() <= 12);
  EXPECT_TRUE(stringB.substr(headB.size()).size() >= 6);
}

TEST(Events, WorkDoneEventTest)
{
  std::shared_ptr<Device> A = std::make_shared<DeviceA>();
  std::shared_ptr<Device> B = std::make_shared<DeviceB>();

  EXPECT_EQ(WorkDoneEvent(std::move(A)).toString(), "Work with Device A done!");
  EXPECT_EQ(WorkDoneEvent(std::move(B)).toString(), "Work with Device B done!");
}