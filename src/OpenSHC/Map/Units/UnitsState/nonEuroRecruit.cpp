#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x0052EC10
        int UnitsState::nonEuroRecruit(UnitType unitType, undefined4 recruitmentBuilding, int playerID, int param_4)
        {
            this->euroUnitAcquisitionFailReason = 0;
            int _unitCost;
            if (unitType == OpenSHC::Map::Units::UT_E_ENGINEER) {
                _unitCost = 0x1e;
            } else if (unitType == OpenSHC::Map::Units::UT_TUNNELER) {
                _unitCost = 0x1e;
            } else if (unitType == OpenSHC::Map::Units::UT_E_LADDER) {
                _unitCost = 4;
            } else if (unitType == OpenSHC::Map::Units::UT_E_MONK) {
                _unitCost = 10;
            } else if (unitType == OpenSHC::Map::Units::UT_A_ARCHER) {
                _unitCost = 0x4b;
            } else if (unitType == OpenSHC::Map::Units::UT_A_SLAVE) {
                _unitCost = 5;
            } else if (unitType == OpenSHC::Map::Units::UT_A_SLINGER) {
                _unitCost = 0xc;
            } else if (unitType == OpenSHC::Map::Units::UT_A_ASSASSIN) {
                _unitCost = 0x3c;
            } else if (unitType == OpenSHC::Map::Units::UT_A_HARCHER) {
                _unitCost = 0x50;
            } else if (unitType == OpenSHC::Map::Units::UT_A_SWORDSMAN) {
                _unitCost = 0x50;
            } else if (unitType == OpenSHC::Map::Units::UT_A_FIRETHROWER) {
                _unitCost = 100;
            } else {
                return 0;
            }
            /* Check if player has enough gold, then convert peasant to new unit */
            if (DAT_GameState::instance.playerDataArray[playerID].currentResources[0xf] < _unitCost) {
                this->euroUnitAcquisitionFailReason = 1;
                return 0;
            }
            for (int unitID = 1; unitID < (int)this->maxUnitCount; ++unitID) {
                if (this->units[unitID].unitType != OpenSHC::Map::Units::UT_PEASANT) {
                    continue;
                }
                if (this->units[unitID].owner != playerID) {
                    continue;
                }
                if (this->units[unitID].dying != 0) {
                    continue;
                }
                if (this->units[unitID].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                    continue;
                }
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk) {
                    continue;
                }
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_AIM_WEAPONUnk) {
                    continue;
                }
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_JESTER_ROAM_TO) {
                    continue;
                }
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_MELEE_ATTACK) {
                    continue;
                }
                if (param_4 != 0) {
                    return 1;
                }
                this->units[unitID].unitTypeToChangeInto = (UnitTypeShort)unitType;
                this->units[unitID].state_2 = 0;
                this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
                this->units[unitID].disappearFadeAlphaCountdown = 0;
                this->units[unitID].engineerManningSiegeStateRef_checkType = 1;
                this->units[unitID].cachedState = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                this->units[unitID].isDisappearingUnk = 1;
                this->units[unitID].workplaceBuildingID_1 = (short)recruitmentBuilding;
                this->units[unitID].resourceToDeposit = 0;
                DAT_GameState::instance.playerDataArray[playerID].currentResources[0xf] -= _unitCost;
                DAT_GameSynchronyState::instance.finalResults.finalTroopsProduced[playerID] += 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::aiAssignNewUnitToTribe, DAT_TribesState::ptr)(
                    playerID, unitType, unitID);
                return unitID;
            }
            this->euroUnitAcquisitionFailReason = 3;
            return 0;
        }

    }
}
}
