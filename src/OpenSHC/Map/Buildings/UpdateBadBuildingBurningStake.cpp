#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
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

    // FUNCTION: STRONGHOLDCRUSADER 0x00418F90
    void Buildings::UpdateBadBuildingBurningStake()
    {
        int const owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].playerColorUnk = 0;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag = 0;
        DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength = 0;
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateBuildingSignpostCounter,
            DAT_BuildingsState::ptr)(buildingID, 1);
        int const fear = DAT_GameState::instance.playerDataArray[owner].fearFactorLevel;
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = fear <= -5;
        if (fear <= -5) {
            DAT_BuildingsState::instance.buildings[buildingID].animationFrame
                = (char)DAT_BuildingDefinedData::instance.BadBuildingBurningStakeAnimationFrames
                      [DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].animationFrame <= 0) {
            DAT_BuildingsState::instance.buildings[buildingID].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 1;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].animationActive == 0
            || DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU
            || DAT_GameCore::instance.activeMenuTab.tabType != OpenSHC::UI::Enums::BASMTT_BURNINGSTAKE
            || buildingID != DAT_BuildingsState::instance.menuSelectedBuildingID) {
            return;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].animationIndex == 47) {
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                DAT_BuildingsState::instance.buildings[buildingID].x,
                DAT_BuildingsState::instance.buildings[buildingID].y, OpenSHC::DE::SHCDE::FX_WITCH_BURN);
            buildingID = DAT_CurrentBuildingID::instance;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].animationIndex == 49) {
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                DAT_BuildingsState::instance.buildings[buildingID].x,
                DAT_BuildingsState::instance.buildings[buildingID].y, OpenSHC::DE::SHCDE::FX_WITCH_SCREAM);
        }
    }

}
}
