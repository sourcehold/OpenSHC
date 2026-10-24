#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005362F0
        uint UnitsState::getFirstSelectedUnitOfEitherType(int unitType_1, int unitType_2)
        {
            int _currentPlayerSlotID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            for (DAT_CurrentUnitSlotID::instance = 1; DAT_CurrentUnitSlotID::instance < this->maxUnitCount;
                DAT_CurrentUnitSlotID::instance = DAT_CurrentUnitSlotID::instance + 1) {
                if (this->units[DAT_CurrentUnitSlotID::instance].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                    continue;
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].dying) {
                    continue;
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].isSelected == 0) {
                    continue;
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].owner != _currentPlayerSlotID) {
                    return 0;
                }
                if ((short)this->units[DAT_CurrentUnitSlotID::instance].unitType == unitType_1) {
                    return DAT_CurrentUnitSlotID::instance;
                }
                if ((short)this->units[DAT_CurrentUnitSlotID::instance].unitType == unitType_2) {
                    return DAT_CurrentUnitSlotID::instance;
                }
            }
            return 0;
        }

    }
}
}
