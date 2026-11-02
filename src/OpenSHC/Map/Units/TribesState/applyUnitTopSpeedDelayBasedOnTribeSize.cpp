#include "../TribesState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // The pair slot advances for every member while the count only grows for living ones (0x524FCA), so
        // dead members leave zero holes and trailing living members are not re-indexed. The swap test is
        // signed (jge at 0x525009) and skipped entirely when skipDistanceSort is set.
        // FUNCTION: STRONGHOLDCRUSADER 0x00524EF0
        void TribesState::applyUnitTopSpeedDelayBasedOnTribeSize(int tribeID, BOOLEnum skipDistanceSort)
        {
            short* const tribeSize = &this->tribes[tribeID].size;
            int i = 0;
            int j;
            int swapped;
            if (*tribeSize >= 40) {
                for (; i < *tribeSize; ++i) {
                    int const unitID = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(tribeID, i);
                    DAT_UnitsState::instance.units[unitID].topSpeedDelayIndex = (short)(i < 199 ? i : 199);
                }
                return;
            }
            this->someUnitIDArrayCount = 0;
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(this->someUnitIDMovementDistancePair), 0, this->someUnitIDMovementDistancePair);
            for (; i < *tribeSize; ++i) {
                int const unitID = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(tribeID, i);
                if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_NORMAL
                    && DAT_UnitsState::instance.units[unitID].dying == 0) {
                    ++this->someUnitIDArrayCount;
                    this->someUnitIDMovementDistancePair[i].unitID = (short)unitID;
                    if (skipDistanceSort == FALSE) {
                        this->someUnitIDMovementDistancePair[i].movementDistance
                            = DAT_UnitsState::instance.units[unitID].movementDistance;
                    }
                }
            }
            do {
                swapped = 0;
                for (j = 0; j < this->someUnitIDArrayCount - 1; ++j) {
                    int const unitID = this->someUnitIDMovementDistancePair[j].unitID;
                    int const nextUnitID = this->someUnitIDMovementDistancePair[j + 1].unitID;
                    int const distance = this->someUnitIDMovementDistancePair[j].movementDistance;
                    int const nextDistance = this->someUnitIDMovementDistancePair[j + 1].movementDistance;
                    if (skipDistanceSort == FALSE && nextDistance < distance) {
                        swapped = 1;
                        this->someUnitIDMovementDistancePair[j].unitID = (short)nextUnitID;
                        this->someUnitIDMovementDistancePair[j + 1].unitID = (short)unitID;
                        this->someUnitIDMovementDistancePair[j].movementDistance = (short)nextDistance;
                        this->someUnitIDMovementDistancePair[j + 1].movementDistance = (short)distance;
                    }
                }
            } while (swapped != 0);
            for (i = 0; i < this->someUnitIDArrayCount; ++i) {
                DAT_UnitsState::instance.units[this->someUnitIDMovementDistancePair[i].unitID].topSpeedDelayIndex
                    = (short)i;
            }
        }

    }
}
}
