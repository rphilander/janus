#include "writeline_atom.hpp"

#include <iostream>

namespace janus {

WriteInterface WritelineAtom::GetWriteInterface()
{
  return WriteInterface(this, 0);
}

std::string WritelineAtom::WriteInterfaceName(InterfaceId) const
{
  return "Writeline";
}

bool WritelineAtom::WriteInterfaceReady(InterfaceId) const
{
  return true;
}

void WritelineAtom::Write(InterfaceId, Value value)
{
  std::cout << value << std::endl;
}

} // namespace janus
