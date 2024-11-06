#include "EventQueue/EventQueue.h"
#include "parallel-executor/ReadLibrary.h"
#include "parallel-executor/Hierarchy.h"
#include "parallel-executor/includes.h"

#include <iostream>

int main(int argc, char* argv[]) // возможные аргументы: -readA, -readB, -duration
{
  std::shared_ptr<EventQueue> eventQueue = std::make_shared<EventQueue>();

  std::shared_ptr<Device> deviceA = std::make_shared<DeviceA>();
  std::shared_ptr<Device> deviceB = std::make_shared<DeviceB>();

  int callCountReadA = -1;
  int callCountReadB = -1;
  int duration = 0;
  
  if (argc > 1)
  {
    for (int i = 1; i < argc; i += 2)
    {
        if (argv[i] == "-readA")
          callCountReadA = std::stoi(argv[i + 1]);
        if (argv[i] == "-readB")
          callCountReadB = std::stoi(argv[i + 1]);
        if (argv[i] == "-duration")
          duration = std::stoi(argv[i + 1]);
    }
  }

  std::thread threadA(readA, eventQueue, deviceA, callCountReadA);
  std::thread threadB(readB, eventQueue, deviceB, callCountReadB);

  while (true)
  {
    auto event = eventQueue->pop(std::chrono::seconds(duration));
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