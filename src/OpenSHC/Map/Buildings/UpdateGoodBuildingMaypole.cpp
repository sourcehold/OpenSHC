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

    // FUNCTION: STRONGHOLDCRUSADER 0x00418740
    void Buildings::UpdateGoodBuildingMaypole()
    {
        int const owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].playerColorUnk
            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].fireRelatedRNG1 % 9;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int const buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength = 0;
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateBuildingSignpostCounter,
            DAT_BuildingsState::ptr)(buildingID, 1);
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation
            = DAT_GameState::instance.playerDataArray[owner].fearFactorLevel > 0;
        DAT_BuildingsState::instance.buildings[buildingID].spriteOffetX = -35;
        DAT_BuildingsState::instance.buildings[buildingID].spriteOffetY = -79;
        if (DAT_GameState::instance.playerDataArray[owner].popularity
            < (DAT_BuildingsState::instance.buildings[buildingID].fireRelatedRNG1 & 0xff) + 5000) {
            DAT_BuildingsState::instance.buildings[buildingID].animationFrame
                = (char)DAT_BuildingDefinedData::instance.GoodBuildingMaypoleAnimationFrames2
                      [DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                + 32;
            if (DAT_BuildingsState::instance.buildings[buildingID].animationFrame <= 32) {
                DAT_BuildingsState::instance.buildings[buildingID].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 33;
            }
            return;
        }
        DAT_BuildingsState::instance.buildings[buildingID].animationFrame
            = (char)DAT_BuildingDefinedData::instance.GoodBuildingMaypoleAnimationFrames1
                  [DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
        if (DAT_BuildingsState::instance.buildings[buildingID].animationFrame <= 0) {
            DAT_BuildingsState::instance.buildings[buildingID].animationCycleCount += 1;
            DAT_BuildingsState::instance.buildings[buildingID].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 1;
            if ((DAT_BuildingsState::instance.buildings[buildingID].animationCycleCount & 7) == 0) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_BuildingsState::instance.buildings[buildingID].x,
                    DAT_BuildingsState::instance.buildings[buildingID].y, OpenSHC::DE::SHCDE::FX_MAYPOLE);
            }
        }
    }

}
}
