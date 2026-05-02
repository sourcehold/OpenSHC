/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Rendering/ViewportState.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Rendering {

#pragma pack(push, 1)
    // SIZE: 0x000000B4
    typedef struct ViewportState {

        undefined4 field0_0x0; // 0x00000000 length: 4
        int mouseTileX; // 0x00000004 length: 4
        int mouseTileY; // 0x00000008 length: 4
        int mouseTile; // 0x0000000C length: 4
        int field4_0x10; // 0x00000010 length: 4
        undefined4 field5_0x14; // 0x00000014 length: 4
        undefined4 field6_0x18; // 0x00000018 length: 4
        int mouseRayBuildingID; // 0x0000001C length: 4
        undefined4 field8_0x20; // 0x00000020 length: 4
        int mouseRayEntityID; // 0x00000024 length: 4
        int mouseRayUnitID; // 0x00000028 length: 4
        undefined4 field11_0x2c; // 0x0000002C length: 4
        int mouseRayLastUnitID; // 0x00000030 length: 4
        undefined4 field13_0x34; // 0x00000034 length: 4
        undefined4 field14_0x38; // 0x00000038 length: 4
        undefined4 field15_0x3c; // 0x0000003C length: 4
        undefined4 field16_0x40; // 0x00000040 length: 4
        int somePitchDitchID; // 0x00000044 length: 4
        undefined4 field18_0x48; // 0x00000048 length: 4
        undefined4 field19_0x4c; // 0x0000004C length: 4
        undefined4 field20_0x50; // 0x00000050 length: 4
        undefined4 field21_0x54; // 0x00000054 length: 4
        undefined4 field22_0x58; // 0x00000058 length: 4
        undefined4 field23_0x5c; // 0x0000005C length: 4
        undefined4 field24_0x60; // 0x00000060 length: 4
        int mouseX; // 0x00000064 length: 4
        int mouseY; // 0x00000068 length: 4
        undefined4 field27_0x6c; // 0x0000006C length: 4
        int mouseAtomRefFloorTile; // 0x00000070 length: 4
        undefined4 ptrColor; // 0x00000074 length: 4
        int viewportX; // 0x00000078 length: 4
        int viewportY; // 0x0000007C length: 4
        int currentCameraOffsetX; // 0x00000080 length: 4
        int currentCameraOffsetY; // 0x00000084 length: 4
        int viewportHeight; // 0x00000088 length: 4
        int viewportWidth; // 0x0000008C length: 4
        int isZoomedOutUnk; // 0x00000090 length: 4
        undefined4 field37_0x94; // 0x00000094 length: 4
        undefined4 unknownScreenXRelated; // 0x00000098 length: 4
        int tileCenterX; // 0x0000009C length: 4
        int tileCenterY; // 0x000000A0 length: 4
        undefined4 someYOffset; // 0x000000A4 length: 4
        undefined4 someXOffset; // 0x000000A8 length: 4
        dword mbr_0xac; // 0x000000AC length: 4
        dword mbr_0xb0; // 0x000000B0 length: 4

    } ViewportState;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(ViewportState) == 180, ViewportState);
} // namespace Rendering
} // namespace OpenSHC
