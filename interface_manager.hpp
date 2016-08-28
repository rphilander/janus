#pragma once

#include "interface.hpp"
#include "synchronized_queue.hpp"

namespace janus {

class InterfaceManager
{
public:
  virtual void AddInterface(ReadInterface) = 0;
  virtual void InterfaceReady(ReadInterface) = 0;
  virtual void InterfaceNotReady(ReadInterface) = 0;
  virtual void AddInterface(WriteInterface) = 0;
  virtual void InterfaceReady(WriteInterface) = 0;
  virtual void InterfaceNotReady(WriteInterface) = 0;
};

class InterfaceManagerUpdate
{
public:
  virtual void operator()(InterfaceManager&) = 0;
};

using InterfaceManagerUpdateSink = SynchronizedQueue<InterfaceManagerUpdate *>;

class InterfaceManagerUpdater
{
public:
  InterfaceManagerUpdater(InterfaceManagerUpdateSink *);

  void AddInterface(ReadInterface);
  void InterfaceReady(ReadInterface);
  void InterfaceNotReady(ReadInterface);

  void AddInterface(WriteInterface);
  void InterfaceReady(WriteInterface);
  void InterfaceNotReady(WriteInterface);

private:
  InterfaceManagerUpdateSink *sink_;
};

} // namepace janus