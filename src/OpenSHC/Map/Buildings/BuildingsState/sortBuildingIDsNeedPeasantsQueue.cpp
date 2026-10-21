#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0041C6F0
        void BuildingsState::sortBuildingIDsNeedPeasantsQueue(int playerID)
        {
            if ((int)this->DAT_CountOfBuildingsNeedPeasants <= 1) {
                return;
            }
            int const hasBurningBuilding
                = MACRO_CALL_MEMBER(BuildingsState_Func::playerHasBurningBuilding, DAT_BuildingsState::ptr)(playerID);
            int swapped;
            do {
                swapped = 0;
                for (int i = 0; i < (int)this->DAT_CountOfBuildingsNeedPeasants - 1; ++i) {
                    int const firstID = (short)this->DAT_BuildingIDsNeedPeasantsQueue[i];
                    int const secondID = (short)this->DAT_BuildingIDsNeedPeasantsQueue[i + 1];
                    short const firstIdle = this->buildings[firstID].idleTimerUnk;
                    short const secondIdle = this->buildings[secondID].idleTimerUnk;
                    if (firstIdle > secondIdle
                        || (MACRO_CALL_MEMBER(BuildingsState_Func::getBuildingPriority, this)(
                                this->buildings[secondID].buildingType, hasBurningBuilding)
                                < MACRO_CALL_MEMBER(BuildingsState_Func::getBuildingPriority, this)(
                                    this->buildings[firstID].buildingType, hasBurningBuilding)
                            && secondIdle <= firstIdle)) {
                        swapped = 1;
                        this->DAT_BuildingIDsNeedPeasantsQueue[i + 1] = firstID;
                        this->DAT_BuildingIDsNeedPeasantsQueue[i] = secondID;
                    }
                }
            } while (swapped != 0);
        }

    }
}
}
