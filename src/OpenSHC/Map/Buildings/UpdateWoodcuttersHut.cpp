#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace Map {

    // field206_0x2d4 is compared signed with someCount10 (movsx + jle at 0x410DAB); frame tables are
    // signed bytes (jg at 0x410DEC / 0x410EAF).
    // FUNCTION: STRONGHOLDCRUSADER 0x00410D20
    void Buildings::UpdateWoodcuttersHut()
    {
        int buildingID = DAT_CurrentBuildingID::instance;
        int owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation
            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workers[0] != 0;
        if (DAT_BuildingsState::instance.buildings[buildingID].currentlyNeededEmployeeCount != 0) {
            DAT_GameState::instance.playerDataArray[owner].countWoodcutters += 1;
        } else {
            DAT_GameState::instance.playerDataArray[owner].noLabourerBuildingCount += 1;
        }
        if (MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::destroyBuildingIfNoWorker, DAT_AICState::ptr)(buildingID)
            != 0) {
            return;
        }
        buildingID = DAT_CurrentBuildingID::instance;
        if (DAT_BuildingsState::instance.buildings[buildingID].field202_0x2c8 != 0) {
            DAT_BuildingsState::instance.buildings[buildingID].field206_0x2d4 = 0;
        }
        int pathLength = DAT_BuildingsState::instance.buildings[buildingID].field206_0x2d4;
        if (pathLength > DAT_GameState::instance.playerDataArray[owner].someCount10) {
            DAT_GameState::instance.playerDataArray[owner].someCount10 = pathLength;
            DAT_GameState::instance.playerDataArray[owner].someCount11 = buildingID;
        }
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        buildingID = DAT_CurrentBuildingID::instance;
        if ((char)DAT_BuildingDefinedData::instance
                .WoodcuttersHutAnimationFrames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
            <= 0) {
            DAT_BuildingsState::instance.buildings[buildingID].animationIndex = 0;
            int* counterPtr = &DAT_BuildingsState::instance.buildings[buildingID].animationCycleCount;
            *counterPtr = *counterPtr + 1;
            DAT_BuildingsState::instance.buildings[buildingID].animationCycleCompleted = 1;
        }
        int frame = (char)DAT_BuildingDefinedData::instance
                        .WoodcuttersHutAnimationFrames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
        DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame;
        if (frame == 0x10 && DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0) {
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                DAT_BuildingsState::instance.buildings[buildingID].x,
                DAT_BuildingsState::instance.buildings[buildingID].y, OpenSHC::DE::SHCDE::FX_SAW);
        }
        int pictureBase = GMFirstPictureIndex::instance[0x43];
        buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 1;
        int stock = DAT_BuildingsState::instance.buildings[buildingID].resources[1];
        if (stock != 0) {
            DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite1 = stock + 0x12 + pictureBase;
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite1 = 0;
        }
        stock = DAT_BuildingsState::instance.buildings[buildingID].resources[2];
        if (stock != 0) {
            DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite2 = stock + 0x15 + pictureBase;
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite2 = 0;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
            DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage += 1;
            if ((char)DAT_BuildingDefinedData::instance
                    .SharedOverlayAnimationFrames[DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage / 2]
                <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage = 0;
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayImageID = (char)DAT_BuildingDefinedData::instance
                .SharedOverlayAnimationFrames[DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage / 2];
            return;
        }
        DAT_BuildingsState::instance.buildings[buildingID].overlayImageID = 0;
    }

}
}
