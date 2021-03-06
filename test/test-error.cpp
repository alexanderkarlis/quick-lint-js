// quick-lint-js finds bugs in JavaScript programs.
// Copyright (C) 2020  Matthew Glazar
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <gtest/gtest.h>
#include <quick-lint-js/error.h>
#include <string>
#include <unordered_map>

namespace quick_lint_js {
namespace {
TEST(test_error, error_codes_are_unique) {
  struct error_name_and_code {
    const char* name;
    const char* code;
  };
  static constexpr error_name_and_code all_errors[] = {
#define QLJS_ERROR_TYPE(error_name, error_code, struct_body, format) \
  {.name = #error_name, .code = error_code},
      QLJS_X_ERROR_TYPES
#undef QLJS_ERROR_TYPE
  };

  std::unordered_map<std::string, const char*> code_to_error_name;
  for (const error_name_and_code& error : all_errors) {
    auto existing_it = code_to_error_name.find(error.code);
    if (existing_it == code_to_error_name.end()) {
      code_to_error_name.emplace(error.code, error.name);
    } else {
      ADD_FAILURE() << "error code " << error.code
                    << " used for multiple errors: " << error.name << ", "
                    << existing_it->second;
    }
  }
}
}
}
