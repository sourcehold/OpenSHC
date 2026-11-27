#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004240D0
    void Buildings::UpdateWoodGate1()
    {
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int variation = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingVariation;
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateGateDrawBridgeOpenCloseLogic,
            DAT_BuildingsState::ptr)();
        if (DAT_TileMapState::instance.mapOrientation == 2 || DAT_TileMapState::instance.mapOrientation == 6) {
            variation += 1;
        }
        if (variation > 81) {
            variation = 80;
        }
        int const buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag = 1;
        DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite1 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite2 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite3 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite4 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage1 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage2 = 0;
        if (variation == 80) {
            DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite1 = 40;
            DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite3 = 9;
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite2 = 41;
            DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite4 = 10;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].pathLinkageRelated2 == 0) {
            if (DAT_BuildingsState::instance.buildings[buildingID].gateState == 10) {
                DAT_BuildingsState::instance.buildings[buildingID].pathLinkageRelated2 = 2;
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToGates,
                    DAT_PathFindingState::ptr)(buildingID);
            }
            return;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].pathLinkageRelated2 != 2) {
            return;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].gateState == 11) {
            DAT_BuildingsState::instance.buildings[buildingID].pathLinkageRelated2 = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToGates,
                DAT_PathFindingState::ptr)(buildingID);
        }
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = 0;
        if (variation == 80) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage1 = 6;
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage2 = 8;
        }
    }

}
}
