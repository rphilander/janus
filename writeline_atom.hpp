#pragma once

#include <memory>
#include <vector>

#include <boost/asio.hpp>

#include "atom.hpp"
#include "value.hpp"

namespace janus {

class Runtime;

class WritelineAtom : public Atom
{
public:
  WritelineAtom();
  void Initialize(RestOfWorld*);
  void GetInterfaces(std::vector<InterfacePtr>&) const;

private:
  Status Read(InterfaceId, ValuePtr&);
  Status Write(InterfaceId, ValuePtr);

  // For boost::asio callbacks.
  void HandleWriteComplete(const boost::system::error_code& error, std::size_t length);

  RestOfWorld *row_;
  InterfacePtr input_, output_;

  std::unique_ptr<boost::asio::posix::stream_descriptor> stdout_stream_;
  std::vector<char> output_buffer_;
};

} // namespace janus
