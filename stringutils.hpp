// stringutils.hpp

#include <string>

#include "errors.hpp"

bool readline(const std::string &prompt, std::string &line);

Error get_token(std::string &token, std::string &source);
