#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0041C6F0
        void BuildingsState::sortBuildingIDsNeedPeasantsQueue(int playerID)
        {
            // Matching note: The remaining difference is register and stack slot allocation of the IDs and
            // idle times. The count is kept in a register over the first call through /GL (see
            // cmake/compiler-flags-gl.txt).
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
                                this->buildings[previous].buildingType, hasBurningBuilding)
                                > MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingPriority,
                                    this)(this->buildings[current].buildingType, hasBurningBuilding)
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
