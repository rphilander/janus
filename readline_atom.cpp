#include "readline_atom.hpp"

#include <boost/bind.hpp>

#include "runtime.hpp"
#include "schema.hpp"

namespace janus {

ReadlineAtom::ReadlineAtom() : input_buffer_(1024) {}

void ReadlineAtom::Initialize(RestOfWorld* row)
{
  row_ = row;
  stdin_stream_.reset(new boost::asio::posix::stream_descriptor(row->GetIoService(), ::dup(STDIN_FILENO)));

  SchemaPtr input_expectations = std::make_shared<Schema>();
  input_expectations->has_name = true;
  input_expectations->name = "ReadlineNow";
  input_expectations->schema_type = SchemaType::SCALAR;
  input_expectations->scalar_type = ValueType::SIGNAL;

  input_.reset(new Interface(shared_from_this(),
                             InterfaceId(0),
                             "input",
                             InterfaceType::INPUT,
                             input_expectations));

  SchemaPtr output_expectations = std::make_shared<Schema>();
  output_expectations->has_name = true;
  output_expectations->name = "Line";
  output_expectations->schema_type = SchemaType::SCALAR;
  output_expectations->scalar_type = ValueType::STRING;

  output_.reset(new Interface(shared_from_this(),
                              InterfaceId(1),
                              "output",
                              InterfaceType::OUTPUT,
                              output_expectations));

  row_->Ready(input_);
}

void ReadlineAtom::GetInterfaces(std::vector<InterfacePtr>& interfaces) const
{
  interfaces.clear();
  interfaces.push_back(input_);
  interfaces.push_back(output_);
}

Status ReadlineAtom::Read(InterfaceId, ValuePtr& value)
{
  Status status;
  value.reset(new Value());
  value->has_name = true;
  value->name = "Line";
  value->value_type = ValueType::STRING;
  value->value_string = line_;
  row_->Ready(input_);
  return status;
}

// Received a Signal on our input interface. Post to asio to read a line from stdin.
Status ReadlineAtom::Write(InterfaceId, ValuePtr)
{
  Status status;
  boost::asio::async_read_until(*stdin_stream_, input_buffer_, '\n',
                                boost::bind(&ReadlineAtom::HandleReadInput, this, _1, _2));
  return status;
}

// asio is done reading a line from stdin.
void ReadlineAtom::HandleReadInput(const boost::system::error_code& error, std::size_t length)
{
  // Get length chars from input_buffer_ as string. Also clears those chars from input_buffer_.
  input_buffer_.prepare(length);
  input_buffer_.commit(length);
  boost::asio::streambuf::const_buffers_type bufs = input_buffer_.data();
  line_.clear();
  line_.assign(boost::asio::buffers_begin(bufs), boost::asio::buffers_begin(bufs) + length);
  input_buffer_.consume(length);
  row_->Ready(output_);
}

} // namespace janus