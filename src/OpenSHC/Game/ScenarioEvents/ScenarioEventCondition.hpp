/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Game/ScenarioEvents/ScenarioEventCondition.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Game {
    namespace ScenarioEvents {

#pragma pack(push, 1)
        // SIZE: 0x00000004
        typedef struct ScenarioEventCondition {

            short value; // 0x00000000 length: 2
            byte subType; // 0x00000002 length: 1
            byte enabled; // 0x00000003 length: 1

        } ScenarioEventCondition;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(ScenarioEventCondition) == 4, ScenarioEventCondition);
    } // namespace ScenarioEvents
} // namespace Game
} // namespace OpenSHC
