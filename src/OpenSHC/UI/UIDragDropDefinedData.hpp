/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/UIDragDropDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)
    // SIZE: 0x0000006C
    typedef struct UIDragDropDefinedData {

        BOOLEnum DAT_MenuView_TriggerInitial; // 0x00000000 length: 4
        byte DAT_UI_DragTicks[100]; // 0x00000004 length: 100
        undefined1 padding_0x68[4]; // 0x00000068 length: 4

    } UIDragDropDefinedData;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(UIDragDropDefinedData) == 108, UIDragDropDefinedData);
} // namespace UI
} // namespace OpenSHC
