#include "OpenSHC/AI/AIVState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_AIVState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00424270
        void BuildingsState::updateHeatmapBasedOnBuildingAccessibility(int playerID)
        {
            // Removes the buildings of the player that cannot be accessed anymore
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState == 0 || this->buildings[i].logicalState == BLS_REMOVE
                    || this->buildings[i].owner != playerID
                    || DAT_BuildingDefinedData::instance.ABuildingTypeValueArray[this->buildings[i].buildingType]
                        != FALSE) {
                    continue;
                }
                int accessibility = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible, DAT_BuildingsState::ptr)(i, 0);
                if (accessibility == 0) {
                    this->buildings[i].logicalState = BLS_REMOVE;
                } else if (accessibility == 2) {
                    this->buildings[i].logicalState = BLS_REMOVE;
                }
                if (this->buildings[i].logicalState == BLS_REMOVE) {
                    MACRO_CALL_MEMBER(OpenSHC::AI::AIVState_Func::resetCountdownInHeatMap, DAT_AIVState::ptr)(
                        (short)this->buildings[i].x, (short)this->buildings[i].y);
                }
            }
        }

    }
}
}
