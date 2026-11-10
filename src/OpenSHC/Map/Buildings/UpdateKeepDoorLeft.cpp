#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004189A0
    void Buildings::UpdateKeepDoorLeft()
    {
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        int const keepID = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].quarryStockpileID;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].orientation
            = DAT_BuildingsState::instance.buildings[keepID].orientation;
        if (DAT_BuildingsState::instance.buildings[keepID].buildingType == BT_MANORHOUSE) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].gfxOffset = 0x531;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteID = 0x524;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].unknownManorHouseOrStoneKeepRelated
                = 0;
        } else if (DAT_BuildingsState::instance.buildings[keepID].buildingType == BT_STONEKEEP
            || DAT_BuildingsState::instance.buildings[keepID].buildingType == BT_STRONGHOLD) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].gfxOffset = 0x52c;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteID = 0x522;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].unknownManorHouseOrStoneKeepRelated
                = 0;
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
