#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Map::Units::States::UnitState;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004591F0
    void GameStateStructures::despawnPeasantOrWorker(int playerID)
    {
        for (int unitID = 1; unitID < (int)DAT_UnitsState::instance.maxUnitCount; unitID++) {
            if ((DAT_UnitsState::instance.units[unitID].logicalState == OpenSHC::Map::Units::ULS_NORMAL)
                && (DAT_UnitsState::instance.units[unitID].dying == 0)
                && (DAT_UnitsState::instance.units[unitID].owner == playerID)
                && (DAT_UnitsState::instance.units[unitID].unitType == OpenSHC::Map::Units::UT_PEASANT)) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::clearHiddenFlagAndUpdatePosition,
                    DAT_UnitsState::ptr)(unitID);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                    DAT_UnitsState::ptr)(unitID);
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
                DAT_UnitsState::instance.units[unitID].buildingID = 0;
                DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
                return;
            }
        }
        int despawnUnitID = 0;
        int highestPriority = 0;
        for (int unitID = 1; unitID < (int)DAT_UnitsState::instance.maxUnitCount; unitID++) {
            if ((DAT_UnitsState::instance.units[unitID].logicalState == OpenSHC::Map::Units::ULS_NORMAL)
                && (DAT_UnitsState::instance.units[unitID].dying == 0)
                && (DAT_UnitsState::instance.units[unitID].owner == playerID)
                && (DAT_UnitsState::instance.units[unitID].isSelectable_OR_matchTime == 0)
                && (DAT_UnitsState::instance.units[unitID].field64_0x90 == 0)
                && (DAT_UnitsState::instance.units[unitID].isStalked == 0)) {
                int despawnPriority;
                switch (DAT_UnitsState::instance.units[unitID].unitType) {
                case OpenSHC::Map::Units::UT_WHEATFARMER:
                    despawnPriority = 4;
                    break;
                case OpenSHC::Map::Units::UT_HOPSFARMER:
                    despawnPriority = 14;
                    break;
                case OpenSHC::Map::Units::UT_APPLEFARMER:
                    despawnPriority = 2;
                    break;
                case OpenSHC::Map::Units::UT_DAIRYFARMER:
                    despawnPriority = 1;
                    break;
                case OpenSHC::Map::Units::UT_HUNTER:
                    despawnPriority = 3;
                    break;
                case OpenSHC::Map::Units::UT_MILLER:
                    despawnPriority = 5;
                    break;
                case OpenSHC::Map::Units::UT_BAKER:
                    despawnPriority = 6;
                    break;
                case OpenSHC::Map::Units::UT_WOODCUTTER:
                    despawnPriority = 7;
                    break;
                case OpenSHC::Map::Units::UT_QUARRYMASON:
                    despawnPriority = 8;
                    break;
                case OpenSHC::Map::Units::UT_QUARRYWORKER:
                    despawnPriority = 9;
                    break;
                case OpenSHC::Map::Units::UT_PITCHMAN:
                    despawnPriority = 12;
                    break;
                case OpenSHC::Map::Units::UT_MINER:
                    despawnPriority = 11;
                    break;
                case OpenSHC::Map::Units::UT_TRANSPORTMINER:
                    despawnPriority = 10;
                    break;
                case OpenSHC::Map::Units::UT_FLETCHER:
                    despawnPriority = 15;
                    break;
                case OpenSHC::Map::Units::UT_BREWER:
                    despawnPriority = 20;
                    break;
                case OpenSHC::Map::Units::UT_POLETURNER:
                    despawnPriority = 16;
                    break;
                case OpenSHC::Map::Units::UT_SMITH:
                    despawnPriority = 17;
                    break;
                case OpenSHC::Map::Units::UT_ARMORER:
                    despawnPriority = 18;
                    break;
                case OpenSHC::Map::Units::UT_TANNER:
                    despawnPriority = 19;
                    break;
                case OpenSHC::Map::Units::UT_PRIEST:
                    despawnPriority = 22;
                    break;
                case OpenSHC::Map::Units::UT_HEALER:
                    despawnPriority = 23;
                    break;
                case OpenSHC::Map::Units::UT_INNKEEPER:
                    despawnPriority = 21;
                    break;
                default:
                    continue;
                }
                if (despawnPriority > highestPriority) {
                    highestPriority = despawnPriority;
                    despawnUnitID = unitID;
                }
            }
        }
        if (despawnUnitID != 0) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::clearHiddenFlagAndUpdatePosition,
                DAT_UnitsState::ptr)(despawnUnitID);
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                DAT_UnitsState::ptr)(despawnUnitID);
            DAT_UnitsState::instance.units[despawnUnitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
            DAT_UnitsState::instance.units[despawnUnitID].buildingID = 0;
            DAT_UnitsState::instance.units[despawnUnitID].updateTickTracker = 0;
        }
    }
}
}
