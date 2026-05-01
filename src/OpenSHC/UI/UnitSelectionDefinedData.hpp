/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/UI/UnitSelectionDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/Map/Navigation/Algorithms/XYPair.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Map::Navigation::Algorithms::XYPair;

#pragma pack(push, 1)
    // SIZE: 0x00000E04
    typedef struct UnitSelectionDefinedData {

        undefined1 padding_0x0[1604]; // 0x00000000 length: 1604
        short DAT_BitMaskHelper[16]; // 0x00000644 length: 32
        short DAT_BitMaskHelper2[16]; // 0x00000664 length: 32
        int DAT_UnitInstructionMoveDelay[200]; // 0x00000684 length: 800
        int DAT_UnitMoveDelay[200]; // 0x000009A4 length: 800
        XYPair field1608_0xcc4[40]; // 0x00000CC4 length: 320

    } UnitSelectionDefinedData;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(UnitSelectionDefinedData) == 3588, UnitSelectionDefinedData);
} // namespace UI
} // namespace OpenSHC
