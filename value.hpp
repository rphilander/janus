#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace janus {

struct Value;
typedef std::shared_ptr<Value> ValuePtr;

enum class ValueType
{
  TABLE, SEQUENCE, BOOL, INT, FLOAT, STRING, SIGNAL
};

struct Value
{
  typedef std::unordered_map<std::string, ValuePtr> TableType;
  typedef std::vector<ValuePtr> SequenceType;
  typedef bool BoolType;
  typedef int IntType;
  typedef double FloatType;
  typedef std::string StringType;

  bool has_name;
  std::string name;

  ValueType value_type;

  TableType value_table;
  SequenceType value_sequence;
  BoolType value_bool;
  IntType value_int;
  FloatType value_float;
  StringType value_string;

};

} // namespace janus
