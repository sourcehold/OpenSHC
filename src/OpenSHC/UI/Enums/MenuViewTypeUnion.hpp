/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Enums/MenuViewTypeUnion.hpp'
*/

#pragma once

#include "OpenSHC/DE/SHCDE/eAppModesInt.hpp"
#include "OpenSHC/UI/Enums/MenuViewTypeInt.hpp"

namespace OpenSHC {
namespace UI {
    namespace Enums {

        using OpenSHC::DE::SHCDE::eAppModesInt;
        using OpenSHC::UI::Enums::MenuViewTypeInt;

#pragma pack(push, 1)
        // SIZE: 0x00000004
        typedef union MenuViewTypeUnion {

            eAppModesInt shcde; // 0x00000000 length: 4
            MenuViewTypeInt shc; // 0x00000000 length: 4

        } MenuViewTypeUnion;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(MenuViewTypeUnion) == 4, MenuViewTypeUnion);
    } // namespace Enums
} // namespace UI
} // namespace OpenSHC
