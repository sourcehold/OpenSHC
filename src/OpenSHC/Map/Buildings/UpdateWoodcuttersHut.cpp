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

    // FUNCTION: STRONGHOLDCRUSADER 0x00410D20
    void Buildings::UpdateWoodcuttersHut()
    {
        int const owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation
            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workers[0] != 0;
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentlyNeededEmployeeCount != 0) {
            DAT_GameState::instance.playerDataArray[owner].countWoodcutters += 1;
        } else {
            DAT_GameState::instance.playerDataArray[owner].noLabourerBuildingCount += 1;
        }
        if (MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::destroyBuildingIfNoWorker, DAT_AICState::ptr)(
                DAT_CurrentBuildingID::instance)
            != FALSE) {
            return;
        }
        int const buildingID = DAT_CurrentBuildingID::instance;
        if (DAT_BuildingsState::instance.buildings[buildingID].field201_0x2c8 != 0) {
            DAT_BuildingsState::instance.buildings[buildingID].field205_0x2d4 = 0;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].field205_0x2d4
            > DAT_GameState::instance.playerDataArray[owner].someCount10) {
            DAT_GameState::instance.playerDataArray[owner].someCount10
                = DAT_BuildingsState::instance.buildings[buildingID].field205_0x2d4;
            DAT_GameState::instance.playerDataArray[owner].someCount11 = buildingID;
        }
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        if ((char)DAT_BuildingDefinedData::instance.WoodcuttersHutAnimationFrames
                [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex]
            <= 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationCycleCount += 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationCycleCompleted = 1;
        }
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame
            = (char)DAT_BuildingDefinedData::instance.WoodcuttersHutAnimationFrames
                  [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame == 16
            && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0) {
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y, OpenSHC::DE::SHCDE::FX_SAW);
        }
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 1;
        // GMTotalPicturesProcessed[67] is the first picture of the woodcutter's log piles.
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].resources[1] != 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].resources[1]
                + GMTotalPicturesProcessed::instance[67] + 18;
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 0;
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].resources[2] != 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].resources[2]
                + GMTotalPicturesProcessed::instance[67] + 21;
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2 = 0;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage += 1;
            if (DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                    [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage / 2]
                <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage = 0;
            }
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayImageID
                = DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage
                          / 2];
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayImageID = 0;
        }
    }

}
}
