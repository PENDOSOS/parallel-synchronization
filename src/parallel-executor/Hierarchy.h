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
  virtual std::string getDataAsString();
private:
  std::string name;
  int data;
};

class DeviceEvent
{
public:
  DeviceEvent(std::shared_ptr<Device> device);
private:
  std::shared_ptr<Device> device;
};

class DataEvent : public Event
{
public:
  std::string toString() override;
};

class WorkDoneEvent : public Event
{
public:
  std::string toString() override;
};

class StartedEvent : public Event
{
public:
  std::string toString() override;
};