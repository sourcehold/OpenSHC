/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/Units/Climbing/ClimbLogicDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/Map/Navigation/Algorithms/XYPair.hpp"
#include "OpenSHC/Util/FunctionTypes/NoArgCallback.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace Climbing {

            using OpenSHC::Map::Navigation::Algorithms::XYPair;
            using OpenSHC::Util::FunctionTypes::NoArgCallback;

#pragma pack(push, 1)
            // SIZE: 0x000002BC
            typedef struct ClimbLogicDefinedData {

                NoArgCallback* updateFunctions[10]; // 0x00000000 length: 40
                undefined1 padding_0x28[4]; // 0x00000028 length: 4
                int field5_0x2c[8]; // 0x0000002C length: 32
                int field6_0x4c[55]; // 0x0000004C length: 220
                undefined1 field7_0x128; // 0x00000128 length: 1
                undefined1 field8_0x129; // 0x00000129 length: 1
                undefined1 field9_0x12a; // 0x0000012A length: 1
                undefined1 field10_0x12b; // 0x0000012B length: 1
                byte DAT_BitFlagHelperForPathLinkage[8]; // 0x0000012C length: 8
                byte DAT_DirectionArray[8]; // 0x00000134 length: 8
                int field13_0x13c[8][3]; // 0x0000013C length: 96
                XYPair DAT_CardinalHorizontalFirstSearchOrder[4]; // 0x0000019C length: 32
                XYPair DAT_OrderedOrientationBasedCardinalDirectionList[8][4]; // 0x000001BC length: 256

            } ClimbLogicDefinedData;
#pragma pack(pop)

            static_assert_cpp98_obj(sizeof(ClimbLogicDefinedData) == 700, ClimbLogicDefinedData);
        } // namespace Climbing
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
