#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00521720
        UnitType TribesState::getMajoritySelectedUnitType(int tribeID, int* maximumCount)
        {
            int countOfUnitTypes[80];
            memset(countOfUnitTypes, 0, sizeof(countOfUnitTypes));
            for (int unitID = 1; unitID < (int)DAT_UnitsState::instance.maxUnitCount; ++unitID) {
                if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_NORMAL
                    && DAT_UnitsState::instance.units[unitID].dying == 0
                    && DAT_UnitsState::instance.units[unitID].owner
                        == DAT_GameSynchronyState::instance.currentPlayerSlotID
                    && DAT_UnitsState::instance.units[unitID].isSelected != 0) {
                    int const type = DAT_UnitsState::instance.units[unitID].unitType;
                    if (type < countof(countOfUnitTypes)) {
                        ++countOfUnitTypes[type];
                    }
                }
            }
            int maximumTroopType = 0;
            int maxCount = -1;
            for (int i = 1; i < countof(countOfUnitTypes); ++i) {
                if (countOfUnitTypes[i] > maxCount) {
                    maximumTroopType = i;
                    maxCount = countOfUnitTypes[i];
                }
            }
            if (maximumTroopType != 0 && maximumCount != 0) {
                *maximumCount = maxCount;
            }
            return (UnitType)maximumTroopType;
        }

    } // namespace Units
} // namespace Map
} // namespace OpenSHC
