#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
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

    // FUNCTION: STRONGHOLDCRUSADER 0x00416540
    void Buildings::UpdateWheatFarm()
    {
        short sVar3;
        int iVar4;
        iVar4 = DAT_CurrentBuildingID::instance;
        sVar3 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        DAT_GameState::instance.playerDataArray[sVar3].countFarms
            = DAT_GameState::instance.playerDataArray[sVar3].countFarms + 1;
        if (DAT_BuildingsState::instance.buildings[iVar4].workers[0] == 0) {
            DAT_GameState::instance.playerDataArray[sVar3].farmsWithoutWorkers
                = DAT_GameState::instance.playerDataArray[sVar3].farmsWithoutWorkers + 1;
        }
        /*
          Two fire related functions.
         */
        MACRO_CALL_MEMBER(AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(iVar4);
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        iVar4 = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[iVar4].growCounter
            = DAT_BuildingsState::instance.buildings[iVar4].growCounter + 1;
        if (0x96 < DAT_BuildingsState::instance.buildings[iVar4].growCounter) {
            DAT_BuildingsState::instance.buildings[iVar4].growCounter = 0;
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::growWheat, DAT_BuildingsState::ptr)(iVar4);
        }
        MACRO_CALL_MEMBER(
            Map::Buildings::BuildingsState_Func::updateWheatFieldTileGraphics, DAT_BuildingsState::ptr)(iVar4);
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
            DAT_BuildingsState::instance.buildings[iVar4].displayOwnerFlag = 1;
            DAT_BuildingsState::instance.buildings[iVar4].flagSlot.ownerFlagFrame
                = DAT_BuildingsState::instance.buildings[iVar4].flagSlot.ownerFlagFrame + 1;
            if ((char)DAT_BuildingDefinedData::instance
                    .SharedOverlayAnimationFrames[DAT_BuildingsState::instance.buildings[iVar4].flagSlot.ownerFlagFrame
                        / 2]
                <= '\0') {
                DAT_BuildingsState::instance.buildings[iVar4].flagSlot.ownerFlagFrame = 0;
            }
            DAT_BuildingsState::instance.buildings[iVar4].overlayImageID
                = (int)(char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                      [DAT_BuildingsState::instance.buildings[iVar4].flagSlot.ownerFlagFrame / 2];
        }
        DAT_BuildingsState::instance.buildings[iVar4].overlayImageID = 0;
    }

}
}
