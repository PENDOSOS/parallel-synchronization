#pragma once

#include "../parallel-executor/includes.h"
#include "../parallel-executor/Hierarchy.h"

class EventQueue
{
public:
  // Положить сообщение в очередь
  void push(const std::shared_ptr<const Event>& event);

  // Удалить сообщение из очереди и вернуть его. По истечении duration, если очерель пуста, вернуть пустой указатель.
  std::shared_ptr<const Event> pop(const std::chrono::seconds& duration);
private:
  std::queue<std::shared_ptr<const Event>> m_queue;
  std::mutex m_mtx;
  std::condition_variable m_cv;
};
