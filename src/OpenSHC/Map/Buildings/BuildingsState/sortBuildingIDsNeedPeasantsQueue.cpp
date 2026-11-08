#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0041C6F0
        void BuildingsState::sortBuildingIDsNeedPeasantsQueue(int playerID)
        {
            // The idle times are read from the fields each time rather than through locals: with locals the
            // allocator keeps &buildings[previous] in ebp instead of &buildings[current]. The two identical swap
            // blocks are deliberate: the original cross-jumps from the idle test into the second one.
            // Bubble sorts the queue by idle time, then by building priority
            if ((int)this->DAT_CountOfBuildingsNeedPeasants <= 1) {
                return;
            }
            int hasBurningBuilding
                = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::playerHasBurningBuilding,
                    DAT_BuildingsState::ptr)(playerID);
            int swapped;
            do {
                swapped = 0;
                for (int i = 0; i < (int)this->DAT_CountOfBuildingsNeedPeasants - 1; ++i) {
                    int const previous = (short)this->DAT_BuildingIDsNeedPeasantsQueue[i];
                    int const current = (short)this->DAT_BuildingIDsNeedPeasantsQueue[i + 1];
                    if (this->buildings[previous].idleTimerUnk > this->buildings[current].idleTimerUnk) {
                        this->DAT_BuildingIDsNeedPeasantsQueue[i] = current;
                        this->DAT_BuildingIDsNeedPeasantsQueue[i + 1] = previous;
                        swapped = 1;
                    } else if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingPriority,
                                   this)(this->buildings[current].buildingType, hasBurningBuilding)
                            < MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingPriority,
                                this)(this->buildings[previous].buildingType, hasBurningBuilding)
                        && this->buildings[current].idleTimerUnk <= this->buildings[previous].idleTimerUnk) {
                        this->DAT_BuildingIDsNeedPeasantsQueue[i] = current;
                        this->DAT_BuildingIDsNeedPeasantsQueue[i + 1] = previous;
                        swapped = 1;
                    }
                }
            } while (swapped != 0);
        }

    }
}
}
