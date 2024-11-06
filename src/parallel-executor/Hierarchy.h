#pragma once

#include "includes.h"

class Event
{
public:
  virtual std::string toString() = 0;
};

class Device
{
public:
  virtual std::string getName();
  virtual std::string getDataAsString() = 0;
};

class DeviceA : public Device
{
public:
  std::string getDataAsString() override;
  std::string getName() override { return "Device A"; }
};

class DeviceB : public Device
{
public:
  std::string getDataAsString() override;
  std::string getName() override { return "Device B"; }
};

class DeviceEvent : public Event
{
public:
  DeviceEvent(std::shared_ptr<Device> device) : device(device) {}
private:
  std::shared_ptr<Device> device;
};

class DataEvent : public DeviceEvent
{
public:
  std::string toString() override
  {
    return "Reading data from ";
  }
};

class WorkDoneEvent : public DeviceEvent
{
public:
  std::string toString() override 
  {
    //std::string deviceName = this->device->getName();
    return "Work done!"; 
  }
};

class StartedEvent : public DeviceEvent
{
public:
  std::string toString() override
  {
    return "Started work...";
  }
};