/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/AI/AIV/AIVDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/AI/AIV/AIVSectionAddress.hpp"
#include "OpenSHC/Commands/CommandBuildingTypeInt.hpp"

namespace OpenSHC {
namespace AI {
    namespace AIV {

        using OpenSHC::AI::AIV::AIVSectionAddress;
        using OpenSHC::Commands::CommandBuildingTypeInt;

#pragma pack(push, 1)
        // SIZE: 0x00001CEC
        typedef struct AIVDefinedData {

            undefined1 padding_0x0[4]; // 0x00000000 length: 4
            AIVSectionAddress DAT_AIVSectionAddressArray[14]; // 0x00000004 length: 224
            undefined1 padding_0xe4[16]; // 0x000000E4 length: 16
            CommandBuildingTypeInt field21_0xf4[79]; // 0x000000F4 length: 316
            undefined1 padding_0x230[4]; // 0x00000230 length: 4
            char DAT_AIVFileNames[16][8][50]; // 0x00000234 length: 6400
            int DAT_BuildingLocationFindingOffsetArray[9][2]; // 0x00001B34 length: 72
            int field28_0x1b7c[9][2]; // 0x00001B7C length: 72
            int field29_0x1bc4[9]; // 0x00001BC4 length: 36
            int field30_0x1be8[65]; // 0x00001BE8 length: 260

        } AIVDefinedData;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(AIVDefinedData) == 7404, AIVDefinedData);
    } // namespace AIV
} // namespace AI
} // namespace OpenSHC
