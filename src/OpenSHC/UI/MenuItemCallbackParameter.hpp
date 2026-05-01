/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/UI/MenuItemCallbackParameter.hpp'
*/

#pragma once

#include "OpenSHC/UI/ActiveMenuTab.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::ActiveMenuTab;

#pragma pack(push, 1)
    // SIZE: 0x00000004
    typedef union MenuItemCallbackParameter {

        int parameter; // 0x00000000 length: 4
        ActiveMenuTab activeMenuTab; // 0x00000000 length: 4
        int textIndex; // 0x00000000 length: 4

    } MenuItemCallbackParameter;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(MenuItemCallbackParameter) == 4, MenuItemCallbackParameter);
} // namespace UI
} // namespace OpenSHC
