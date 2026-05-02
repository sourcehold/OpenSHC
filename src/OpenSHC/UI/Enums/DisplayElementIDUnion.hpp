/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Enums/DisplayElementIDUnion.hpp'
*/

#pragma once

#include "OpenSHC/DE/SHCDE/eOnScreenTextInt.hpp"
#include "OpenSHC/UI/Enums/DisplayElementIDInt.hpp"

namespace OpenSHC {
namespace UI {
    namespace Enums {

        using OpenSHC::DE::SHCDE::eOnScreenTextInt;
        using OpenSHC::UI::Enums::DisplayElementIDInt;

#pragma pack(push, 1)
        // SIZE: 0x00000004
        typedef union DisplayElementIDUnion {

            eOnScreenTextInt shcde; // 0x00000000 length: 4
            DisplayElementIDInt shc; // 0x00000000 length: 4

        } DisplayElementIDUnion;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(DisplayElementIDUnion) == 4, DisplayElementIDUnion);
    } // namespace Enums
} // namespace UI
} // namespace OpenSHC
