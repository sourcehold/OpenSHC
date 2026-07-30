/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/AI/AIV/AIVDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/AI/AIV/AIVSectionAddress.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Map/Navigation/Algorithms/XYPair.hpp"

namespace OpenSHC {
namespace AI {
    namespace AIV {

        using OpenSHC::AI::AIV::AIVSectionAddress;
        using OpenSHC::Commands::MappersEnum;
        using OpenSHC::Map::Navigation::Algorithms::XYPair;

#pragma pack(push, 1)
        // SIZE: 0x00001CEC
        typedef struct AIVDefinedData {

            undefined1 padding_0x0[4]; // 0x00000000 length: 4
            AIVSectionAddress DAT_AIVSectionAddressArray[14]; // 0x00000004 length: 224
            undefined1 padding_0xe4[16]; // 0x000000E4 length: 16
            MappersEnum field21_0xf4[79]; // 0x000000F4 length: 316
            undefined1 padding_0x230[4]; // 0x00000230 length: 4
            char aivFileNames[16][8][50]; // 0x00000234 length: 6400
            XYPair offsetsForFiveByFiveAreaSpotCheck[9]; // 0x00001B34 length: 72
            XYPair offsetsForClockwiseThreeByThreeAreaCheck[9]; // 0x00001B7C length: 72
            XYPair offsetsForSpotCheckThreeByThreeAreaOnTheSide[4]; // 0x00001BC4 length: 32
            XYPair tilesSelfAndRightThree[4]; // 0x00001BE4 length: 32
            int field31_0x1c04[58]; // 0x00001C04 length: 232

        } AIVDefinedData;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(AIVDefinedData) == 7404, AIVDefinedData);
    } // namespace AIV
} // namespace AI
} // namespace OpenSHC
