#include "writeline_atom.hpp"

#include <boost/bind.hpp>

#include "schema.hpp"

namespace janus {

WritelineAtom::WritelineAtom() : output_buffer_(1024) {}

void WritelineAtom::Initialize(RestOfWorld* row)
{

  row_ = row;
  stdout_stream_.reset(new boost::asio::posix::stream_descriptor(row->GetIoService(), ::dup(STDOUT_FILENO)));

  SchemaPtr input_expectations = std::make_shared<Schema>();
  input_expectations->has_name = true;
  input_expectations->name = "Line";
  input_expectations->schema_type = SchemaType::SCALAR;
  input_expectations->scalar_type = ValueType::STRING;

  output_.reset(new Interface(shared_from_this(),
                              InterfaceId(0),
                              "output",
                              InterfaceType::OUTPUT,
                              input_expectations));

  SchemaPtr output_expectations = std::make_shared<Schema>();
  output_expectations->has_name = true;
  output_expectations->name = "LineWritten";
  output_expectations->schema_type = SchemaType::SCALAR;
  output_expectations->scalar_type = ValueType::SIGNAL;

  input_.reset(new Interface(shared_from_this(),
                             InterfaceId(1),
                             "input",
                             InterfaceType::INPUT,
                             output_expectations));

  row_->Ready(input_);
}

void WritelineAtom::GetInterfaces(std::vector<InterfacePtr>& interfaces) const
{
  interfaces.clear();
  interfaces.push_back(input_);
  interfaces.push_back(output_);
}

// Receieved a Line to write to stdout.
Status WritelineAtom::Write(InterfaceId, ValuePtr value)
{
  Status status;
  output_buffer_.clear();
  const std::string &s = value->value_string;
  output_buffer_.insert(output_buffer_.begin(), s.begin(), s.end());
  boost::asio::async_write(*stdout_stream_, boost::asio::buffer(output_buffer_),
                           boost::bind(&WritelineAtom::HandleWriteComplete, this, _1, _2));
  return status;
}

// Asynchronous write to stdout as completed.
void WritelineAtom::HandleWriteComplete(const boost::system::error_code& error, std::size_t length)
{
  row_->Ready(output_);
}

Status WritelineAtom::Read(InterfaceId, ValuePtr& value)
{
  Status status;
  value.reset(new Value());
  value->has_name = true;
  value->name = "LineWritten";
  value->value_type = ValueType::SIGNAL;
  row_->Ready(input_);
  return status;
}

} // namespace janus
