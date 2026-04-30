/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/UI/UC.hpp'
*/

#pragma once

#include "OpenSHC/UI/Enums/UserControlIDInt.hpp"
#include "OpenSHC/UI/Position.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Position;
    using OpenSHC::UI::Enums::UserControlIDInt;

#pragma pack(push, 1)
    // SIZE: 0x000001F0
    typedef struct UC {

        Position defaultPosition; // 0x00000000 length: 8
        UserControlIDInt id; // 0x00000008 length: 4
        char* ucLabelPtr; // 0x0000000C length: 4
        Position ucPositionArray[40]; // 0x00000010 length: 320
        int isActiveArray[40]; // 0x00000150 length: 160

    } UC;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(UC) == 496, UC);
} // namespace UI
} // namespace OpenSHC
