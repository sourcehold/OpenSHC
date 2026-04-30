/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/UI/BuildingNameRelatedStruct.hpp'
*/

#pragma once

#include "OpenSHC/UI/BuildingNameRelatedSubStruct.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::BuildingNameRelatedSubStruct;

#pragma pack(push, 1)
    // SIZE: 0x00000028
    typedef struct BuildingNameRelatedStruct {

        int nameNumberInTextGroup; // 0x00000000 length: 4
        BuildingNameRelatedSubStruct field1_0x4[3]; // 0x00000004 length: 36

    } BuildingNameRelatedStruct;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(BuildingNameRelatedStruct) == 40, BuildingNameRelatedStruct);
} // namespace UI
} // namespace OpenSHC
