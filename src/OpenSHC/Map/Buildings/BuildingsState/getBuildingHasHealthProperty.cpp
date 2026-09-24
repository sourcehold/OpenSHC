#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040B900
        BOOLEnum BuildingsState::getBuildingHasHealthProperty(uint buildingID)
        {
            if (buildingID == 0) {
                return FALSE;
            }
            switch (this->buildings[buildingID].buildingType) {
            case BT_GATEHOUSELARGE:
            case BT_GATEHOUSESMALL:
            case BT_TOWER1:
            case BT_TOWER2:
            case BT_TOWER3:
            case BT_TOWER4:
            case BT_TOWER5:
                return TRUE;
            default:
                return (BOOLEnum)(DAT_BuildingDefinedData::instance
                                      .BuildingTypeHasHealth[this->buildings[buildingID].buildingType]
                    != 0);
            }
        }

    }
}
}
