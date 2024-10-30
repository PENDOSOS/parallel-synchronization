#include "EventQueue.h"

void EventQueue::push(const std::shared_ptr<const Event>& event)
{
    std::mutex mtx;
    mtx.lock();
    this->queue.push(event);
    mtx.unlock();
}

std::shared_ptr<const Event> EventQueue::pop(const std::chrono::seconds& duration)
{
    std::mutex mtx;
    mtx.lock();
    std::shared_ptr<const Event> event = this->queue.front();
    this->queue.pop();
    mtx.unlock();
    return event;
}