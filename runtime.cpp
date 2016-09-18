#include "runtime.hpp"

#include <iostream>

#include <boost/bind.hpp>
#include <boost/functional/hash.hpp>

#include "atom.hpp"
#include "readline_atom.hpp"
#include "writeline_atom.hpp"

namespace janus {

std::size_t HashStringPair::operator()(std::pair<std::string, std::string> p) const
{
  std::size_t seed = 0;
  boost::hash_combine(seed, p.first);
  boost::hash_combine(seed, p.second);
  return seed;
}


boost::asio::io_service &Runtime::GetIoService()
{
  return io_service_;
}

void Runtime::Run()
{
  io_service_.run();
}

void Runtime::Ready(InterfacePtr iface)
{
  io_service_.post(boost::bind(&Runtime::HandleReady, this, iface));
}

void Runtime::AddAtom(std::string atom_type_name, std::string atom_name)
{
  io_service_.post(boost::bind(&Runtime::HandleAddAtom, this, atom_type_name, atom_name));
}

void Runtime::AddConnection(std::string from_atom, std::string from_iface, std::string to_atom, std::string to_iface)
{
  io_service_.post(boost::bind(&Runtime::HandleAddConnection, this, from_atom, from_iface, to_atom, to_iface));
}

void Runtime::Write(std::string atom, std::string iface, ValuePtr value)
{
  io_service_.post(boost::bind(&Runtime::HandleWrite, this, atom, iface, value));
}

void Runtime::HandleReady(InterfacePtr iface)
{
  interface_readiness_[iface] = true;
  if (iface->GetInterfaceType() == InterfaceType::OUTPUT)
  {
    InterfacePtr to = connections_.left.at(iface);
    if (interface_readiness_.at(to))
    {
      MoveValue(iface, to);
    }
  }
  else
  {
    InterfacePtr from = connections_.right.at(iface);
    if (interface_readiness_.at(from))
    {
      MoveValue(from, iface);
    }
  }
}

void Runtime::HandleAddAtom(std::string atom_type_name, std::string atom_name)
{
  AtomPtr atom;
  if ("Readline" == atom_type_name)
  {
    atom.reset(new ReadlineAtom());
  }
  else if ("Writeline" == atom_type_name)
  {
    atom.reset(new WritelineAtom());
  }
  else
  {
    // Unrecognized atom name.
    assert(0);
  }
  atom->Initialize(this);
  atoms_.insert(atom);
  std::vector<InterfacePtr> interfaces;
  atom->GetInterfaces(interfaces);
  for (InterfacePtr iface : interfaces)
  {
    interfaces_.insert( std::make_pair( std::make_pair(atom_name, iface->GetName()), iface) );
    interface_readiness_[iface] = false;
  }
}

void Runtime::HandleAddConnection(std::string from_atom, std::string from_iface,
                                  std::string to_atom, std::string to_iface)
{
  InterfacePtr from = interfaces_.at(std::make_pair(from_atom, from_iface));
  InterfacePtr to = interfaces_.at(std::make_pair(to_atom, to_iface));
  connections_.left.insert(std::make_pair(from, to));
  if (interface_readiness_.at(from) and interface_readiness_.at(to))
  {
    MoveValue(from, to);
  }
}

void Runtime::HandleWrite(std::string atom, std::string iface, ValuePtr value)
{
  interfaces_.at(std::make_pair(atom, iface))->Write(value);
}

void Runtime::MoveValue(InterfacePtr from, InterfacePtr to)
{
  ValuePtr value;
  from->Read(value);
  to->Write(value);
  interface_readiness_[from] = false;
  interface_readiness_[to] = false;
}

} // namespace janus
