/**
  path: 'OpenSHC/Game/ScenarioEvents/InGameEventUnionVersion.func.hpp'
*/

#include "OpenSHC/Game/ScenarioEvents/InGameEventUnionVersion.hpp"
#include "OpenSHC/Game/ScenarioEvents/ScenarioEventCondition.hpp"
namespace OpenSHC {
namespace Game {
    namespace ScenarioEvents {
        namespace InGameEventUnionVersion_Func {

            using OpenSHC::Game::ScenarioEvents::ScenarioEventCondition;

            MACRO_FUNCTION_RESOLVER(undefined4 (InGameEventUnionVersion::*)(), false, Address::SHC_3BB0A8C1_0x004B7730,
                &InGameEventUnionVersion::resetEvent)
            resetEvent;

            MACRO_FUNCTION_RESOLVER(ScenarioEventCondition* (InGameEventUnionVersion::*)(), false,
                Address::SHC_3BB0A8C1_0x004B77A0, &InGameEventUnionVersion::initializeScenarioEvent)
            initializeScenarioEvent;

        } // namespace InGameEventUnionVersion_Func
    } // namespace ScenarioEvents
} // namespace Game
} // namespace OpenSHC
