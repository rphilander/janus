#include "interface_manager.hpp"

namespace janus {



namespace {

template <class I>
class AddInterfaceUpdate : public InterfaceManagerUpdate
{
public:
  AddInterfaceUpdate(I iface) : iface_(iface) {}
  void operator()(InterfaceManager &manager)
  {
    manager.AddInterface(iface_);
  }
private:
  I iface_;
};

template <class I>
class InterfaceReadyUpdate : public InterfaceManagerUpdate
{
public:
  InterfaceReadyUpdate(I iface) : iface_(iface) {}
  void operator()(InterfaceManager &manager)
  {
    manager.InterfaceReady(iface_);
  }
private:
  I iface_;
};

template <class I>
class InterfaceNotReadyUpdate : public InterfaceManagerUpdate
{
public:
  InterfaceNotReadyUpdate(I iface) : iface_(iface) {}
  void operator()(InterfaceManager &manager)
  {
    manager.InterfaceNotReady(iface_);
  }
private:
  I iface_;
};

} // namespace (anonymous)

InterfaceManagerUpdater::InterfaceManagerUpdater(InterfaceManagerUpdateSink *sink) : sink_(sink) {}

void InterfaceManagerUpdater::AddInterface(ReadInterface iface)
{
  sink_->push(new AddInterfaceUpdate<ReadInterface>(iface));
}

void InterfaceManagerUpdater::InterfaceReady(ReadInterface iface)
{
  sink_->push(new InterfaceReadyUpdate<ReadInterface>(iface));
}

void InterfaceManagerUpdater::InterfaceNotReady(ReadInterface iface)
{
  sink_->push(new InterfaceNotReadyUpdate<ReadInterface>(iface));
}

void InterfaceManagerUpdater::AddInterface(WriteInterface iface)
{
  sink_->push(new AddInterfaceUpdate<WriteInterface>(iface));
}

void InterfaceManagerUpdater::InterfaceReady(WriteInterface iface)
{
  sink_->push(new InterfaceReadyUpdate<WriteInterface>(iface));
}

void InterfaceManagerUpdater::InterfaceNotReady(WriteInterface iface)
{
  sink_->push(new InterfaceNotReadyUpdate<WriteInterface>(iface));
}

} // namespace janus
