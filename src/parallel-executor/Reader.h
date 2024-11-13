#pragma once

#include "EventQueue.h"
#include "Hierarchy.h"

class Reader
{
public:
  Reader(std::shared_ptr<EventQueue> queue, std::shared_ptr<Device> deviceA, std::shared_ptr<Device> deviceB)
    : m_queue(queue), m_deviceA(deviceA), m_deviceB(deviceB) 
    {
      if (m_queue.get() == nullptr || m_deviceA.get() == nullptr || m_deviceB.get() == nullptr)
        throw std::runtime_error("nullptr received");
    }

  void run(size_t loopCountA, size_t loopCountB, size_t crushIndexA = SIZE_MAX, size_t crushIndexB = SIZE_MAX, size_t duration);
private:
  void read(std::shared_ptr<Device> device, std::chrono::seconds sleepDuration, size_t loopCount, size_t crushIndex);
private: 
  std::shared_ptr<EventQueue> m_queue;
  std::shared_ptr<Device> m_deviceA;
  std::shared_ptr<Device> m_deviceB;
};