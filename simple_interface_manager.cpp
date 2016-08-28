#include "simple_interface_manager.hpp"

namespace janus {

void SimpleInterfaceManager::AddInterface(ReadInterface iface)
{
  if (iface.ready())
  {
    ready_readers_.insert(iface);
  }
  else
  {
    notready_readers_.insert(iface);
  }
}

void SimpleInterfaceManager::InterfaceReady(ReadInterface iface)
{
  if (notready_readers_.count(iface) == 1)
  {
    notready_readers_.erase(iface);
    ready_readers_.insert(iface);
  }  
}

void SimpleInterfaceManager::InterfaceNotReady(ReadInterface iface)
{
  if (ready_readers_.count(iface) == 1)
  {
    ready_readers_.erase(iface);
    notready_readers_.insert(iface);
  }
}

void SimpleInterfaceManager::AddInterface(WriteInterface iface)
{
  if (iface.ready())
  {
    ready_writers_.insert(iface);
  }
  else
  {
    notready_writers_.insert(iface);
  }
}

void SimpleInterfaceManager::InterfaceReady(WriteInterface iface)
{
  if (notready_writers_.count(iface) == 1)
  {
    notready_writers_.erase(iface);
    ready_writers_.insert(iface);
  }
}

void SimpleInterfaceManager::InterfaceNotReady(WriteInterface iface)
{
  if (ready_writers_.count(iface) == 1)
  {
    ready_writers_.erase(iface);
    notready_writers_.insert(iface);
  }
}

void SimpleInterfaceManager::AddConnection(ReadInterface read_iface, WriteInterface write_iface)
{
  connections_.push_back({read_iface, write_iface});
}

void SimpleInterfaceManager::propagate()
{
  bool stop = false;
  while (not stop)
  {
    std::list<Connection> ready, notready;
    for (Connection connection : connections_)
    {
      if (connection.read_iface.ready() and connection.write_iface.ready())
      {
        connection.write_iface.Write(connection.read_iface.Read());
        ready.push_back(connection);
      }
      else
      {
        notready.push_back(connection);
      }
    }
    if (ready.empty())
    {
      stop = true;
    }
    connections_.clear();
    connections_.insert(connections_.begin(), notready.begin(), notready.end());
    connections_.insert(connections_.end(), ready.begin(), ready.end());
  }
}

} // namespace janus
