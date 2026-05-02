/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/UIButtonDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/UI/Rendering/ButtonGmData.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Rendering::ButtonGmData;

#pragma pack(push, 1)
    // SIZE: 0x0000490C
    typedef struct UIButtonDefinedData {

        int field0_0x0; // 0x00000000 length: 4
        int field1_0x4; // 0x00000004 length: 4
        int field2_0x8; // 0x00000008 length: 4
        int field3_0xc; // 0x0000000C length: 4
        int field4_0x10; // 0x00000010 length: 4
        int field5_0x14; // 0x00000014 length: 4
        int field6_0x18; // 0x00000018 length: 4
        int field7_0x1c; // 0x0000001C length: 4
        int field8_0x20; // 0x00000020 length: 4
        int field9_0x24; // 0x00000024 length: 4
        int field10_0x28; // 0x00000028 length: 4
        int field11_0x2c; // 0x0000002C length: 4
        undefined1 padding_0x30[4]; // 0x00000030 length: 4
        ButtonGmData DAT_ButtonGmDataArray[650]; // 0x00000034 length: 18200
        char field17_0x474c[7][32]; // 0x0000474C length: 224
        char field18_0x482c[7][32]; // 0x0000482C length: 224

    } UIButtonDefinedData;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(UIButtonDefinedData) == 18700, UIButtonDefinedData);
} // namespace UI
} // namespace OpenSHC
