#pragma once

#include <list>
#include <unordered_set>

#include "interface.hpp"
#include "interface_manager.hpp"

namespace janus {

  class SimpleInterfaceManager : public InterfaceManager
  {
  public:

    void AddInterface(ReadInterface);
    void InterfaceReady(ReadInterface);
    void InterfaceNotReady(ReadInterface);
    void AddInterface(WriteInterface);
    void InterfaceReady(WriteInterface);
    void InterfaceNotReady(WriteInterface);

    void AddConnection(ReadInterface, WriteInterface);

    void propagate();

  private:
    std::unordered_set<ReadInterface> ready_readers_, notready_readers_;
    std::unordered_set<WriteInterface> ready_writers_, notready_writers_;

    struct Connection
    {
      ReadInterface read_iface;
      WriteInterface write_iface;
    };
    std::list<Connection> connections_;

  };


} // namespace janus