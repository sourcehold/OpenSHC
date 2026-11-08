#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0041C6F0
        void BuildingsState::sortBuildingIDsNeedPeasantsQueue(int playerID)
        {
            // Matching note: The original keeps the count in ebx across playerHasBurningBuilding, which needs /GL
            // (the callees are in cmake/compiler-flags-gl.txt, this file is not). That shifts the register
            // allocation of the IDs and building pointers in the loop.
            // Bubble sorts the queue by idle time and building priority
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
                    int current = (short)this->DAT_BuildingIDsNeedPeasantsQueue[i + 1];
                    int previous = (short)this->DAT_BuildingIDsNeedPeasantsQueue[i];
                    short currentIdle = this->buildings[current].idleTimerUnk;
                    short previousIdle = this->buildings[previous].idleTimerUnk;
                    if (previousIdle > currentIdle
                        || (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingPriority, this)(
                                this->buildings[current].buildingType, hasBurningBuilding)
                                < MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingPriority,
                                    this)(this->buildings[previous].buildingType, hasBurningBuilding)
                            && currentIdle <= previousIdle)) {
                        swapped = 1;
                        current = (short)this->DAT_BuildingIDsNeedPeasantsQueue[i + 1];
                        this->DAT_BuildingIDsNeedPeasantsQueue[i + 1] = previous;
                        this->DAT_BuildingIDsNeedPeasantsQueue[i] = current;
                    }
                }
            } while (swapped != 0);
        }

    }
}
}
