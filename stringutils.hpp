// stringutils.hpp

#include <string>

#include "status.hpp"

// Returns EOI when input is exhausted.
Status readline(const std::string &prompt, std::string &line);

Status get_token(std::string &token, std::string &source);
