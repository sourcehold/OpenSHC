#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00409FF0
        int BuildingsState::getSpriteID2(MappersEnum commandBuildingType)
        {
            BuildingType buildingType = MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType, this)(
                commandBuildingType);
            if (DAT_BuildingDefinedData::instance.Building_Sprite_ID_Array_2[buildingType] == 0) {
                return MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getSpriteID, this)(
                    commandBuildingType);
            }
            return DAT_BuildingDefinedData::instance.Building_Sprite_ID_Array_2[buildingType];
        }

    }
}
}
