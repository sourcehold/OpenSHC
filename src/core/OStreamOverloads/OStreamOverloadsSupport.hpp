#pragma once

#include <iomanip>
#include <ostream>

/*
    Support for enum printing.
    The macro can be used to add a case, assign, break to a switch, easier allowing to add more cases.
    Always consider number overlaps. The linter might warn, though.
*/

#define MACRO_ENUM_CASE(variable, name)                                                                                \
    case name:                                                                                                         \
        variable = #name;                                                                                              \
        break;

std::ostream& printEnum(std::ostream& os, char const* const name, unsigned int const value);
