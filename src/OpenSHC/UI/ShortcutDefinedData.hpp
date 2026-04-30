/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/UI/ShortcutDefinedData.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {

#pragma pack(push, 1)
    // SIZE: 0x0000001C
    typedef struct ShortcutDefinedData {

        undefined4 DAT_ScreenshotFilenameVariant; // 0x00000000 length: 4
        undefined4 DAT_CyclingLordID; // 0x00000004 length: 4
        string DAT_CheatCodeString; // 0x00000008 length: 16
        undefined1 padding_0x18[4]; // 0x00000018 length: 4

    } ShortcutDefinedData;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(ShortcutDefinedData) == 28, ShortcutDefinedData);
} // namespace UI
} // namespace OpenSHC
