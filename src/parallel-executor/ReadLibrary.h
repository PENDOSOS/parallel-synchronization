#include "includes.h"
#include "Hierarchy.h"
#include "../EventQueue/EventQueue.h"

std::string readA(std::shared_ptr<Device> device)
{
  std::shared_ptr<const Event> start = std::make_shared<const Event>(new StartedEvent());
}