/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/HoveredStateElement.hpp'
*/

#pragma once

#include "OpenSHC/Commands/CommandBuildingTypeInt.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Commands::CommandBuildingTypeInt;

#pragma pack(push, 1)
    // SIZE: 0x00000018
    typedef struct HoveredStateElement {

        int x; // 0x00000000 length: 4
        int y; // 0x00000004 length: 4
        CommandBuildingTypeInt type; // 0x00000008 length: 4
        int size; // 0x0000000C length: 4
        int time; // 0x00000010 length: 4
        int rotationOrExtraInfo; // 0x00000014 length: 4

    } HoveredStateElement;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(HoveredStateElement) == 24, HoveredStateElement);
} // namespace UI
} // namespace OpenSHC
