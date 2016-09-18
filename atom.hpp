#pragma once

#include <cassert>
#include <memory>
#include <string>

#include <boost/asio.hpp>

#include "status.hpp"
#include "value.hpp"

namespace janus {

class Atom;
typedef std::shared_ptr<Atom> AtomPtr;

struct Schema;
typedef std::shared_ptr<Schema> SchemaPtr;


class InterfaceId
{
public:
  explicit InterfaceId(int n) : n_(n) {}
  InterfaceId(const InterfaceId& iface) : n_(iface.n_) {}
  InterfaceId& operator=(const InterfaceId& iface) { n_ = iface.n_; return *this; }
  bool operator==(const InterfaceId& rhs) const { return n_ == rhs.n_; }
  bool operator!=(const InterfaceId& rhs) const { return n_ != rhs.n_; }
private:
  int n_;
};

enum class InterfaceType { INPUT, OUTPUT };

class Interface
{
public:
  Interface(AtomPtr atom,
            InterfaceId id,
            std::string name,
            InterfaceType interface_type,
            SchemaPtr default_expectations)
  : atom_(atom),
    id_(id),
    name_(name),
    interface_type_(interface_type),
    default_expectations_(default_expectations)
{
}

  AtomPtr GetAtom() { return atom_; }
  InterfaceType GetInterfaceType() const { return interface_type_; }
  std::string GetName() const { return name_; }
  SchemaPtr GetDefaultExpectation() const { return default_expectations_; }

  Status Read(ValuePtr& value);
  Status Write(ValuePtr value);

private:
  AtomPtr atom_;
  InterfaceId id_;
  std::string name_;
  InterfaceType interface_type_;
  SchemaPtr default_expectations_;
};

typedef std::shared_ptr<Interface> InterfacePtr;

class RestOfWorld
{
public:
  virtual void Ready(InterfacePtr) = 0;
  virtual boost::asio::io_service& GetIoService() = 0;
};

class Atom : public std::enable_shared_from_this<Atom>
{
public:
  virtual void Initialize(RestOfWorld*) = 0;
  virtual void GetInterfaces(std::vector<InterfacePtr>&) const = 0;
  friend class Interface;
private:
  virtual Status Read(InterfaceId, ValuePtr&);
  virtual Status Write(InterfaceId, ValuePtr);
};

} // namespace janus
