#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;
        using OpenSHC::Map::Units::Behavior::USE_STAND_GROUND;

        // maxUnitCount (uint) is compared signed (jle at 0x522CCF). The stance counter array is indexed with the
        // tribe's unitStance without a range check (0x522D15).
        // FUNCTION: STRONGHOLDCRUSADER 0x00522CA0
        void TribesState::snapshotSelectionTribeAndComputeStance(int playerID)
        {
            this->tribeCopiedToSlot0 = 0;
            BOOL multipleTribes = FALSE;
            int stanceCount[3];
            stanceCount[0] = 0;
            stanceCount[1] = 0;
            stanceCount[2] = 0;
            int lastTribeID = -1;
            for (int unitID = 1; unitID < (int)DAT_UnitsState::instance.maxUnitCount; ++unitID) {
                if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_NORMAL
                    && DAT_UnitsState::instance.units[unitID].dying == 0
                    && DAT_UnitsState::instance.units[unitID].ifSelectedThenPlayerID == playerID) {
                    int const tribeID = DAT_UnitsState::instance.units[unitID].tribeID;
                    if (tribeID > 0) {
                        ++stanceCount[this->tribes[tribeID].unitStance];
                        if (lastTribeID != -1 && tribeID != lastTribeID) {
                            multipleTribes = TRUE;
                        }
                        lastTribeID = tribeID;
                    }
                }
            }
            if (lastTribeID != -1 && !multipleTribes) {
                this->tribes[0] = this->tribes[lastTribeID];
                this->tribeCopiedToSlot0 = 1;
                return;
            }
            if (stanceCount[2] + stanceCount[1] + stanceCount[0] != 0) {
                if (stanceCount[2] >= stanceCount[1] && stanceCount[2] >= stanceCount[0]) {
                    this->tribes[0].unitStance = USE_AGGRESSIVE;
                } else {
                    this->tribes[0].unitStance = stanceCount[1] >= stanceCount[0];
                }
            } else {
                this->tribes[0].unitStance = USE_STAND_GROUND;
            }
        }

    }
}
}
