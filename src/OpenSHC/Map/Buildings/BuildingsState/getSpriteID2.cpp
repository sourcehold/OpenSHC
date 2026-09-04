#include "../BuildingsState.func.hpp"

#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Commands::MappersEnum;
        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00409FF0
        int BuildingsState::getSpriteID2(MappersEnum commandBuildingType)
        {
            int result = DAT_BuildingDefinedData::instance.Building_Sprite_ID_Array_2[MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType, this)(
                commandBuildingType)];
            if (result != 0) {
                return result;
            }

            // fixme: this is a tail call optimized situation. Merge getSpriteID into this file too?
            return MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getSpriteID, this)(
                commandBuildingType);
        }

    }
}
}
