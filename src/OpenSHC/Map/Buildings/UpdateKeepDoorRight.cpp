#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // Same as UpdateKeepDoorLeft with the right-side sprite IDs (0x528 manor house at 0x418AAB, 0x526 keep at
    // 0x418ACD).
    // FUNCTION: STRONGHOLDCRUSADER 0x00418A60
    void Buildings::UpdateKeepDoorRight()
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
            DAT_BuildingsState::instance.buildings[buildingID].spriteID = 0x528;
        } else {
            if (keepType != OpenSHC::Map::Buildings::BT_STONEKEEP && keepType != OpenSHC::Map::Buildings::BT_STRONGHOLD) {
                goto checkSprite;
            }
            DAT_BuildingsState::instance.buildings[buildingID].gfxOffset = 0x52c;
            DAT_BuildingsState::instance.buildings[buildingID].spriteID = 0x526;
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
