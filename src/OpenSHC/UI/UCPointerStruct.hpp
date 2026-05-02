/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/UCPointerStruct.hpp'
*/

#pragma once

#include "OpenSHC/UI/UC.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::UC;

#pragma pack(push, 1)
    // SIZE: 0x00000004
    typedef struct UCPointerStruct {

        UC* ucArrayPointer; // 0x00000000 length: 4

    } UCPointerStruct;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(UCPointerStruct) == 4, UCPointerStruct);
} // namespace UI
} // namespace OpenSHC
