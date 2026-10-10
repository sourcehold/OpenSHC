#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    using DE::SHCDE::eSFX;
    using UI::Enums::BuildingsAndStatusMenuTabType;
    using UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x00419420
    void Buildings::UpdateBadBuildingDunkingStool()
    {
        byte bVar1;
        short sVar2;
        int buildingID;
        sVar2 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        MACRO_CALL_MEMBER(AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].playerColorUnk = 0;
        DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag = 0;
        DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength = 0;
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updateBuildingSignpostCounter, DAT_BuildingsState::ptr)(
            buildingID, 1);
        if (DAT_GameState::instance.playerDataArray[sVar2].fearFactorLevel < -4) {
            DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 1;
            DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 1;
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 0;
            DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 0;
        }
        bVar1 = DAT_BuildingDefinedData::instance.BadBuildingDunkingStoolAnimationFrames
                    [DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
        DAT_BuildingsState::instance.buildings[buildingID].animationFrame = (int)(char)bVar1;
        if ((char)bVar1 < 1) {
            DAT_BuildingsState::instance.buildings[buildingID].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 1;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0
            && DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILDING_AND_STATUS_MENU
            && DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_DUNKINGSTOOL
            && buildingID == DAT_BuildingsState::instance.menuSelectedBuildingID) {
            if (DAT_BuildingsState::instance.buildings[buildingID].animationIndex == 4) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    (int)(short)DAT_BuildingsState::instance.buildings[buildingID].x,
                    (int)((short)DAT_BuildingsState::instance.buildings[buildingID].y), DE::SHCDE::FX_WH_DUNK);
                buildingID = DAT_CurrentBuildingID::instance;
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].animationIndex == 0x22) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    (int)(short)DAT_BuildingsState::instance.buildings[buildingID].x,
                    (int)((short)DAT_BuildingsState::instance.buildings[buildingID].y), DE::SHCDE::FX_WH_BREATH1);
                buildingID = DAT_CurrentBuildingID::instance;
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].animationIndex == 0x48) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    (int)(short)DAT_BuildingsState::instance.buildings[buildingID].x,
                    (int)((short)DAT_BuildingsState::instance.buildings[buildingID].y), DE::SHCDE::FX_WH_BREATH2);
                buildingID = DAT_CurrentBuildingID::instance;
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].animationIndex == 0x68) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    (int)(short)DAT_BuildingsState::instance.buildings[buildingID].x,
                    (int)((short)DAT_BuildingsState::instance.buildings[buildingID].y), DE::SHCDE::FX_WH_LIFT);
                buildingID = DAT_CurrentBuildingID::instance;
            }
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive
            != DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState) {
            MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(buildingID);
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive;
        }
    }

}
}
