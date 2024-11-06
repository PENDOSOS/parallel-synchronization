#include "EventQueue/EventQueue.h"
#include "parallel-executor/ReadLibrary.h"
#include "parallel-executor/Hierarchy.h"
#include "parallel-executor/ThreadTasks.h"
#include "parallel-executor/includes.h"

#include <iostream>

int main()
{
  std::shared_ptr<EventQueue> eventQueue = std::make_shared<EventQueue>();

  std::shared_ptr<Device> deviceA = std::make_shared<DeviceA>();
  std::shared_ptr<Device> deviceB = std::make_shared<DeviceB>();

  //std::function<void(const std::shared_ptr<EventQueue>&, const std::shared_ptr<Device>&)> readFromA = readA;
  //std::function<void(const std::shared_ptr<EventQueue>&, const std::shared_ptr<Device>&)> readFromB = readB;

  std::thread threadA(readA, eventQueue, deviceA);
  std::thread threadB(readB, eventQueue, deviceB);

  while (true)
  {
    auto event = eventQueue->pop(std::chrono::seconds(0));
    if (event)
      std::cout << event->toString() << std::endl;
    else
    {
      std::cout << "Work with devices ended" << std::endl;
      break;
    }
  }

  return 0;
}