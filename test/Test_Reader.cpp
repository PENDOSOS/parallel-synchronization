#include "../src/parallel-executor/EventQueue.h"
#include "../src/parallel-executor/Hierarchy.h"
#include "../src/parallel-executor/Reader.h"

#include <gtest/gtest.h>

#include <memory>

namespace
{
  std::string captureOutput(std::function<void()> func)
  {
    std::stringstream buffer;
    using BasicStreambuf = std::basic_streambuf<char, std::char_traits<char>>;
    std::unique_ptr<BasicStreambuf> old {std::cout.rdbuf(buffer.rdbuf())};
    func();
    std::cout.rdbuf(old.release());
    return buffer.str();
  }
}

TEST(Reader, RunDefaultTest)
{
  std::shared_ptr<EventQueue> queue = std::make_shared<EventQueue>();
  std::shared_ptr<Device> deviceA = std::make_shared<DeviceA>();
  std::shared_ptr<Device> deviceB = std::make_shared<DeviceB>();

  Reader reader(queue, deviceA, deviceB);

  std::string stream = captureOutput([&]() { reader.run(1, 1); });

  EXPECT_TRUE(stream.find("Started work with Device A") != std::string::npos);
  EXPECT_TRUE(stream.find("Data from Device A is: ") != std::string::npos);
  EXPECT_TRUE(stream.find("Work with Device A done!") == std::string::npos);

  EXPECT_TRUE(stream.find("Started work with Device B") != std::string::npos);
  EXPECT_TRUE(stream.find("Data from Device B is: ") != std::string::npos);
  EXPECT_TRUE(stream.find("Work with Device B done!") == std::string::npos);
}

TEST(Reader, RunCrushATest)
{
  std::shared_ptr<EventQueue> queue = std::make_shared<EventQueue>();
  std::shared_ptr<Device> deviceA = std::make_shared<DeviceA>();
  std::shared_ptr<Device> deviceB = std::make_shared<DeviceB>();

  Reader reader(queue, deviceA, deviceB);

  std::string stream = captureOutput([&]() { reader.run(2, 1, 1); });

  EXPECT_TRUE(stream.find("Started work with Device A") != std::string::npos);
  EXPECT_TRUE(stream.find("Data from Device A is: ") != std::string::npos);
  EXPECT_TRUE(stream.find("Work with Device A done!") == std::string::npos);

  EXPECT_TRUE(stream.find("Started work with Device B") != std::string::npos);
  EXPECT_TRUE(stream.find("Data from Device B is: ") != std::string::npos);
  EXPECT_TRUE(stream.find("Work with Device B done!") == std::string::npos);
}

TEST(Reader, RunCrushBTest)
{
  std::shared_ptr<EventQueue> queue = std::make_shared<EventQueue>();
  std::shared_ptr<Device> deviceA = std::make_shared<DeviceA>();
  std::shared_ptr<Device> deviceB = std::make_shared<DeviceB>();

  Reader reader(queue, deviceA, deviceB);

  std::string stream = captureOutput([&]() { reader.run(1, 2, 1, 1); });

  EXPECT_TRUE(stream.find("Started work with Device A") != std::string::npos);
  EXPECT_TRUE(stream.find("Data from Device A is: ") != std::string::npos);
  EXPECT_TRUE(stream.find("Work with Device A done!") == std::string::npos);

  EXPECT_TRUE(stream.find("Started work with Device B") != std::string::npos);
  EXPECT_TRUE(stream.find("Data from Device B is: ") != std::string::npos);
  EXPECT_TRUE(stream.find("Work with Device B done!") == std::string::npos);
}

TEST(Reader, RunCrushABTest)
{
  std::shared_ptr<EventQueue> queue = std::make_shared<EventQueue>();
  std::shared_ptr<Device> deviceA = std::make_shared<DeviceA>();
  std::shared_ptr<Device> deviceB = std::make_shared<DeviceB>();

  Reader reader(queue, deviceA, deviceB);

  std::string stream = captureOutput([&]() { reader.run(2, 2, 1, 1); });

  EXPECT_TRUE(stream.find("Started work with Device A") != std::string::npos);
  EXPECT_TRUE(stream.find("Data from Device A is: ") != std::string::npos);
  EXPECT_TRUE(stream.find("Work with Device A done!") == std::string::npos);

  EXPECT_TRUE(stream.find("Started work with Device B") != std::string::npos);
  EXPECT_TRUE(stream.find("Data from Device B is: ") != std::string::npos);
  EXPECT_TRUE(stream.find("Work with Device B done!") == std::string::npos);
}

TEST(Reader, InitWithEmptyQueueTest)
{
  std::shared_ptr<Device> deviceA = std::make_shared<DeviceA>();
  std::shared_ptr<Device> deviceB = std::make_shared<DeviceB>();

  EXPECT_THROW(
    Reader(nullptr, std::move(deviceA), std::move(deviceB)),
    std::runtime_error
  );
}

TEST(Parser, InitWithEmptyDevicesTest)
{
  std::shared_ptr<EventQueue> queue = std::make_shared<EventQueue>();
  std::shared_ptr<Device> deviceA = std::make_shared<DeviceA>();
  std::shared_ptr<Device> deviceB = std::make_shared<DeviceB>();

  EXPECT_THROW(
    Reader(queue, nullptr, std::move(deviceB)),
    std::runtime_error
  );

  EXPECT_THROW(
    Reader(queue, std::move(deviceA), nullptr),
    std::runtime_error
  );
}