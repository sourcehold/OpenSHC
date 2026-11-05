#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0041C6F0
        void BuildingsState::sortBuildingIDsNeedPeasantsQueue(int playerID)
        {
            if (this->DAT_CountOfBuildingsNeedPeasants <= 1) {
                return;
            }
            int const hasBurningBuilding
                = MACRO_CALL_MEMBER(BuildingsState_Func::playerHasBurningBuilding, DAT_BuildingsState::ptr)(playerID);
            int swapped;
            do {
                swapped = 0;
                for (int i = 0; i < this->DAT_CountOfBuildingsNeedPeasants - 1; ++i) {
                    short* const second = &this->DAT_BuildingIDsNeedPeasantsQueue[i + 1];
                    int const secondID = second[0];
                    int const firstID = second[-1];
                    Building const& secondBuilding = this->buildings[secondID];
                    Building const& firstBuilding = this->buildings[firstID];
                    short const firstIdle = firstBuilding.idleTimerUnk;
                    short const secondIdle = secondBuilding.idleTimerUnk;
                    if (firstIdle > secondIdle
                        || (MACRO_CALL_MEMBER(BuildingsState_Func::getBuildingPriority, this)(
                                secondBuilding.buildingType, hasBurningBuilding)
                                < MACRO_CALL_MEMBER(BuildingsState_Func::getBuildingPriority, this)(
                                    firstBuilding.buildingType, hasBurningBuilding)
                            && secondIdle <= firstIdle)) {
                        swapped = 1;
                        second[0] = firstID;
                        second[-1] = secondID;
                    }
                }
            } while (swapped != 0);
        }

    }
}
}
