/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/UI/MenuIDMenuElementAddressPair.hpp'
*/

#pragma once

#include "OpenSHC/UI/Enums/MenuViewTypeInt.hpp"
#include "OpenSHC/UI/Menu.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Menu;
    using OpenSHC::UI::Enums::MenuViewTypeInt;

#pragma pack(push, 1)
    // SIZE: 0x00000008
    typedef struct MenuIDMenuElementAddressPair {

        MenuViewTypeInt menuID; // 0x00000000 length: 4
        Menu* menuAddress; // 0x00000004 length: 4

    } MenuIDMenuElementAddressPair;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(MenuIDMenuElementAddressPair) == 8, MenuIDMenuElementAddressPair);
} // namespace UI
} // namespace OpenSHC
