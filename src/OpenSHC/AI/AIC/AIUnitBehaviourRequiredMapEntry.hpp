/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/AI/AIC/AIUnitBehaviourRequiredMapEntry.hpp'
*/

#pragma once

#include "OpenSHC/AI/AIUnitBehaviourTypeInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace AI {
    namespace AIC {

        using OpenSHC::AI::AIUnitBehaviourTypeInt;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)
        // SIZE: 0x00000008
        typedef struct AIUnitBehaviourRequiredMapEntry {

            AIUnitBehaviourTypeInt unitBehaviourType; // 0x00000000 length: 4
            BOOLEnum required; // 0x00000004 length: 4

        } AIUnitBehaviourRequiredMapEntry;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(AIUnitBehaviourRequiredMapEntry) == 8, AIUnitBehaviourRequiredMapEntry);
    } // namespace AIC
} // namespace AI
} // namespace OpenSHC
