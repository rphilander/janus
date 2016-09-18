#include "atom.hpp"

#include <cassert>

namespace janus {



Status Interface::Read(ValuePtr& value)
{
  assert(interface_type_ == InterfaceType::OUTPUT);
  return atom_->Read(id_, value);
}

Status Interface::Write(ValuePtr value)
{
  assert(interface_type_ == InterfaceType::INPUT);
  return atom_->Write(id_, value);
}



Status Atom::Read(InterfaceId, ValuePtr&)
{
  assert(false);
}

Status Atom::Write(InterfaceId, ValuePtr)
{
  assert(false);
}

} // namespace janus
