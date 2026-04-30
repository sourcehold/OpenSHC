/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/UI/MenuItemPosition.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItemUCInfo.hpp"
#include "OpenSHC/UI/Position.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::MenuItemUCInfo;
    using OpenSHC::UI::Position;

#pragma pack(push, 1)
    // SIZE: 0x00000008
    typedef union MenuItemPosition {

        Position position; // 0x00000000 length: 8
        MenuItemUCInfo ucInfo; // 0x00000000 length: 8

    } MenuItemPosition;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(MenuItemPosition) == 8, MenuItemPosition);
} // namespace UI
} // namespace OpenSHC
