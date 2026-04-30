/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/UI/MenuItemFirstItemTypeData.hpp'
*/

#pragma once

#include "OpenSHC/Rendering/Enums/GmDataIndexInt.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Rendering::Enums::GmDataIndexInt;

#pragma pack(push, 1)
    // SIZE: 0x00000004
    typedef union MenuItemFirstItemTypeData {

        GmDataIndexInt gmDataIndex; // 0x00000000 length: 4
        int itemsToSkip; // 0x00000000 length: 4

    } MenuItemFirstItemTypeData;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(MenuItemFirstItemTypeData) == 4, MenuItemFirstItemTypeData);
} // namespace UI
} // namespace OpenSHC
