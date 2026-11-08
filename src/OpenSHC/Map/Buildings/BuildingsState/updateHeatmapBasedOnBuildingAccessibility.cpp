#include "../BuildingsState.func.hpp"

#include "OpenSHC/AI/AIVState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/DAT_AIVState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00424270
        void BuildingsState::updateHeatmapBasedOnBuildingAccessibility(int playerID)
        {
            for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                if (this->buildings[buildingID].logicalState != 0
                    && this->buildings[buildingID].logicalState != BLS_REMOVE
                    && this->buildings[buildingID].owner == playerID
                    && DAT_BuildingDefinedData::instance
                            .ABuildingTypeValueArray[this->buildings[buildingID].buildingType]
                        == 0) {
                    int const accessible = MACRO_CALL_MEMBER(
                        BuildingsState_Func::buildingIsAccessible, DAT_BuildingsState::ptr)(buildingID, 0);
                    if (accessible == 0) {
                        this->buildings[buildingID].logicalState = BLS_REMOVE;
                    } else if (accessible == 2) {
                        this->buildings[buildingID].logicalState = BLS_REMOVE;
                    }
                    if (this->buildings[buildingID].logicalState == BLS_REMOVE) {
                        MACRO_CALL_MEMBER(OpenSHC::AI::AIVState_Func::resetCountdownInHeatMap, DAT_AIVState::ptr)(
                            this->buildings[buildingID].x, this->buildings[buildingID].y);
                    }
                }
            }
        }

    }
}
}
