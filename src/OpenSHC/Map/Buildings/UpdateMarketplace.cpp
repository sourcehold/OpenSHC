#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    using Game::GameMode;
    using Game::GameMode2;

    // FUNCTION: STRONGHOLDCRUSADER 0x00415C90
    void Buildings::UpdateMarketplace()
    {
        int* piVar1;
        byte bVar2;
        int buildingID;
        short sVar3;
        bool bVar4;
        MACRO_CALL_MEMBER(AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        buildingID = DAT_CurrentBuildingID::instance;
        bVar4 = DAT_GameCore::instance.gameMode_2 == Game::GM_SKIRMISH_AND_MULTIPLAYER;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[buildingID].animationIncrement = 1;
        DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag = 0;
        if (bVar4) {
            DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 1;
        } else {
            if (DAT_GameState::instance.mapAndTime.traderRelated2 == 2) {
                DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 1;
                if (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive != 1) {
                    DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 1;
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 0;
                    DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength = 0x1f;
                    DAT_BuildingsState::instance.buildings[buildingID].animationCycleCount = 0;
                }
                goto LAB_00415d57;
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive == 1) {
                DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 0;
                DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength = 1;
            }
            sVar3 = DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength;
            if ((!sVar3) || (0x1f < sVar3))
                goto LAB_00415d57;
        }
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 1;
    LAB_00415d57:
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updateVisuallyActiveState,
            DAT_BuildingsState::ptr)(buildingID);
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive
            != DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState) {
            MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                buildingID);
            buildingID = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive;
        }
        bVar2 = DAT_BuildingDefinedData::instance
                    .AnimMarketPlace[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
        DAT_BuildingsState::instance.buildings[buildingID].animationFrame = (int)(char)bVar2;
        if ((char)bVar2 <= 0) {
            DAT_BuildingsState::instance.buildings[buildingID].animationIndex = 0;
            piVar1 = &DAT_BuildingsState::instance.buildings[buildingID].animationCycleCount;
            *piVar1 = *piVar1 + 1;
            DAT_BuildingsState::instance.buildings[buildingID].animationCycleCompleted = 1;
            DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 1;
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].animationCycleCompleted = 0;
        }
        sVar3 = DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength;
        if (0 < sVar3) {
            if (DAT_BuildingsState::instance.buildings[buildingID].animationCycleCount == 0) {
                sVar3 = sVar3 + -1;
            } else {
                sVar3 = sVar3 + 1;
            }
            DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength = sVar3;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength <= 0) {
            DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength = 0;
        }
        if (0x1f < DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength) {
            DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength = 0x20;
            DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 0;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
            DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag = 1;
            piVar1 = &DAT_BuildingsState::instance.buildings[buildingID].flagSlot.ownerFlagFrame;
            *piVar1 = *piVar1 + 1;
            if ((char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                    [DAT_BuildingsState::instance.buildings[buildingID].flagSlot.ownerFlagFrame / 2]
                <= '\0') {
                DAT_BuildingsState::instance.buildings[buildingID].flagSlot.ownerFlagFrame = 0;
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayImageID
                = (int)(char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                      [DAT_BuildingsState::instance.buildings[buildingID].flagSlot.ownerFlagFrame / 2];
        }
        DAT_BuildingsState::instance.buildings[buildingID].overlayImageID = 0;
    }

}
}
