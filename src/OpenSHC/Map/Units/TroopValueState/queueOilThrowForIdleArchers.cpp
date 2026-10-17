#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
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

        using Map::Units::UnitInstructionType;
        using Map::Units::UnitLogicState;
        using Map::Units::UnitType;
        using Map::Units::States::UnitState;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051C470
        void TroopValueState::queueOilThrowForIdleArchers()
        {
            BOOLEnum BVar1;
            Unit* _pUnit;
            int iVar4;
            iVar4 = 1;
            if (1 < DAT_UnitsState::instance.maxUnitCount) {
                _pUnit = &DAT_UnitsState::instance.units[1];
                do {
                    if (_pUnit->logicalState != Map::Units::ULS_INVISIBLE
                        && (BVar1 = MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::getPlayerNot1AndHasKeep, this)(
                                (int)_pUnit->owner),
                            BVar1)
                        && _pUnit->unitType == Map::Units::UT_E_ENGINEER && _pUnit->dying == 0
                        && _pUnit->state.generic == Map::Units::States::US_SIT_DOWNUnk) {
                        int iVar2 = 3;
                        if (0x6e < _pUnit->terrainOrClimbHeight) {
                            iVar2 = 5;
                        }
                        MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::computeTotalUnitsWithinDistance,
                            DAT_PathFindingState::ptr)(DAT_TroopValueState::instance.attackInfo.pitchRelatedPlayerID, 0, 0, _pUnit->tile, iVar2);
                        if (10 <= DAT_PathFindingState::instance.ALGO_TotalTroopValue && 2 <= DAT_PathFindingState::instance.ALGO_TotalTroopCount
                            && DAT_PathFindingState::instance.field34_0x64) {
                            iVar2 = DAT_PathFindingState::instance.field34_0x64;
                            _pUnit->targetingType = Map::Units::UIT_THROW_OIL;
                            _pUnit->attackAtTileX = DAT_UnitsState::instance.units[iVar2].x;
                            _pUnit->attackAtTileY = DAT_UnitsState::instance.units[iVar2].y;
                            _pUnit->animationFrame = 4;
                        }
                    }
                    iVar4 = iVar4 + 1;
                    _pUnit = _pUnit + 1;
                } while (iVar4 < DAT_UnitsState::instance.maxUnitCount);
            }
        }

    }
}
}
