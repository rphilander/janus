#pragma once

#include <unordered_map>
#include <unordered_set>

#include <boost/asio.hpp>
#include <boost/bimap.hpp>

#include "atom.hpp"
#include "status.hpp"

namespace janus {

class HashStringPair
{
public:
  std::size_t operator()(std::pair<std::string, std::string>) const;
};

class Runtime : public RestOfWorld
{
public:
  // Thread-safe, asynchronous.
  void Ready(InterfacePtr);
  void AddAtom(std::string atom_type_name, std::string atom_name);
  void AddConnection(std::string from_atom, std::string from_iface, std::string to_atom, std::string to_iface);
  void Write(std::string atom, std::string iface, ValuePtr);

  // Thread-safe, synchronous.
  boost::asio::io_service& GetIoService();

  // Call on its own thread.
  void Run();

private:
  boost::asio::io_service io_service_;
  std::unordered_map<InterfacePtr, bool> interface_readiness_;
  boost::bimap<InterfacePtr, InterfacePtr> connections_;
  std::unordered_set<AtomPtr> atoms_;
  std::unordered_map<std::pair<std::string, std::string>, InterfacePtr, HashStringPair> interfaces_;

  // callbacks
  void HandleReady(InterfacePtr);
  void HandleAddAtom(std::string atom_type_name, std::string atom_name);
  void HandleAddConnection(std::string from_atom, std::string from_iface, std::string to_atom, std::string to_iface);
  void HandleWrite(std::string atom, std::string iface, ValuePtr);

  // helpers
  void MoveValue(InterfacePtr from, InterfacePtr to);
};

} // namespace janus
