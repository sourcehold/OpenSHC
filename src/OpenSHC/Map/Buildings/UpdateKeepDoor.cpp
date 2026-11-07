#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00418B20
    void Buildings::UpdateKeepDoor()
    {
        int const keepID = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].quarryStockpileID;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].orientation
            = DAT_BuildingsState::instance.buildings[keepID].orientation;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation
            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].useOffsetGraphics == 0;
        if (DAT_BuildingsState::instance.buildings[keepID].buildingType == BT_MANORHOUSE) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].gfxOffset = 0x533;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteID = 0x52f;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].unknownManorHouseOrStoneKeepRelated
                = 0;
            if (DAT_TileMapState::instance.mapOrientation != 0 && DAT_TileMapState::instance.mapOrientation != 4) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetX = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetY = -42;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = 34;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetX = -2;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetY = -44;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = 32;
            }
        } else if (DAT_BuildingsState::instance.buildings[keepID].buildingType == BT_STONEKEEP
            || DAT_BuildingsState::instance.buildings[keepID].buildingType == BT_STRONGHOLD) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].gfxOffset = 0x52e;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteID = 0x52a;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].unknownManorHouseOrStoneKeepRelated
                = 0;
            if (DAT_TileMapState::instance.mapOrientation != 0 && DAT_TileMapState::instance.mapOrientation != 4) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetY = -64;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetX = 14;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = 30;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetY = -63;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetX = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = 28;
            }
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteID
            != DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                DAT_CurrentBuildingID::instance);
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteID;
        }
    }

}
}
