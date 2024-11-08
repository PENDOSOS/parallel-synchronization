#pragma once

#include "includes.h"
#include "Hierarchy.h"
#include "EventQueue.h"

void readA(const std::shared_ptr<EventQueue>& queue, const std::shared_ptr<Device>& device, int callCount)
{
  int elapsedCalls = 0;
  if (callCount == -1) // == -1 - количество вызовов функции не ограничено
    elapsedCalls = -2;
  while (elapsedCalls < callCount)
  {
    auto start = std::chrono::high_resolution_clock::now();
    
    queue->push(std::make_shared<const StartedEvent>(device));
    queue->push(std::make_shared<const DataEvent>(device));
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);

    while (duration.count() < 5)
    {
      end = std::chrono::high_resolution_clock::now();
      duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    }

    queue->push(std::make_shared<const WorkDoneEvent>(device));
    if (callCount != -1)
      elapsedCalls++;
  }
}

void readB(const std::shared_ptr<EventQueue>& queue, const std::shared_ptr<Device>& device, int callCount)
{
  int elapsedCalls = 0;
  if (callCount == -1) // == -1 - количество вызовов функции не ограничено
    elapsedCalls = -2;
  while (elapsedCalls < callCount)
  {
    auto start = std::chrono::high_resolution_clock::now();

    queue->push(std::make_shared<const StartedEvent>(device));
    queue->push(std::make_shared<const DataEvent>(device));
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);

    while (duration.count() < 1)
    {
      end = std::chrono::high_resolution_clock::now();
      duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    }

    queue->push(std::make_shared<const WorkDoneEvent>(device));
    if (callCount != -1)
      elapsedCalls++;
  }
}