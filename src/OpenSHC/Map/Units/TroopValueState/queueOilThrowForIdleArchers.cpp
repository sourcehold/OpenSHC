#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051C470
        void TroopValueState::queueOilThrowForIdleArchers()
        {
            for (int unitID = 1; unitID < DAT_UnitsState::instance.maxUnitCount; ++unitID) {
                if (DAT_UnitsState::instance.units[unitID].logicalState == Map::Units::ULS_INVISIBLE) {
                    continue;
                }
                BOOLEnum const isAIPlayerWithKeep
                    = MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::getPlayerNot1AndHasKeep, this)(
                        DAT_UnitsState::instance.units[unitID].owner);
                if (!isAIPlayerWithKeep || DAT_UnitsState::instance.units[unitID].unitType != Map::Units::UT_E_ENGINEER
                    || DAT_UnitsState::instance.units[unitID].dying != 0
                    || DAT_UnitsState::instance.units[unitID].state.generic != Map::Units::States::US_SIT_DOWNUnk) {
                    continue;
                }
                int radius = 3;
                if (110 < DAT_UnitsState::instance.units[unitID].terrainOrClimbHeight) {
                    radius = 5;
                }
                MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::computeTotalUnitsWithinDistance,
                    DAT_PathFindingState::ptr)(DAT_TroopValueState::instance.attackInfo.pitchRelatedPlayerID, 0, 0,
                    DAT_UnitsState::instance.units[unitID].tile, radius);
                if (DAT_PathFindingState::instance.ALGO_TotalTroopValue < 10
                    || DAT_PathFindingState::instance.ALGO_TotalTroopCount < 2
                    || !DAT_PathFindingState::instance.field_0x64) {
                    continue;
                }
                int const targetUnitID = DAT_PathFindingState::instance.field_0x64;
                DAT_UnitsState::instance.units[unitID].targetingType = Map::Units::UIT_THROW_OIL;
                DAT_UnitsState::instance.units[unitID].attackAtTileX = DAT_UnitsState::instance.units[targetUnitID].x;
                DAT_UnitsState::instance.units[unitID].attackAtTileY = DAT_UnitsState::instance.units[targetUnitID].y;
                DAT_UnitsState::instance.units[unitID].animationFrame = 4;
            }
        }

    }
}
}
