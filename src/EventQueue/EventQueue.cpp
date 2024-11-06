#include "EventQueue.h"

void EventQueue::push(const std::shared_ptr<const Event>& event)
{
  std::lock_guard<std::mutex> lk(this->mtx);
  this->queue.push(event);
  cv.notify_one();
}

std::shared_ptr<const Event> EventQueue::pop(const std::chrono::seconds& duration)
{
  std::unique_lock<std::mutex> lk(this->mtx);
  cv.wait(lk, [this] { return !this->queue.empty(); });
  auto start = std::chrono::high_resolution_clock::now();
  auto end = std::chrono::high_resolution_clock::now();
  auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(end - start);
  while (this->queue.empty() && elapsedTime.count() < duration.count())
  {
    end = std::chrono::high_resolution_clock::now();
    elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(end - start);
  }
  if (!this->queue.empty())
  {
    std::shared_ptr<const Event> event = this->queue.front();
    this->queue.pop();
    mtx.unlock();
    return event;
  }
  return nullptr;
}