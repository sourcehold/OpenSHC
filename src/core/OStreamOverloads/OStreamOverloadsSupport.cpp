#include "OStreamOverloadsSupport.hpp"

std::ostream& printEnum(std::ostream& os, char const* const name, unsigned int const value)
{
    return os << name << "(" << value << ")";
}
