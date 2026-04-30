/**
  path: 'OpenSHC/UI/HoveredState.func.hpp'
*/

#include "OpenSHC/Commands/CommandBuildingTypeInt.hpp"
#include "OpenSHC/UI/HoveredState.hpp"
namespace OpenSHC {
namespace UI {
    namespace HoveredState_Func {

        using OpenSHC::Commands::CommandBuildingTypeInt;

        MACRO_FUNCTION_RESOLVER(
            void (HoveredState::*)(), false, Address::SHC_3BB0A8C1_0x005010C0, &HoveredState::clearHoveredState)
        clearHoveredState;

        MACRO_FUNCTION_RESOLVER(void (HoveredState::*)(), false, Address::SHC_3BB0A8C1_0x005010E0,
            &HoveredState::clearInvalidatedHoverStates)
        clearInvalidatedHoverStates;

        MACRO_FUNCTION_RESOLVER(void (HoveredState::*)(int, int, CommandBuildingTypeInt, int, int), false,
            Address::SHC_3BB0A8C1_0x00501110, &HoveredState::createHoverStateElement)
        createHoverStateElement;

        MACRO_FUNCTION_RESOLVER(
            void (HoveredState::*)(), false, Address::SHC_3BB0A8C1_0x005119D0, &HoveredState::calculateHoveredTile)
        calculateHoveredTile;

    } // namespace HoveredState_Func
} // namespace UI
} // namespace OpenSHC
