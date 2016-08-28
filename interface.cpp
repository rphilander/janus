#include "hash_combine.hpp"
#include "interface.hpp"

namespace janus {

ReadInterface::ReadInterface(Reader *reader, InterfaceId id) : 
  reader_(reader),
  id_(id)
{
}

std::string ReadInterface::name() const
{
  return reader_->ReadInterfaceName(id_);
}

bool ReadInterface::ready() const
{
  return reader_->ReadInterfaceReady(id_);
}

Value ReadInterface::Read()
{
  return reader_->Read(id_);
}

bool ReadInterface::operator==(const ReadInterface &rhs) const
{
  return (reader_ == rhs.reader_ and id_ == rhs.id_);
}



WriteInterface::WriteInterface(Writer *writer, InterfaceId id) :
  writer_(writer),
  id_(id)
{
}

std::string WriteInterface::name() const
{
  return writer_->WriteInterfaceName(id_);
}

bool WriteInterface::ready() const
{
  return writer_->WriteInterfaceReady(id_);
}

void WriteInterface::Write(Value value)
{
  writer_->Write(id_, value);
}

bool WriteInterface::operator==(const WriteInterface &rhs) const
{
  return (writer_ == rhs.writer_ and id_ == rhs.id_);
}

} // namespace janus


namespace std {

std::size_t std::hash<janus::ReadInterface>::operator()(const janus::ReadInterface &iface) const
{
  std::size_t seed = 0;
  hash_combine(seed, iface.reader_);
  hash_combine(seed, iface.id_);
  return seed;
}

std::size_t std::hash<janus::WriteInterface>::operator()(const janus::WriteInterface &iface) const
{
  std::size_t seed = 0;
  hash_combine(seed, iface.writer_);
  hash_combine(seed, iface.id_);
  return seed;
}

} // namespace std
