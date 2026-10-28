#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00415C90
    void Buildings::UpdateMarketplace()
    {
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[buildingID].animationIncrement = 1;
        DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag = 0;
        if (DAT_GameCore::instance.gameMode_2 == Game::GM_SKIRMISH_AND_MULTIPLAYER) {
            DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 1;
            DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 1;
        } else if (DAT_GameState::instance.mapAndTime.traderRelated2 == 2) {
            DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 1;
            if (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive != 1) {
                DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 1;
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 0;
                DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength = 31;
                DAT_BuildingsState::instance.buildings[buildingID].animationCycleCount = 0;
            }
        } else {
            if (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive == 1) {
                DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 0;
                DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength = 1;
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength != 0
                && DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength < 32) {
                DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 1;
            }
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateVisuallyActiveState,
            DAT_BuildingsState::ptr)(buildingID);
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive
            != DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                buildingID);
            buildingID = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState
                = DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive;
        }
        DAT_BuildingsState::instance.buildings[buildingID].animationFrame
            = (char)DAT_BuildingDefinedData::instance
                  .AnimMarketPlace[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
        if (DAT_BuildingsState::instance.buildings[buildingID].animationFrame <= 0) {
            DAT_BuildingsState::instance.buildings[buildingID].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[buildingID].animationCycleCount += 1;
            DAT_BuildingsState::instance.buildings[buildingID].animationCycleCompleted = 1;
            DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 1;
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].animationCycleCompleted = 0;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength > 0) {
            if (DAT_BuildingsState::instance.buildings[buildingID].animationCycleCount == 0) {
                DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength -= 1;
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength += 1;
            }
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength <= 0) {
            DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength = 0;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength >= 32) {
            DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength = 32;
            DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 0;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != 0) {
            DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag = 1;
            DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage += 1;
            if (DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                    [DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage / 2]
                <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage = 0;
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayImageID
                = DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                      [DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage / 2];
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].overlayImageID = 0;
        }
    }

}
}
