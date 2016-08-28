#pragma once

#include <string>

namespace janus {

using InterfaceId = int;
using Value = std::string;

class Reader
{
public:
  virtual std::string ReadInterfaceName(InterfaceId) const = 0;
  virtual bool ReadInterfaceReady(InterfaceId) const = 0;
  virtual Value Read(InterfaceId) = 0;
};

class ReadInterface
{
public:
  ReadInterface(Reader *, InterfaceId);
  std::string name() const;
  bool ready() const;
  Value Read();
  // For hashing.
  bool operator==(const ReadInterface&) const;
  friend std::hash<ReadInterface>;
private:
  Reader *reader_;
  InterfaceId id_;
};

class Writer
{
public:
  virtual std::string WriteInterfaceName(InterfaceId) const = 0;
  virtual bool WriteInterfaceReady(InterfaceId) const = 0;
  virtual void Write(InterfaceId, Value) = 0;
};

class WriteInterface
{
public:
  WriteInterface(Writer *, InterfaceId);
  std::string name() const;
  bool ready() const;
  void Write(Value);
  // For hashing.
  bool operator==(const WriteInterface&) const;
  friend std::hash<WriteInterface>;
private:
  Writer *writer_;
  InterfaceId id_;
};

} // namespace janus


namespace std {

template <>
struct std::hash<janus::ReadInterface>
{
  std::size_t operator()(const janus::ReadInterface &) const;
};

template <>
struct std::hash<janus::WriteInterface>
{
  std::size_t operator()(const janus::WriteInterface &) const;
};

} // namespace std
