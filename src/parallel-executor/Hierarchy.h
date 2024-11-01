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
  std::string getDataAsString() override { return this->data; }
  std::string getName() override { return this->name; }
private:
  std::string name = "Device A";
  std::string data;
};

class DeviceB : public Device
{
public:
  std::string getDataAsString() override;
  std::string getName() override { return this->name; }
private:
  std::string name = "Device B";
  std::vector<int> data;
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