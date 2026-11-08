#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00409FF0
        int BuildingsState::getSpriteID2(MappersEnum commandBuildingType)
        {
            int const spriteID = DAT_BuildingDefinedData::instance.Building_Sprite_ID_Array_2[MACRO_CALL_MEMBER(
                BuildingsState_Func::convertCommandBuildingTypeToBuildingType, this)(commandBuildingType)];
            if (spriteID != 0) {
                return spriteID;
            }
            return MACRO_CALL_MEMBER(BuildingsState_Func::getSpriteID, this)(commandBuildingType);
        }

    }
}
}
