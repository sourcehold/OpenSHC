/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MiniMap/MiniMapDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/Map/MapColorRelatedStructure1.hpp"

namespace OpenSHC {
namespace UI {
    namespace MiniMap {

        using OpenSHC::Map::MapColorRelatedStructure1;

#pragma pack(push, 1)
        // SIZE: 0x000002C4
        typedef struct MiniMapDefinedData {

            int LuminescenceBrightnessPercent[8]; // 0x00000000 length: 32
            ushort field_0x20[2]; // 0x00000020 length: 4
            ushort SeaMinimapColors[16]; // 0x00000024 length: 32
            ushort RiverMinimapColors[8]; // 0x00000044 length: 16
            ushort FordMinimapColors[8]; // 0x00000054 length: 16
            ushort field_0x64[8]; // 0x00000064 length: 16
            ushort field_0x74[8]; // 0x00000074 length: 16
            ushort BouldersMinimapColors[16]; // 0x00000084 length: 32
            ushort MinimapColorArray[8]; // 0x000000A4 length: 16
            ushort PebblesMinimapColors[8]; // 0x000000B4 length: 16
            ushort field_0xc4[8]; // 0x000000C4 length: 16
            ushort BeachMinimapColors[8]; // 0x000000D4 length: 16
            ushort IronMinimapColors[8]; // 0x000000E4 length: 16
            ushort MarshOrOilMinimapColors[8]; // 0x000000F4 length: 16
            ushort EarthMinimapColors[16]; // 0x00000104 length: 32
            ushort EarthAndStonesMinimapColors[16]; // 0x00000124 length: 32
            ushort field_0x144[8]; // 0x00000144 length: 16
            ushort StonesOrDrivenSandMinimapColors[8]; // 0x00000154 length: 16
            ushort ScrubMinimapColors[8]; // 0x00000164 length: 16
            ushort ThickScrubMinimapColors[8]; // 0x00000174 length: 16
            ushort OasisGrassMinimapColors[52]; // 0x00000184 length: 104
            ushort PlayerColorColors[9][4][2]; // 0x000001EC length: 144
            MapColorRelatedStructure1 MinimapColorByLogicBit[8]; // 0x0000027C length: 64
            int cachedKeepEnclosed; // 0x000002BC length: 4
            int cachedMapOrientation; // 0x000002C0 length: 4

        } MiniMapDefinedData;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(MiniMapDefinedData) == 708, MiniMapDefinedData);
    } // namespace MiniMap
} // namespace UI
} // namespace OpenSHC
