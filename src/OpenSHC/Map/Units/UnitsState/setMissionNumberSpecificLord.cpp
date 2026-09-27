#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x005308F0
        void UnitsState::setMissionNumberSpecificLord(int missionNumber)
        {
            if (missionNumber == 5 || missionNumber == 6 || missionNumber == 8 || missionNumber == 15) {
                for (int unitID = 1; unitID < (int)this->maxUnitCount; ++unitID) {
                    if (this->units[unitID].logicalState == OpenSHC::Map::Units::ULS_NORMAL
                        && this->units[unitID].dying == 0
                        && this->units[unitID].owner != DAT_GameSynchronyState::instance.currentPlayerSlotID
                        && this->units[unitID].unitType == OpenSHC::Map::Units::UT_LORD) {
                        this->units[unitID].unknownLordTypeBasedMissionSpecificValue_01 = 1;
                    }
                }
                return;
            }
            if (missionNumber <= 15) {
                return;
            }
            for (int unitID = 1; unitID < (int)this->maxUnitCount; ++unitID) {
                if (this->units[unitID].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                    continue;
                }
                if (this->units[unitID].dying != 0) {
                    continue;
                }
                if (this->units[unitID].owner == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    continue;
                }
                if (this->units[unitID].unitType != OpenSHC::Map::Units::UT_LORD) {
                    continue;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::getLordTypeForPlayer,
                        DAT_GameSynchronyState::ptr)(this->units[unitID].owner)
                    == 1) {
                    this->units[unitID].unknownLordTypeBasedMissionSpecificValue_01 = 1;
                }
            }
        }

    }
}
}
