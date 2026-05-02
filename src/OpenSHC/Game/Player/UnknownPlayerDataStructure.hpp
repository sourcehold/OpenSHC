/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/Player/UnknownPlayerDataStructure.hpp'
*/

#pragma once

#include "OpenSHC/Coordinates/XYPairShort.hpp"

namespace OpenSHC {
namespace Game {
    namespace Player {

        using OpenSHC::Coordinates::XYPairShort;

#pragma pack(push, 1)
        // SIZE: 0x000006C0
        typedef struct UnknownPlayerDataStructure {

            XYPairShort mercenaryOutpostCampgroundLocations[24]; // 0x00000000 length: 96
            XYPairShort xyPairs2[24]; // 0x00000060 length: 96
            XYPairShort xyPairs3[24]; // 0x000000C0 length: 96
            XYPairShort field3_0x120[24]; // 0x00000120 length: 96
            XYPairShort field4_0x180[24]; // 0x00000180 length: 96
            XYPairShort field5_0x1e0[24]; // 0x000001E0 length: 96
            XYPairShort field6_0x240[24]; // 0x00000240 length: 96
            XYPairShort field7_0x2a0[24]; // 0x000002A0 length: 96
            XYPairShort field8_0x300[24]; // 0x00000300 length: 96
            XYPairShort field9_0x360[24]; // 0x00000360 length: 96
            XYPairShort field10_0x3c0[24]; // 0x000003C0 length: 96
            XYPairShort field11_0x420[24]; // 0x00000420 length: 96
            XYPairShort field12_0x480[24]; // 0x00000480 length: 96
            XYPairShort field13_0x4e0[24]; // 0x000004E0 length: 96
            XYPairShort field14_0x540[24]; // 0x00000540 length: 96
            XYPairShort field15_0x5a0[24]; // 0x000005A0 length: 96
            XYPairShort field16_0x600[24]; // 0x00000600 length: 96
            XYPairShort field17_0x660[24]; // 0x00000660 length: 96

        } UnknownPlayerDataStructure;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(UnknownPlayerDataStructure) == 1728, UnknownPlayerDataStructure);
    } // namespace Player
} // namespace Game
} // namespace OpenSHC
