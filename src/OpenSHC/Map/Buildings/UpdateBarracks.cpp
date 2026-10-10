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

    // FUNCTION: STRONGHOLDCRUSADER 0x00411480
    void Buildings::UpdateBarracks()
    {
        int* piVar1;
        int iVar2;
        iVar2 = DAT_CurrentBuildingID::instance;
        piVar1 = &DAT_GameState::instance
                      .playerDataArray[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner]
                      .someCount04;
        *piVar1 = *piVar1 + 10;
        MACRO_CALL_MEMBER(AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(iVar2);
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        iVar2 = DAT_CurrentBuildingID::instance;
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 1;
            piVar1 = &DAT_BuildingsState::instance.buildings[iVar2].flagSlot.ownerFlagFrame;
            *piVar1 = *piVar1 + 1;
            if ((char)DAT_BuildingDefinedData::instance
                    .SharedOverlayAnimationFrames[DAT_BuildingsState::instance.buildings[iVar2].flagSlot.ownerFlagFrame
                        / 2]
                <= '\0') {
                DAT_BuildingsState::instance.buildings[iVar2].flagSlot.ownerFlagFrame = 0;
            }
            DAT_BuildingsState::instance.buildings[iVar2].overlayImageID
                = (int)(char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                      [DAT_BuildingsState::instance.buildings[iVar2].flagSlot.ownerFlagFrame / 2];
        }
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayImageID = 0;
    }

}
}
