/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/OrganismDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/Map/Navigation/Algorithms/XYPair.hpp"
#include "OpenSHC/Util/FunctionTypes/NoArgCallback.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Navigation::Algorithms::XYPair;
    using OpenSHC::Util::FunctionTypes::NoArgCallback;

#pragma pack(push, 1)
    // SIZE: 0x000010CC
    typedef struct OrganismDefinedData {

        undefined1 padding_0x0[4]; // 0x00000000 length: 4
        NoArgCallback* PTR_FUN_UpdateTree[20]; // 0x00000004 length: 80
        NoArgCallback* PTR_RockTypeFunctions[20]; // 0x00000054 length: 80
        int DAT_TreeRelated1[20][7]; // 0x000000A4 length: 560
        int DAT_TreeRelated2[20][7]; // 0x000002D4 length: 560
        int DAT_TreeStageLevels[20][7]; // 0x00000504 length: 560
        int TreeTypeBasedValueMapping[20]; // 0x00000734 length: 80
        int INT_ARRAY_Rock_field0xe[20]; // 0x00000784 length: 80
        int DAT_RandomRockImageGMImageOffsets[16]; // 0x000007D4 length: 64
        int field12_0x814; // 0x00000814 length: 4
        int field13_0x818; // 0x00000818 length: 4
        int field14_0x81c; // 0x0000081C length: 4
        int field15_0x820; // 0x00000820 length: 4
        int field16_0x824; // 0x00000824 length: 4
        int field17_0x828; // 0x00000828 length: 4
        int field18_0x82c; // 0x0000082C length: 4
        int field19_0x830; // 0x00000830 length: 4
        int field20_0x834; // 0x00000834 length: 4
        int field21_0x838; // 0x00000838 length: 4
        int field22_0x83c; // 0x0000083C length: 4
        int field23_0x840; // 0x00000840 length: 4
        int field24_0x844; // 0x00000844 length: 4
        int field25_0x848; // 0x00000848 length: 4
        int field26_0x84c; // 0x0000084C length: 4
        int field27_0x850; // 0x00000850 length: 4
        int field28_0x854[20]; // 0x00000854 length: 80
        int ANIM_Tree_2_B[124]; // 0x000008A4 length: 496
        int ANIM_Tree_2_A[120]; // 0x00000A94 length: 480
        byte ANIM_Tree_1_A[168]; // 0x00000C74 length: 168
        byte ANIM_Tree_1_B[720]; // 0x00000D1C length: 720
        XYPair DAT_TreeSpreadOffsets[8]; // 0x00000FEC length: 64
        int DAT_WindRelatedArray[40]; // 0x0000102C length: 160

    } OrganismDefinedData;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(OrganismDefinedData) == 4300, OrganismDefinedData);
} // namespace Map
} // namespace OpenSHC
