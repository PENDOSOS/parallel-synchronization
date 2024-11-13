#include "EventQueue.h"

void EventQueue::push(const std::shared_ptr<const Event>& event)
{
  std::lock_guard<std::mutex> lk(this->m_mtx);
  this->m_queue.push(event);
  m_cv.notify_one();
}

std::shared_ptr<const Event> EventQueue::pop(const std::chrono::seconds& duration)
{
  std::unique_lock<std::mutex> lock(m_mtx);
  if (m_queue.empty())
  {
    if (m_cv.wait_for(lock, duration) == std::cv_status::timeout)
    {
      return nullptr;
    }
  }

  if (!m_queue.empty())
  {
    std::shared_ptr<const Event> event = m_queue.front();
    m_queue.pop();
    return event;
  }

  return nullptr;
}