/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Game/TroopDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/Game/Resources/ResourceTypeInt.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::Resources::ResourceTypeInt;

#pragma pack(push, 1)
    // SIZE: 0x00000354
    typedef struct TroopDefinedData {

        undefined1 padding_0x0[4]; // 0x00000000 length: 4
        int DAT_PeasantSpawnClockIncrementSolitaryPopLessThan101[21]; // 0x00000004 length: 84
        undefined1 padding_0x58[4]; // 0x00000058 length: 4
        int DAT_PeasantSpawnClockIncrementSolitaryPopMoreThan100[21]; // 0x0000005C length: 84
        undefined1 padding_0xb0[4]; // 0x000000B0 length: 4
        int DAT_PeasantSpawnClockIncrementSkirmish[21]; // 0x000000B4 length: 84
        undefined1 padding_0x108[264]; // 0x00000108 length: 264
        int field279_0x210[38]; // 0x00000210 length: 152
        int field280_0x2a8; // 0x000002A8 length: 4
        ResourceTypeInt DAT_MarketResourceCycleArray[21]; // 0x000002AC length: 84
        uint DAT_BarracksUnitCost[7]; // 0x00000300 length: 28
        undefined1 padding_0x31c[12]; // 0x0000031C length: 12
        int DAT_NonEuroUnitCost[11]; // 0x00000328 length: 44

    } TroopDefinedData;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(TroopDefinedData) == 852, TroopDefinedData);
} // namespace Game
} // namespace OpenSHC
