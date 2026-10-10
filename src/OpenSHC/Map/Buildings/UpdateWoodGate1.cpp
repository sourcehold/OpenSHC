#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
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
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int iVar2 = (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingVariation;
        MACRO_CALL_MEMBER(
            Map::Buildings::BuildingsState_Func::updateGateDrawBridgeOpenCloseLogic, DAT_BuildingsState::ptr)();
        int buildingID = DAT_CurrentBuildingID::instance;
        if ((DAT_TileMapState::instance.mapOrientation == 2) || (DAT_TileMapState::instance.mapOrientation == 6)) {
            iVar2 = iVar2 + 1;
        }
        if (0x51 < iVar2) {
            iVar2 = 0x50;
        }
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag = 1;
        DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite1 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite2 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite3 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite4 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage1 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage2 = 0;
        if (iVar2 == 0x50) {
            DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite1 = 0x28;
            DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite3 = 9;
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite2 = 0x29;
            DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite4 = 10;
        }
        byte bVar1 = DAT_BuildingsState::instance.buildings[buildingID].pathLinkageRelated2;
        if (!bVar1) {
            if (DAT_BuildingsState::instance.buildings[buildingID].gateState == 10) {
                DAT_BuildingsState::instance.buildings[buildingID].pathLinkageRelated2 = 2;
                MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToGates,
                    DAT_PathFindingState::ptr)(buildingID);
            }
        } else if (bVar1 == 2) {
            if (DAT_BuildingsState::instance.buildings[buildingID].gateState == 0xb) {
                DAT_BuildingsState::instance.buildings[buildingID].pathLinkageRelated2 = 0;
                MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToGates,
                    DAT_PathFindingState::ptr)(buildingID);
                buildingID = DAT_CurrentBuildingID::instance;
            }
            DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 1;
            DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 0;
            if (iVar2 == 0x50) {
                DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage1 = 6;
            }
            DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage2 = 8;
        }
    }

}
}
