#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::Map::Buildings::BuildingTypeShort;

        // FUNCTION: STRONGHOLDCRUSADER 0x00422370
        uint BuildingsState::getArmoryWithSpaceLeft(
            uint targetBuildingID, undefined4 producedItemTypeUnk, int playerID, int resourceToDeposit)
        {
            if (targetBuildingID != 0) {
                return MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft, this)(
                    targetBuildingID, (undefined4)((int)(producedItemTypeUnk)), playerID, resourceToDeposit);
            }
            for (int _buildingID = 1; _buildingID < (int)this->maxBuildingsCount; _buildingID++) {
                if (this->buildings[_buildingID].buildingType == Buildings::BT_ARMORY) {
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible, this)(
                            _buildingID, 0)) {
                        if (MACRO_CALL_MEMBER(
                                OpenSHC::Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft, this)(
                                _buildingID, (undefined4)((int)(producedItemTypeUnk)), playerID, resourceToDeposit)) {
                            return _buildingID;
                        }
                    }
                }
            }
            return 0;
        }

    }
}
}
