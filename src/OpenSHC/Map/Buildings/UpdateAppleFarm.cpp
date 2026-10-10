#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {

    using Game::GameMode;

    // FUNCTION: STRONGHOLDCRUSADER 0x00416720
    void Buildings::UpdateAppleFarm()
    {
        int* piVar1;
        short sVar2;
        int iVar3;
        bool bVar4;
        iVar3 = DAT_CurrentBuildingID::instance;
        sVar2 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        piVar1 = &DAT_GameState::instance.playerDataArray[sVar2].countFarms;
        *piVar1 = *piVar1 + 1;
        if (DAT_BuildingsState::instance.buildings[iVar3].workers[0] == 0) {
            piVar1 = &DAT_GameState::instance.playerDataArray[sVar2].farmsWithoutWorkers;
            *piVar1 = *piVar1 + 1;
        }
        MACRO_CALL_MEMBER(AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(iVar3);
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        iVar3 = DAT_CurrentBuildingID::instance;
        bVar4 = DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        if (bVar4) {
            DAT_BuildingsState::instance.buildings[iVar3].displayOwnerFlag = 1;
            piVar1 = &DAT_BuildingsState::instance.buildings[iVar3].flagSlot.ownerFlagFrame;
            *piVar1 = *piVar1 + 1;
            if ((char)DAT_BuildingDefinedData::instance
                    .SharedOverlayAnimationFrames[DAT_BuildingsState::instance.buildings[iVar3].flagSlot.ownerFlagFrame
                        / 2]
                <= '\0') {
                DAT_BuildingsState::instance.buildings[iVar3].flagSlot.ownerFlagFrame = 0;
            }
            DAT_BuildingsState::instance.buildings[iVar3].overlayImageID
                = (int)(char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                      [DAT_BuildingsState::instance.buildings[iVar3].flagSlot.ownerFlagFrame / 2];
        }
        DAT_BuildingsState::instance.buildings[iVar3].overlayImageID = 0;
    }

}
}
