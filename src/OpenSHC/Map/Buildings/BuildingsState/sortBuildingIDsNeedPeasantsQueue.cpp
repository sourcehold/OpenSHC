#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0041C6F0
        void BuildingsState::sortBuildingIDsNeedPeasantsQueue(int playerID)
        {
            // Bubble sorts the queue by idle time and building priority
            if ((int)this->DAT_CountOfBuildingsNeedPeasants <= 1) {
                return;
            }
            int hasBurningBuilding = MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::playerHasBurningBuilding, this)(playerID);
            bool swapped;
            do {
                swapped = false;
                for (int i = 0; i < (int)this->DAT_CountOfBuildingsNeedPeasants - 1; ++i) {
                    short current = this->DAT_BuildingIDsNeedPeasantsQueue[i + 1];
                    short previous = this->DAT_BuildingIDsNeedPeasantsQueue[i];
                    short currentIdle = this->buildings[current].idleTimerUnk;
                    short previousIdle = this->buildings[previous].idleTimerUnk;
                    if (currentIdle < previousIdle
                        || (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingPriority, this)(
                                this->buildings[previous].buildingType, hasBurningBuilding)
                                > MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingPriority,
                                    this)(this->buildings[current].buildingType, hasBurningBuilding)
                            && currentIdle <= previousIdle)) {
                        swapped = true;
                        this->DAT_BuildingIDsNeedPeasantsQueue[i + 1] = previous;
                        this->DAT_BuildingIDsNeedPeasantsQueue[i] = current;
                    }
                }
            } while (swapped);
        }

    }
}
}
