#pragma once

#include <memory>

#include <boost/asio.hpp>

#include "atom.hpp"
#include "value.hpp"

namespace janus {

class Runtime;

class ReadlineAtom : public Atom
{
public:
  ReadlineAtom();
  void Initialize(RestOfWorld*);
  void GetInterfaces(std::vector<InterfacePtr>&) const;

private:
  Status Read(InterfaceId, ValuePtr&);
  Status Write(InterfaceId, ValuePtr);

  // For boost::asio callbacks.
  void HandleReadInput(const boost::system::error_code& error, std::size_t length);

  RestOfWorld *row_;
  InterfacePtr input_;
  InterfacePtr output_;
  std::string line_;

  std::unique_ptr<boost::asio::posix::stream_descriptor> stdin_stream_;
  boost::asio::streambuf input_buffer_;
};

} // namespace janus
