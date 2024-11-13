#include "Reader.h"

void Reader::run(size_t duration, size_t loopCountA, size_t loopCountB, size_t crushIndexA, size_t crushIndexB)
{
  std::thread readA(&Reader::read, this, m_deviceA, std::chrono::seconds(1), loopCountA, crushIndexA);
  std::thread readB(&Reader::read, this, m_deviceB, std::chrono::seconds(5), loopCountB, crushIndexB);

  size_t activeDevice = 2;
  while (activeDevice > 0)
  {
    auto event = m_queue->pop(std::chrono::seconds(duration));
    if (event.get() != nullptr)
    {
      std::cout << event->toString() << '\n';

      if (dynamic_cast<const WorkDoneEvent*>(event.get()) != nullptr)
      {
        --activeDevice;
      }
    }
    else
    {
      --activeDevice;
    }
  }

  readA.join();
  readB.join();
}

void Reader::read(std::shared_ptr<Device> device, std::chrono::seconds sleepDuration, size_t loopCount, size_t crushIndex)
{
  try
  {
    std::shared_ptr<const Event> event;
    event = std::make_shared<StartedEvent>(device);
    m_queue->push(event);
    for (size_t i = 0; i < loopCount; ++i)
    {
      if (i == crushIndex)
      {
        return;
      }
      event = std::make_shared<DataEvent>(device);
      std::this_thread::sleep_for(sleepDuration);
      m_queue->push(event);
    }
    event = std::make_shared<WorkDoneEvent>(device);
    m_queue->push(event);
  }
  catch(std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
  catch(...)
  {
    std::cerr << "Caught unknown exception\n";
  }
}

/*
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
}*/