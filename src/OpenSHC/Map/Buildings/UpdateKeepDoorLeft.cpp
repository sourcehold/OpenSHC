#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // quarryStockpileID is read with movsx (0x4189B7); oldVisualActiveState caches the low word of spriteID
    // (movsx compare at 0x418A21, word store at 0x418A4D). Unknown keep types leave sprite/gfx untouched.
    // FUNCTION: STRONGHOLDCRUSADER 0x004189A0
    void Buildings::UpdateKeepDoorLeft()
    {
        int buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        int keepBuildingID = (short)DAT_BuildingsState::instance.buildings[buildingID].quarryStockpileID;
        DAT_BuildingsState::instance.buildings[buildingID].orientation
            = DAT_BuildingsState::instance.buildings[keepBuildingID].orientation;
        OpenSHC::Map::Buildings::BuildingTypeShort keepType
            = DAT_BuildingsState::instance.buildings[keepBuildingID].buildingType;
        if (keepType == OpenSHC::Map::Buildings::BT_MANORHOUSE) {
            DAT_BuildingsState::instance.buildings[buildingID].gfxOffset = 0x531;
            DAT_BuildingsState::instance.buildings[buildingID].spriteID = 0x524;
        } else {
            if (keepType != OpenSHC::Map::Buildings::BT_STONEKEEP && keepType != OpenSHC::Map::Buildings::BT_STRONGHOLD) {
                goto checkSprite;
            }
            DAT_BuildingsState::instance.buildings[buildingID].gfxOffset = 0x52c;
            DAT_BuildingsState::instance.buildings[buildingID].spriteID = 0x522;
        }
        DAT_BuildingsState::instance.buildings[buildingID].unknownManorHouseOrStoneKeepRelated = 0;
    checkSprite:
        if (DAT_BuildingsState::instance.buildings[buildingID].spriteID
            != DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                buildingID);
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState
                = (short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteID;
        }
    }

}
}
