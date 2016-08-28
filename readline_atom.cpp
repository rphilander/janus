#include "readline_atom.hpp"
#include "stringutils.hpp"

#include <string>

namespace janus {

ReadInterface ReadlineAtom::GetReadInterface()
{
  return ReadInterface(this, 0);
}

std::string ReadlineAtom::ReadInterfaceName(InterfaceId) const 
{
  return "Readline";
}

bool ReadlineAtom::ReadInterfaceReady(InterfaceId) const
{
  return true;
}

Value ReadlineAtom::Read(InterfaceId)
{
  std::string line;
  Status status = readline("janus> ", line);
  if (not status)
  {
    line = status.get_message();
  }
  return line;
}

} // namespace janus
