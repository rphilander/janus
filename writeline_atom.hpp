#pragma once

#include "interface.hpp"

namespace janus {

class WritelineAtom : public Writer
{
public:
  WriteInterface GetWriteInterface();
  std::string WriteInterfaceName(InterfaceId) const;
  bool WriteInterfaceReady(InterfaceId) const;
  void Write(InterfaceId, Value);
};

} // namespace janus
