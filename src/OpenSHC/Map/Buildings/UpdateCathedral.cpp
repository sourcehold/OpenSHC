#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
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

    // FUNCTION: STRONGHOLDCRUSADER 0x004177E0
    void Buildings::UpdateCathedral()
    {
        int* piVar1;
        int buildingID;
        bool bVar2;
        MACRO_CALL_MEMBER(AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        buildingID = DAT_CurrentBuildingID::instance;
        bVar2 = DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        if (bVar2) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayImageID = 0;
        } else {
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
        if ((DAT_GameCore::instance.gameMode_2 == Game::GM_CAMPAIGN_MISSION)
            && (DAT_GameCore::instance.missionNumber1to20 == 7)) {
            if ((DAT_BuildingsState::instance.buildings[buildingID].maxHealth * 3) / 10
                < (int)DAT_BuildingsState::instance.buildings[buildingID].currentHealth) {
                DAT_BuildingsState::instance.buildings[buildingID].field249_0x2da = 0;
            } else if ((DAT_BuildingsState::instance.buildings[buildingID].field249_0x2da == 0)
                || (DAT_BuildingsState::instance.buildings[buildingID].spriteID != 0x11f)) {
                DAT_BuildingsState::instance.buildings[buildingID].field249_0x2da = 1;
                DAT_BuildingsState::instance.buildings[buildingID].spriteID = 0x11f;
                MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                    buildingID);
            }
        }
    }

}
}
