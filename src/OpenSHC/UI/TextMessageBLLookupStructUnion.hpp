/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/TextMessageBLLookupStructUnion.hpp'
*/

#pragma once

#include "OpenSHC/Commands/CommandBuildingTypeInt.hpp"
#include "OpenSHC/UI/Enums/TextMessageBLLookupStructButtonTextEnumInt.hpp"
#include "OpenSHC/UI/TextMessageBLLookupStructUnitsTextTypeInt.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Commands::CommandBuildingTypeInt;
    using OpenSHC::UI::TextMessageBLLookupStructUnitsTextTypeInt;
    using OpenSHC::UI::Enums::TextMessageBLLookupStructButtonTextEnumInt;

#pragma pack(push, 1)
    // SIZE: 0x00000004
    typedef union TextMessageBLLookupStructUnion {

        CommandBuildingTypeInt buildingType; // 0x00000000 length: 4
        TextMessageBLLookupStructUnitsTextTypeInt unitsAndWeaponsType; // 0x00000000 length: 4
        TextMessageBLLookupStructButtonTextEnumInt buttonText; // 0x00000000 length: 4

    } TextMessageBLLookupStructUnion;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(TextMessageBLLookupStructUnion) == 4, TextMessageBLLookupStructUnion);
} // namespace UI
} // namespace OpenSHC
