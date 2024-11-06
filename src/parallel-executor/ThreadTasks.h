#pragma once

#include "ReadLibrary.h"

void taskForThread(std::function<void(const std::shared_ptr<EventQueue>&, const std::shared_ptr<Device>&)> readFunc, const std::shared_ptr<EventQueue>& queue, const std::shared_ptr<Device>& device)
{
  readFunc(queue, device);
  while (true)
  {
    auto event = queue->pop(std::chrono::seconds(10));
    std::cout << event->toString() << std::endl;
  }
}