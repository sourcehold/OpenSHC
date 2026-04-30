/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/UI/Enums/MenuViewTypeUnion.hpp'
*/

#pragma once

#include "OpenSHC/UI/Enums/MenuViewTypeInt.hpp"
#include "OpenSHC/_SHCDE/eAppModesInt.hpp"

namespace OpenSHC {
namespace UI {
    namespace Enums {

        using OpenSHC::_SHCDE::eAppModesInt;
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
