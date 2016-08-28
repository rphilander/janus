#pragma once

#include "interface.hpp"

namespace janus {

class ReadlineAtom : public Reader
{
public:
  ReadInterface GetReadInterface();
  std::string ReadInterfaceName(InterfaceId) const ;
  bool ReadInterfaceReady(InterfaceId) const;
  Value Read(InterfaceId);
};




} // namespace janus