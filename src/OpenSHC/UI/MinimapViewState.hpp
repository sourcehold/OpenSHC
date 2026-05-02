/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MinimapViewState.hpp'
*/

#pragma once

#include "OpenSHC/Map/MapHeaderSection4IntStruct.hpp"
#include "WinDef.h"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Map::MapHeaderSection4IntStruct;

#pragma pack(push, 1)

    // SIZE: 0x00061BF8
    class MinimapViewState {
    public:
        undefined4 field0_0x0; // 0x00000000 length: 4
        undefined4 field1_0x4; // 0x00000004 length: 4
        undefined4 field2_0x8; // 0x00000008 length: 4
        undefined4 field3_0xc; // 0x0000000C length: 4
        undefined4 field4_0x10; // 0x00000010 length: 4
        undefined4 field5_0x14; // 0x00000014 length: 4
        undefined4 width; // 0x00000018 length: 4
        undefined4 height; // 0x0000001C length: 4
        undefined4 widthFactor; // 0x00000020 length: 4
        undefined4 heightFactor; // 0x00000024 length: 4
        undefined4 x; // 0x00000028 length: 4
        undefined4 y; // 0x0000002C length: 4
        undefined4 oneOrTwo; // 0x00000030 length: 4
        undefined4 field13_0x34; // 0x00000034 length: 4
        undefined4 field14_0x38; // 0x00000038 length: 4
        undefined4 field15_0x3c; // 0x0000003C length: 4
        undefined4 DAT_SomeMiniMapCounterTill4; // 0x00000040 length: 4
        ushort field17_0x44[80000]; // 0x00000044 length: 160000
        ushort field18_0x27144[80000]; // 0x00027144 length: 160000
        short loadedMiniMap[200][200]; // 0x0004E244 length: 80000
        MapHeaderSection4IntStruct DAT_MapU4B64; // 0x00061AC4 length: 64
        int spawnMomentX[20]; // 0x00061B04 length: 80
        int spawnMomentY[20]; // 0x00061B54 length: 80
        DWORD spawnMoment[20]; // 0x00061BA4 length: 80
        undefined4 spawnMomentCount; // 0x00061BF4 length: 4

    private:
        MinimapViewState(MinimapViewState const&);
        void operator=(MinimapViewState const&);

        MinimapViewState();
        ~MinimapViewState();

    public:
        // Constructor
        MinimapViewState* Constructor_MinimapViewState();

        void FUN_004b5110();

        void meth_0x4b51a0(int* param_1, int* param_2);

        void renderMinimapPreview(int screenX, int screenY);

        void meth_0x4b5300();

        void FUN_004b5330(uint param_1, int param_2, int param_3, uint param_4, int param_5);

        void setTileColorsUnk(uint param_1, int param_2, int param_3, int param_4, uint param_5);

        void meth_0x4b5f70(uint param_1, int param_2, int param_3);

        void generateMinimapImage();

        void createMapPreviewMiniMap_ConvertColorsUnk();

        void setSpawnMoment(int x, int y);

        void clearOldSpawnMoment();

        void setMapPropertyDependingOnMapSize(uint param_1, int param_2);

        void setTileColorsDependingOnMapSize(int param_1, uint param_2);

        void drawMinimap(int xPos, int yPos, int width, int height, uint flags, int xOffset, int yOffset,
            int widthFactor, int heightFactor, int param_10);

        void renderMinimapMain();

        void renderMinimapLandscaping(int xPos, int yPos, int width, int heigth);

        void renderMinimapEditor(int xPos, int yPos, int width, int height);

        void renderMiniMapForSaving(int param_1, int param_2, int param_3, int param_4);
    };

    static_assert_cpp98_obj(sizeof(MinimapViewState) == 400376, MinimapViewState);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(MinimapViewState, false, Address::SHC_3BB0A8C1_0x01A31610) pDAT_MinimapViewState;

} // namespace UI
} // namespace OpenSHC
