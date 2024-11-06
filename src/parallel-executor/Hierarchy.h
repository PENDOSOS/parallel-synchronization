#pragma once

#include "includes.h"

class Event
{
public:
  //Event() = default;
  virtual std::string toString() const = 0;
};

class Device
{
public:
  //Device() = default;

  virtual std::string getName() const;
  virtual std::string getDataAsString() = 0;
};

class DeviceA : public Device
{
public:
  //DeviceA() = default;

  std::string getDataAsString() override;
  std::string getName() const override { return "Device A"; }
};

class DeviceB : public Device
{
public:
  std::string getDataAsString() override;
  std::string getName() const override { return "Device B"; }
};

class DeviceEvent : public Event
{
public:
  DeviceEvent(std::shared_ptr<Device> device) : device(device) {}
protected:
  std::shared_ptr<Device> device;
};

class DataEvent : public DeviceEvent
{
public:
  DataEvent(std::shared_ptr<Device> device) : DeviceEvent(device) {}

  std::string toString() const override
  {
    return "Data from " + this->device->getName() + " is: " + this->device->getDataAsString();
  }
};

class WorkDoneEvent : public DeviceEvent
{
public:
  WorkDoneEvent(std::shared_ptr<Device> device) : DeviceEvent(device) {}

  std::string toString() const override 
  {
    return "Work with " + this->device->getName() + " done!"; 
  }
};

class StartedEvent : public DeviceEvent
{
public:
  StartedEvent(std::shared_ptr<Device> device) : DeviceEvent(device) {}

  std::string toString() const override
  {
    return "Started work with " + this->device->getName();
  }
};