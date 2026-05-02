/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItemUCInfo.hpp'
*/

#pragma once

#include "OpenSHC/UI/Enums/MenuItemUCMarkerInt.hpp"
#include "OpenSHC/UI/Enums/UserControlIDInt.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Enums::MenuItemUCMarkerInt;
    using OpenSHC::UI::Enums::UserControlIDInt;

#pragma pack(push, 1)
    // SIZE: 0x00000008
    typedef struct MenuItemUCInfo {

        MenuItemUCMarkerInt ucMarker_0x0; // 0x00000000 length: 4
        UserControlIDInt ucIndex_0x4; // 0x00000004 length: 4

    } MenuItemUCInfo;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(MenuItemUCInfo) == 8, MenuItemUCInfo);
} // namespace UI
} // namespace OpenSHC
