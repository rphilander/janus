#pragma once

#include <memory>
#include <string>

#include "value.hpp"

namespace janus {

enum class SchemaType {
  COMPOSITE, OPTIONS, REPETITION, SCALAR, CONSTANT
};

struct Schema;
typedef std::shared_ptr<Schema> SchemaPtr;

struct Schema
{
  bool has_name;
  std::string name;

  SchemaType schema_type;

  // COMPOSITE
  std::vector<SchemaPtr> sequence;

  // OPTIONS
  std::vector<SchemaPtr> options;

  // REPETITION
  int repetition_min;
  int repetition_max;
  bool repetition_unlimited;
  SchemaPtr repetition;

  // SCALAR
  ValueType scalar_type;

  // CONSTANT
  ValuePtr constant_value;
};


} // namespace janus