/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/UI/ActiveMenuTab.hpp'
*/

#pragma once

#include "OpenSHC/UI/Enums/BuildMenuTabTypeShort.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabTypeInt.hpp"
#include "OpenSHC/_SHCDE/eInBuildingModesInt.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::_SHCDE::eInBuildingModesInt;
    using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabTypeInt;
    using OpenSHC::UI::Enums::BuildMenuTabTypeShort;

#pragma pack(push, 1)
    // SIZE: 0x00000004
    typedef union ActiveMenuTab {

        BuildingsAndStatusMenuTabTypeInt tabType; // 0x00000000 length: 4
        BuildMenuTabTypeShort buildMenuTab; // 0x00000000 length: 4
        eInBuildingModesInt inBuildingTab; // 0x00000000 length: 4

    } ActiveMenuTab;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(ActiveMenuTab) == 4, ActiveMenuTab);
} // namespace UI
} // namespace OpenSHC
