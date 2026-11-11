#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0041C6F0
        void BuildingsState::sortBuildingIDsNeedPeasantsQueue(int playerID)
        {
            // Bubble sorts the queue by idle time, then by building priority.
            if (this->DAT_CountOfBuildingsNeedPeasants <= 1) {
                return;
            }
            BOOLEnum const hasBurningBuilding
                = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::playerHasBurningBuilding,
                    DAT_BuildingsState::ptr)(playerID);
            for (BOOLEnum swapped = TRUE; swapped;) {
                swapped = FALSE;
                for (int i = 0; i < this->DAT_CountOfBuildingsNeedPeasants - 1; ++i) {
                    int const previous = this->DAT_BuildingIDsNeedPeasantsQueue[i];
                    int const current = this->DAT_BuildingIDsNeedPeasantsQueue[i + 1];
                    if (this->buildings[previous].idleTimerUnk > this->buildings[current].idleTimerUnk) {
                        this->DAT_BuildingIDsNeedPeasantsQueue[i] = current;
                        this->DAT_BuildingIDsNeedPeasantsQueue[i + 1] = previous;
                        swapped = TRUE;
                    } else if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingPriority,
                                   this)(this->buildings[current].buildingType, hasBurningBuilding)
                            < MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingPriority,
                                this)(this->buildings[previous].buildingType, hasBurningBuilding)
                        && this->buildings[current].idleTimerUnk <= this->buildings[previous].idleTimerUnk) {
                        this->DAT_BuildingIDsNeedPeasantsQueue[i] = current;
                        this->DAT_BuildingIDsNeedPeasantsQueue[i + 1] = previous;
                        swapped = TRUE;
                    }
                }
            }
        }

    }
}
}
