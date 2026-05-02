/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/IO/SkMasterDataEntry.hpp'
*/

#pragma once

#include "OpenSHC/Game/Skirmish/SkirmishStatistics.hpp"

namespace OpenSHC {
namespace IO {

    using OpenSHC::Game::Skirmish::SkirmishStatistics;

#pragma pack(push, 1)
    // SIZE: 0x00000BF0
    typedef struct SkMasterDataEntry {

        int score; // 0x00000000 length: 4
        char mapName[1000]; // 0x00000004 length: 1000
        int skMasterScore; // 0x000003EC length: 4
        int activePlayerCount; // 0x000003F0 length: 4
        int array1[9]; // 0x000003F4 length: 36
        int aiArray[9]; // 0x00000418 length: 36
        int aliveArray[9]; // 0x0000043C length: 36
        int lordType; // 0x00000460 length: 4
        uint localTimeDay; // 0x00000464 length: 4
        uint localTimeMonth; // 0x00000468 length: 4
        uint localTimeYear; // 0x0000046C length: 4
        int gameDurationInMinutes; // 0x00000470 length: 4
        int mapTimeInTicks; // 0x00000474 length: 4
        SkirmishStatistics results; // 0x00000478 length: 1912

    } SkMasterDataEntry;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(SkMasterDataEntry) == 3056, SkMasterDataEntry);
} // namespace IO
} // namespace OpenSHC
