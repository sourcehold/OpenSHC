/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/UI/TextMessageBLLookupStruct.hpp'
*/

#pragma once

#include "OpenSHC/UI/Enums/TextMessageBLLookupStructTypeEnumInt.hpp"
#include "OpenSHC/UI/TextMessageBLLookupStructUnion.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::TextMessageBLLookupStructUnion;
    using OpenSHC::UI::Enums::TextMessageBLLookupStructTypeEnumInt;

#pragma pack(push, 1)
    // SIZE: 0x00000010
    typedef struct TextMessageBLLookupStruct {

        TextMessageBLLookupStructTypeEnumInt messageType; // 0x00000000 length: 4
        int textGroupIndex; // 0x00000004 length: 4
        int textIndexInGroup; // 0x00000008 length: 4
        TextMessageBLLookupStructUnion associatedType; // 0x0000000C length: 4

    } TextMessageBLLookupStruct;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(TextMessageBLLookupStruct) == 16, TextMessageBLLookupStruct);
} // namespace UI
} // namespace OpenSHC
