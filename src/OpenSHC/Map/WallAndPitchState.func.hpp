/**
  path: 'OpenSHC/Map/WallAndPitchState.func.hpp'
*/

#include "OpenSHC/Map/WallAndPitchState.hpp"
namespace OpenSHC {
namespace Map {
    namespace WallAndPitchState_Func {

        MACRO_FUNCTION_RESOLVER(void (WallAndPitchState::*)(int), false, Address::SHC_3BB0A8C1_0x00500C20,
            &WallAndPitchState::startBuildingDestructionConfirmation)
        startBuildingDestructionConfirmation;

        MACRO_FUNCTION_RESOLVER(void (WallAndPitchState::*)(), false, Address::SHC_3BB0A8C1_0x00500C80,
            &WallAndPitchState::resetWallAndPitchState)
        resetWallAndPitchState;

        MACRO_FUNCTION_RESOLVER(void (WallAndPitchState::*)(int), false, Address::SHC_3BB0A8C1_0x00500CB0,
            &WallAndPitchState::startEntityDestructionConfirmation)
        startEntityDestructionConfirmation;

        MACRO_FUNCTION_RESOLVER(void (WallAndPitchState::*)(int), false, Address::SHC_3BB0A8C1_0x00500CF0,
            &WallAndPitchState::startUnitDestructionConfirmation)
        startUnitDestructionConfirmation;

        MACRO_FUNCTION_RESOLVER(void (WallAndPitchState::*)(), false, Address::SHC_3BB0A8C1_0x00500D30,
            &WallAndPitchState::resetWallPlacementInfo)
        resetWallPlacementInfo;

        MACRO_FUNCTION_RESOLVER(void (WallAndPitchState::*)(int), false, Address::SHC_3BB0A8C1_0x00500D60,
            &WallAndPitchState::addWallPlacementInfoForTile)
        addWallPlacementInfoForTile;

        MACRO_FUNCTION_RESOLVER(void (WallAndPitchState::*)(int), false, Address::SHC_3BB0A8C1_0x00500DD0,
            &WallAndPitchState::placePitchDitch)
        placePitchDitch;

        MACRO_FUNCTION_RESOLVER(void (WallAndPitchState::*)(int, int, int, int), false,
            Address::SHC_3BB0A8C1_0x00500E20, &WallAndPitchState::destroyWall)
        destroyWall;

        MACRO_FUNCTION_RESOLVER(void (WallAndPitchState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x00500EE0,
            &WallAndPitchState::destroyPitch)
        destroyPitch;

        MACRO_FUNCTION_RESOLVER(void (WallAndPitchState::*)(), false, Address::SHC_3BB0A8C1_0x00500F40,
            &WallAndPitchState::updateDestructionConfirmationCountdown)
        updateDestructionConfirmationCountdown;

        MACRO_FUNCTION_RESOLVER(void (WallAndPitchState::*)(), false, Address::SHC_3BB0A8C1_0x005118C0,
            &WallAndPitchState::confirmAndQueueDestructionCommand)
        confirmAndQueueDestructionCommand;

    } // namespace WallAndPitchState_Func
} // namespace Map
} // namespace OpenSHC
